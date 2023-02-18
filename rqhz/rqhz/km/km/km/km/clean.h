auto clean_from_big_pools( const uintptr_t ntoskrnl , const uintptr_t start ) -> NTSTATUS
{
	////////////SPOOF_FUNC;

	const auto find_big_pool_table = [ & ]( uintptr_t* table , size_t* size ) -> NTSTATUS
	{
		const auto rva = [ & ]( void* instruction , unsigned long offset , unsigned long size ) -> uintptr_t
		{
			return ( reinterpret_cast< uintptr_t > ( instruction ) + size + *reinterpret_cast< long* >( reinterpret_cast< uintptr_t > ( instruction ) + offset ) );
		};

		const auto ex_protect_pool_ex_address = rva( reinterpret_cast< void* >(
			utils::find_pattern( ntoskrnl , "\xE8\x00\x00\x00\x00\x83\x67\x0C\x00" , "x????xxxx" ) ) , 1 , 5 );

		if ( !ex_protect_pool_ex_address )
		{
			return STATUS_UNSUCCESSFUL;
		}

		*table = rva( reinterpret_cast< void* > ( ex_protect_pool_ex_address + 0x95 ) , 3 , 7 );
		*size = rva( reinterpret_cast< void* > ( ex_protect_pool_ex_address + 0x8E ) , 3 , 7 );

		return STATUS_SUCCESS;
	};

	uintptr_t p_pool_big_page_table = 0;
	uintptr_t p_pool_big_page_table_size = 0;

	if ( !NT_SUCCESS( find_big_pool_table( &p_pool_big_page_table , &p_pool_big_page_table_size ) ) )
	{
		return STATUS_UNSUCCESSFUL;
	}

	PPOOL_TRACKER_BIG_PAGES pool_big_page_table = 0;
	RtlCopyMemory( &pool_big_page_table , ( PVOID ) p_pool_big_page_table , 8 );

	size_t pool_big_page_table_size = 0;
	RtlCopyMemory( &pool_big_page_table_size , ( PVOID ) p_pool_big_page_table_size , 8 );

	for ( int i = 0; i < pool_big_page_table_size; i++ )
	{
		if ( pool_big_page_table[ i ].va == start || pool_big_page_table[ i ].va == ( start + 0x1 ) )
		{
			pool_big_page_table[ i ].va = 0x1;
			pool_big_page_table[ i ].number_of_bytes = 0x0;

			return STATUS_SUCCESS;
		}
	}

	return STATUS_UNSUCCESSFUL;
}

auto null_page_frame_numbers( const uintptr_t start , const uint32_t size ) -> NTSTATUS
{
	const auto null_page_frame_numbers = [ & ]( const MDL* mdl ) -> bool
	{
		const auto pages = MmGetMdlPfnArray( mdl );

		if ( !pages )
		{
			return false;
		}

		const auto page_count = ADDRESS_AND_SIZE_TO_SPAN_PAGES( MmGetMdlVirtualAddress( mdl ) , MmGetMdlByteCount( mdl ) );

		unsigned long null_pfn = 0x0;

		MM_COPY_ADDRESS source_address = { &null_pfn };

		for ( auto i = 0ul; i < page_count; i++ )
		{
			size_t bytes = 0;
			MmCopyMemory( &pages[ i ] , source_address , sizeof( unsigned long ) , MM_COPY_MEMORY_VIRTUAL , &bytes );
		}

		return true;
	};

	const auto mdl = IoAllocateMdl( reinterpret_cast< void* > ( start ) , static_cast< unsigned long > ( size ) , 0 , 0 , 0 );

	if ( !mdl )
	{
		return STATUS_UNSUCCESSFUL;
	}

	const auto status = null_page_frame_numbers( mdl );

	IoFreeMdl( mdl );

	return status;
}

auto nmi_callback( uint32_t callback , uint32_t reason ) -> NTSTATUS
{



}