#pragma once
#include "Imports.hpp"

using namespace Offsets;

template <typename t>
class c_list
{
public:

	auto size ( ) -> const std::uint32_t
	{
		return driver->read<std::uint32_t> ( reinterpret_cast<std::uintptr_t>(this) + 0x10 );
	}

	auto get ( const std::uint32_t idx ) -> t
	{
		return driver->read_chain<t> ( reinterpret_cast<std::uintptr_t>(this), { 0x18, 0x20ull + (idx * 0x8ull) } );
	}
};

class c_base_entity
{
public:

	auto get_client_entities ( ) -> c_list<std::uintptr_t>*
	{
		return driver->read_chain<c_list<std::uintptr_t>*> ( reinterpret_cast<std::uintptr_t>(this), { 0x20, 0x10, 0x28 } );
	}
};

class c_convar_client
{
public:

	auto set_camspeed ( const float speed ) -> void
	{
		driver->write<float>( reinterpret_cast<std::uintptr_t>(this) + m_camspeed, speed );
	}

	auto set_camlerp ( const float lerp ) -> void
	{
		driver->write<float> ( reinterpret_cast<std::uintptr_t>(this) + m_camlerp, lerp );
	}

	auto set_camlookspeed ( const float speed ) -> void
	{
		driver->write<float> ( reinterpret_cast<std::uintptr_t>(this) + m_camlookspeed, speed );
	}
};


class c_game_assembly
{
public:

	auto get_base_entity ( ) -> c_base_entity* // System_Collections_Generic_List_BaseGameMode__c*
	{
		return driver->read_chain<c_base_entity*> ( game_assembly, { m_BaseEntity_c, 0xB8 } ); // "Signature": "BaseEntity_c*"
	}

	auto get_convar_client ( ) -> c_convar_client*
	{
		return driver->read_chain<c_convar_client*> ( game_assembly, { m_ConVar_Client_c, 0xB8 } ); // "Signature": "ConVar_Client_c*"
	}
}*assembly;