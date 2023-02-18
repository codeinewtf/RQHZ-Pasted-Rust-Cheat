#include <ntdef.h>
#include <stdint.h>
#include <ntifs.h>
#include <ntddk.h>
#include <ntimage.h>
#include <windef.h>
#include <intrin.h>
#include <ntstrsafe.h>

#include "Spoof.h"
#include "definitions.h"
#include "encrypt.h"
#include "crt.h"
#include "utils.h"
#include "interface.h"
#include "clean.h"

#include "win32k.h"


__int64(__fastcall* o_function)(void*) = nullptr;
__int64 __fastcall communication_handler( void* a1 )
{
	

	
	
	if ( !a1 || ExGetPreviousMode( ) != UserMode || reinterpret_cast< request_data * >( a1 )->unique != request_unique )
	{
		return o_function( a1 );
	}

	//const auto misc_flags = reinterpret_cast<KTHREAD_MISC_FLAGS*>(reinterpret_cast<uintptr_t>(KeGetCurrentThread()) + 0x74);
	// Goodbye Bastian 

	const auto request = reinterpret_cast< request_data * >( a1 );

	switch ( request->code )
	{
	case request_base:
	{
		base_request data { 0 };

		if ( !utils::safe_copy( &data, request->data, sizeof( base_request ) ) )
		{
			return 0;
		}

		if ( !data.name || !data.pid )
		{
			return 0;
		}

		const auto base = utils::get_module_handle( data.pid, data.name );

		if ( !base )
		{
			return 0;
		}

		reinterpret_cast< base_request * > ( request->data )->handle = base;

		return request_success;
	}

	case request_write:
	{
		write_request data { 0 };

		if ( !utils::safe_copy( &data, request->data, sizeof( write_request ) ) )
		{
			return 0;
		}

		if ( data.address >= 0x7FFFFFFFFFFF || data.address <= 0 || !data.pid || !data.buffer || !data.size )
		{
			return 0;
		}

		PEPROCESS process;
		if (PsLookupProcessByProcessId( ( HANDLE )data.pid, &process ) == STATUS_SUCCESS )
		{
			size_t bytes = 0;
			if ( MmCopyVirtualMemory( IoGetCurrentProcess( ), ( void * )reinterpret_cast< write_request * > ( request->data )->buffer, process, ( void * )data.address, data.size, KernelMode, &bytes ) != STATUS_SUCCESS || bytes != data.size )
			{
				ObDereferenceObject( process );
				return 0;
			}

			ObDereferenceObject( process );
		}
		else
		{
			return 0;
		}

		return request_success;
	}
	case request_read:
	{
		read_request data { 0 };

		if ( !utils::safe_copy( &data, request->data, sizeof( read_request ) ) )
		{
			return 0;
		}

		if ( data.address >= 0x7FFFFFFFFFFF || data.address <= 0 || !data.pid || !data.buffer || !data.size )
		{
			return 0;
		}

		PEPROCESS process;
		if (PsLookupProcessByProcessId( ( HANDLE )data.pid, &process ) == STATUS_SUCCESS )
		{
			size_t bytes = 0;
			if ( MmCopyVirtualMemory( process, ( void * )data.address, IoGetCurrentProcess( ), reinterpret_cast< write_request * > ( request->data )->buffer, data.size, KernelMode, &bytes ) != STATUS_SUCCESS || bytes != data.size )
			{
				ObDereferenceObject( process );
				return 0;
			}

			ObDereferenceObject( process );
		}
		else
		{
			return 0;
		}

		return request_success;
	} 
	case request_pattern:
	{
		pattern_request data { 0 };

		if ( !utils::safe_copy( &data, request->data, sizeof( pattern_request ) ) )
		{
			return 0;
		}

		PEPROCESS process;
		if ( PsLookupProcessByProcessId( ( HANDLE )data.pid, &process ) == STATUS_SUCCESS )
		{
			const auto o_process = utils::swap_process( ( uintptr_t )process );

			if ( !o_process )
			{
				utils::swap_process( ( uintptr_t )o_process );

				ObDereferenceObject( process );

				return 0;
			}

			const auto address = utils::find_pattern( data.base, data.signature );

			utils::swap_process( o_process );

			ObDereferenceObject( process );

			if ( !address )
			{
				return 0;
			}

			reinterpret_cast< pattern_request * > ( request->data )->address = address;
		}
		else
		{
			return 0;
		}

		return request_success;
	}
	case request_unload:
	{
		*reinterpret_cast< unload_request * > ( request->data )->buffer = true;

		return request_success;
	}
	}
	return 0;
}


auto DriverEntry(uintptr_t pool_base, size_t size) -> NTSTATUS
{
	//win32k::initialize( ); 

	const auto win32k = utils::get_kernel_module( e( "win32k.sys" ) );
	const auto ntoskrnl = utils::get_kernel_module(e("ntoskrnl.exe") );

	const auto NtUserAutoRotateScreen_QWORD = utils::find_pattern(win32k, e("\x48\x8B\x05\xE5\x01\x06\x00"), e("xxxxxxx"));
	const auto NtUserRemoteRedrawRectangle_QWORD = utils::find_pattern(win32k, e( "\x48\x8B\x05\x05\xDE\x05\x00"), e( "xxxxxxx"));

	*( uintptr_t *)( dereference (NtUserAutoRotateScreen_QWORD) ) = utils::find_pattern(win32k, e( "\x48\x83\xEC\x38\x48\x8B\x05\x05\xDE"),e(  "xxxxxxxxx" ));

	o_function = *(decltype(o_function)*)(dereference(NtUserRemoteRedrawRectangle_QWORD));
	*(uintptr_t*)(dereference(NtUserRemoteRedrawRectangle_QWORD)) = ( uintptr_t )communication_handler;
	
	return STATUS_SUCCESS;
}