#pragma once
#include "Imports.hpp"

DWORD get_process_id( LPCSTR ProcessName ) {
	PROCESSENTRY32 pt;
	HANDLE hsnap = CreateToolhelp32Snapshot( TH32CS_SNAPPROCESS, 0 );
	pt.dwSize = sizeof( PROCESSENTRY32 );
	if ( Process32First( hsnap, &pt ) ) {
		do {
			if ( !lstrcmpi( pt.szExeFile, ProcessName ) ) {
				CloseHandle( hsnap );
				return pt.th32ProcessID;
			}
		} while ( Process32Next( hsnap, &pt ) );
	}
	CloseHandle( hsnap );
	return 0;
}

struct Color {
	float A, R, G, B;
	Color( ) = default;
	Color( float r, float g, float b, float a = 255 ) {
		this->R = r;
		this->G = g;
		this->B = b;
		this->A = a;
	}
	Color( uint32_t color ) {
		this->A = ( color >> 24 ) & 0xff;
		this->R = ( color >> 16 ) & 0xff;
		this->G = ( color >> 8 ) & 0xff;
		this->B = ( color & 0xff );
	}
	Color from_uint( uint32_t uint ) {
		return Color( uint );
	}
	static Color FromHSB( float flHue, float flSaturation, float flBrightness )
	{
		const float h = std::fmodf( flHue, 1.0f ) / ( 60.0f / 360.0f );
		const int i = static_cast<int>( h );
		const float f = h - static_cast<float>( i );
		const float p = flBrightness * ( 1.0f - flSaturation );
		const float q = flBrightness * ( 1.0f - flSaturation * f );
		const float t = flBrightness * ( 1.0f - flSaturation * ( 1.0f - f ) );

		float r = 0.0f, g = 0.0f, b = 0.0f;

		switch ( i )
		{
		case 0:
			r = flBrightness, g = t, b = p;
			break;
		case 1:
			r = q, g = flBrightness, b = p;
			break;
		case 2:
			r = p, g = flBrightness, b = t;
			break;
		case 3:
			r = p, g = q, b = flBrightness;
			break;
		case 4:
			r = t, g = p, b = flBrightness;
			break;
		case 5:
		default:
			r = flBrightness, g = p, b = q;
			break;
		}

		return Color( r, g, b );
	}
	void random_color( int iTick )
	{
		this->R = sin( 3.f * iTick + 0.f ) * 127 + 128;
		this->G = sin( 3.f * iTick + ( ( 2.f * M_PI ) / 3 ) ) * 127 + 128;
		this->B = sin( 3.f * iTick + ( ( 4.f * M_PI ) / 3 ) ) * 127 + 128;
		this->A = 255;
		// decrease 0.3f if you want it smoother
	}

	static Color black( float a = 255 ) {
		return { 0, 0, 0, a };
	}
	static Color white( float a = 255 ) {
		return { 255, 255, 255, a };
	}
	static Color red( float   a = 255 ) {
		return { 255, 0, 0, a };
	}
	static Color green( float a = 255 ) {
		return { 0, 255, 0, a };
	}
	static Color blue( float  a = 255 ) {
		return { 0, 0, 255, a };
	}
};

static void rainbow( Color &Color_ )
{
	static uint32_t cnt = 0;
	DWORD freq = .005f;

	Color _Color = Color(
		std::sin( freq * cnt + 0 ) * 127 + 128,
		std::sin( freq * cnt + 2 ) * 127 + 128,
		std::sin( freq * cnt + 4 ) * 127 + 128,
		255 );

	// Probably redundant
	if ( cnt++ >= (uint32_t)-1 ) cnt = 0;

	Color_ = _Color;
}

const char *items[]{
	"Stone",
	"Sulfur",
	"Metal",
	"Wood",
	"Hemp",
	"Stone Ore",
	"Sulfur Ore",
	"Metal Ore",
	"Backpack",
	"Corpse",
	"Stash",
	"Tool Cupboard",
	"Large Box",
	"Supply Drop",
	"Hackable Crate",
	"Auto Turret",
	"Landmine",
	"Flame Thrower",
	"Shotgun Trap",
	"Bear Trap",
	"Minicopter",
	"Attack Heli"
};
static bool selected[22];

namespace entityloop
{
	struct unity_str
	{
		char buffer[128];
	};

	camera_c *camera;
	matrix_s projection_matrix;
	c_projectile *held_item;
	c_tod_sky *tod_sky;
	Vector3 camera_position;
	c_modelstate *_model_c;

	void get_list( )
	{
		while ( true )
		{
			if ( rainy.player != 0 )
			{
				const auto base_entity = assembly->get_base_entity( );

				if ( !base_entity )
				{
					//std::cout << "BE Broken" << std::endl;
					continue;
				}

				const auto client_entities = base_entity->get_client_entities( );

				if ( !client_entities )
				{
					//std::cout << "CE Broken" << std::endl;
					continue;
				}

				std::vector<baseplayer *> players;
				std::vector<std::tuple<Vector3, const char *>> others{ };

				for ( std::uint32_t i = 0; i < client_entities->size( ); i++ )
				{
					const auto object = driver->read<std::uintptr_t>( client_entities->get( i ) + 0x10 );

					if ( !object )
					{
						continue;
					}

					const auto object_class = driver->read<std::uintptr_t>( object + 0x30 );

					if ( !object_class )
					{
						continue;
					}

					const auto tag = driver->read<WORD>( object_class + 0x54 );

					const auto name = driver->read_chain<unity_str>( object_class, { 0x60, 0x0 } ).buffer;

					if ( tag == 6 )
					{
						const auto player = driver->read<baseplayer *>( object + 0x28 );

						if ( !player )
						{
							continue;
						}

						if ( i == 0 )
						{

						}
						else
						{
							auto local_head_3d = rainy.player->get_bone( head );

							if ( local_head_3d.is_empty( ) )
							{
								continue;
							}

							const auto distance = player->player_model( )->position( ).distance( local_head_3d );

							if ( distance > config.Includes.playerdistance )
							{
								continue;
							}

							players.push_back( player );
						}

						continue;
					}
					std::tuple<Vector3, const char *> element{ { 0.f, 0.f, 0.f }, "" };
					if ( config.Includes.prefabesp )
					{
						if ( selected[0] == true ) // Stone
						{
							if ( strstr( name, ( "stone-collectable.prefab" ) ) )
							{
								element = std::tuple<Vector3, const char *>( { driver->read_chain<Vector3>( object_class, { 0x30, 0x8, 0x38, 0x90 } ), ( "stone" ) } );
								goto end;
							}
						}
						if ( selected[1] == true ) // Sulf
						{
							if ( strstr( name, ( "sulfur-collectable.prefab" ) ) )
							{
								element = std::tuple<Vector3, const char *>( { driver->read_chain<Vector3>( object_class, { 0x30, 0x8, 0x38, 0x90 } ), ( "sulfur" ) } );
								goto end;
							}
						}
						if ( selected[2] == true ) // Metal
						{
							if ( strstr( name, ( "metal-collectable.prefab" ) ) )
							{
								element = std::tuple<Vector3, const char *>( { driver->read_chain<Vector3>( object_class, { 0x30, 0x8, 0x38, 0x90 } ), ( "metal" ) } );
								goto end;
							}
						}
						if ( selected[3] == true ) // Wood
						{
							if ( strstr( name, ( "wood-collectable.prefab" ) ) )
							{
								element = std::tuple<Vector3, const char *>( { driver->read_chain<Vector3>( object_class, { 0x30, 0x8, 0x38, 0x90 } ), ( "wood" ) } );
								goto end;
							}
						}
						if ( selected[4] == true ) // Hemp
						{
							if ( strstr( name, ( "hemp-collectable.prefab" ) ) )
							{
								element = std::tuple<Vector3, const char *>( { driver->read_chain<Vector3>( object_class, { 0x30, 0x8, 0x38, 0x90 } ), ( "hemp" ) } );
								goto end;
							}
						}
						if ( selected[5] == true ) // Stone Ore
						{
							if ( strstr( name, ( "stone-ore.prefab" ) ) )
							{
								element = std::tuple<Vector3, const char *>( { driver->read_chain<Vector3>( object_class, { 0x30, 0x8, 0x38, 0x90 } ), ( "stone ore" ) } );
								goto end;
							}
						}
						if ( selected[6] == true ) // Sulfur Ore
						{
							if ( strstr( name, ( "sulfur-ore.prefab" ) ) )
							{
								element = std::tuple<Vector3, const char *>( { driver->read_chain<Vector3>( object_class, { 0x30, 0x8, 0x38, 0x90 } ), ( "sulfur ore" ) } );
								goto end;
							}
						}
						if ( selected[7] == true ) // Metal Ore
						{
							if ( strstr( name, ( "metal-ore.prefab" ) ) )
							{
								element = std::tuple<Vector3, const char *>( { driver->read_chain<Vector3>( object_class, { 0x30, 0x8, 0x38, 0x90 } ), ( "metal ore" ) } );
								goto end;
							}
						}
						if ( selected[8] == true ) // Backpack
						{
							if ( strstr( name, ( "item_drop_backpack.prefab" ) ) )
							{
								element = std::tuple<Vector3, const char *>( { driver->read_chain<Vector3>( object_class, { 0x30, 0x8, 0x38, 0x90 } ), ( "backpack" ) } );
								goto end;
							}
						}
						if ( selected[9] == true ) // Corpse
						{
							if ( strstr( name, ( "player_corpse.prefab" ) ) )
							{
								element = std::tuple<Vector3, const char *>( { driver->read_chain<Vector3>( object_class, { 0x30, 0x8, 0x38, 0x90 } ), ( "corpse" ) } );
								goto end;
							}
						}
						if ( selected[10] == true ) // Stash
						{
							if ( strstr( name, ( "small_stash_deployed.prefab" ) ) )
							{
								element = std::tuple<Vector3, const char *>( { driver->read_chain<Vector3>( object_class, { 0x30, 0x8, 0x38, 0x90 } ), ( "stash" ) } );
								goto end;
							}
						}
						if ( selected[11] == true ) // Tool Cupboard
						{
							if ( strstr( name, ( "cupboard.tool.deployed.prefab" ) ) )
							{
								element = std::tuple<Vector3, const char *>( { driver->read_chain<Vector3>( object_class, { 0x30, 0x8, 0x38, 0x90 } ), ( "toolcupboard" ) } );
								goto end;
							}
						}
						if ( selected[12] == true ) // Large Box
						{
							if ( strstr( name, ( "box.wooden.large.prefab" ) ) )
							{
								element = std::tuple<Vector3, const char *>( { driver->read_chain<Vector3>( object_class, { 0x30, 0x8, 0x38, 0x90 } ), ( "large box" ) } );
								goto end;
							}
						}
						if ( selected[13] == true ) // Supply Drop
						{
							if ( strstr( name, ( "supply_drop.prefab" ) ) )
							{
								element = std::tuple<Vector3, const char *>( { driver->read_chain<Vector3>( object_class, { 0x30, 0x8, 0x38, 0x90 } ), ( "air drop" ) } );
								goto end;
							}
						}
						if ( selected[14] == true ) // Hackable Crate
						{
							if ( strstr( name, ( "codelockedhackablecrate.prefab" ) ) )
							{
								element = std::tuple<Vector3, const char *>( { driver->read_chain<Vector3>( object_class, { 0x30, 0x8, 0x38, 0x90 } ), ( "locked create" ) } );
								goto end;
							}
						}
						if ( selected[15] == true ) // Auto Turret
						{
							if ( strstr( name, "autoturret_deployed.prefab" ) )
							{
								element = std::tuple<Vector3, const char *>( { driver->read_chain<Vector3>( object_class, { 0x30, 0x8, 0x38, 0x90 } ),  "turret" } );
								goto end;
							}
						}
						if ( selected[16] == true ) // Landmine
						{
							if ( strstr( name, "trap.landmine.prefab" ) )
							{
								element = std::tuple<Vector3, const char *>( { driver->read_chain<Vector3>( object_class, { 0x30, 0x8, 0x38, 0x90 } ),  "mine" } );
								goto end;
							}
						}
						if ( selected[17] == true ) // Flame Thrower
						{
							if ( strstr( name, "flameturret.deployed.prefab" ) )
							{
								element = std::tuple<Vector3, const char *>( { driver->read_chain<Vector3>( object_class, { 0x30, 0x8, 0x38, 0x90 } ),  "flame turret" } );
								goto end;
							}
						}
						if ( selected[18] == true ) // Shotgun Trap
						{
							if ( strstr( name, "guntrap.deployed" ) )
							{
								element = std::tuple<Vector3, const char *>( { driver->read_chain<Vector3>( object_class, { 0x30, 0x8, 0x38, 0x90 } ),  "shotgun trap" } );
								goto end;
							}
						}
						if ( selected[19] == true ) // Bear Trap
						{
							if ( strstr( name, "beartrap.prefab" ) )
							{
								element = std::tuple<Vector3, const char *>( { driver->read_chain<Vector3>( object_class, { 0x30, 0x8, 0x38, 0x90 } ),  "bear trap" } );
								goto end;
							}
						}
						if ( selected[20] == true )
						{
							if ( strstr( name, "minicopter.entity.prefab" ) )
							{
								element = std::tuple<Vector3, const char *>( { driver->read_chain<Vector3>( object_class, { 0x30, 0x8, 0x38, 0x90 } ),  "minicopter" } );
								goto end;
							}
						}
						if ( selected[21] == true )
						{
							if ( strstr( name, "patrolhelicoptermarker.prefab" ) )
							{
								element = std::tuple<Vector3, const char *>( { driver->read_chain<Vector3>( object_class, { 0x30, 0x8, 0x38, 0x90 } ),  "attack heli" } );
								goto end;
							}


						}

					}
				end:
					auto local_head_3d = rainy.player->get_bone( head );

					if ( local_head_3d.is_empty( ) )
					{
						continue;
					}

					const auto distance = std::get<0>( element ).distance( local_head_3d );

					if ( distance > config.Includes.prefabdistance / 2.f )
					{
						continue;
					}

					others.push_back( element );
				}

				rainy.cache_mutex.lock( );

				rainy.player_list = players;
				rainy.prefab_list = others;

				rainy.cache_mutex.unlock( );

				std::this_thread::sleep_for( std::chrono::milliseconds( 1500 ) );
			}
		}
	}

	void get_instances( )
	{
		while ( true )
		{
			rainy.cache_mutex.lock( );

			rainy.player = baseplayer::local_player( );
			held_item = rainy.player->get_projectile( );
			tod_sky = driver->read_chain<c_tod_sky *>( game_assembly, { m_tod_sky_c, 0xB8, 0x0, 0x10, 0x20 } );
			camera = camera_c::get_instance( );

			rainy.cache_mutex.unlock( );

			std::this_thread::sleep_for( std::chrono::milliseconds( 1500 ) );
		}
	}

	void get_camera_fields( )
	{
		while ( true )
		{
			if ( rainy.player != 0 )
			{
				projection_matrix = camera->projection_matrix( );
				camera_position = camera->position( );
			}

			std::this_thread::sleep_for( std::chrono::milliseconds( 2 ) );
		}
	}
}

namespace features
{
	auto GetWeaponRepeatDelay( std::string weaponID ) -> float
	{
		if ( weaponID == "rifle.ak" )
		{
			return 0.1333; //Completed
		}
		else if ( weaponID == "smg.2" )
		{
			return 0.1; //Completed
		}
		else if ( weaponID == "rifle.ak" )
		{
			return 2.6; //Completed
		}
		else if ( weaponID == "rifle.lr300" )
		{
			return 0.12; //Completed
		}
		else if ( weaponID == "lmg.m249" )
		{
			return 0.12; //Completed
		}
		else if ( weaponID == "rifle.m39" )
		{
			return 0.2; //Completed
		}
		else if ( weaponID == "pistol.m92" )
		{
			return 0.15; //Completed
		}
		else if ( weaponID == "smg.mp5" )
		{
			return 0.1; //Completed
		}
		else if ( weaponID == "pistol.nailgun" )
		{
			return 0.15; //Completed
		}
		else if ( weaponID == "pistol.revolver" )
		{
			return 0.175; //Completed
		}
		else if ( weaponID == "pistol.semiauto" )
		{
			return 0.15; //Completed
		}
		else if ( weaponID == "rifle.semiauto" )
		{
			return 0.175; //Completed
		}
		else if ( weaponID == "smg.thompson" )
		{
			return 0.13; //Completed
		}
		else if ( weaponID == "pistol.python" )
		{
			return 0.15; //Completed
		}
		else if ( weaponID == "hmlmg" )
		{
			return 0.13; //Completed
		}
		else if ( weaponID == "pistol.prototype17" )
		{
			return 0.09;
		}
	}

	auto recoil_vals_ov( float n1, float n2, float n3, float n4, c_new_recoil_override *recoil_ov ) -> void
	{
		recoil_ov->set_recoil_yaw_min( config.Includes.RecoilYaw * n1 );
		recoil_ov->set_recoil_yaw_max( config.Includes.RecoilYaw * n1 );
		recoil_ov->set_recoil_pitch_min( config.Includes.RecoilPitch * n3 );
		recoil_ov->set_recoil_pitch_max( config.Includes.RecoilPitch * n4 );
	}

	auto recoil_vals_prop( float n1, float n2, float n3, float n4, c_recoil_properties *recoil_prop ) -> void
	{
		recoil_prop->set_recoil_yaw_min( config.Includes.RecoilYaw * n1 );
		recoil_prop->set_recoil_yaw_max( config.Includes.RecoilYaw * n1 );
		recoil_prop->set_recoil_pitch_min( config.Includes.RecoilPitch * n3 );
		recoil_prop->set_recoil_pitch_max( config.Includes.RecoilPitch * n4 );
	}

	auto no_recoil_ov( std::string itemname, c_new_recoil_override *recoil_ov ) -> void
	{
		if ( itemname == "rifle.ak" ) // AK47
		{
			recoil_vals_ov( 1.5f, 2.5f, -2.5f, -3.5f, recoil_ov );
		}
		else if ( itemname == "rifle.ak.ice" ) // AK47 ICE
		{
			recoil_vals_ov( 1.5f, 2.5f, -2.5f, -3.5f, recoil_ov );
		}
		else if ( itemname == "rifle.lr300" ) // LR300
		{
			recoil_vals_ov( -1.f, 1.f, -2.f, -3.f, recoil_ov );
		}
		else if ( itemname == "lmg.m249" ) // M249
		{
			recoil_vals_ov( 1.25f, 2.25f, -3.f, -4.f, recoil_ov );
		}
		else if ( itemname == "rifle.m39" ) // M39
		{
			recoil_vals_ov( 1.5f, 2.5f, -3.f, -4.f, recoil_ov );
		}
		else if ( itemname == "rifle.semiauto" ) // SAR
		{
			recoil_vals_ov( -0.5f, 0.5f, -2.f, -3.f, recoil_ov );
		}
		else if ( itemname == "hmlmg" ) // HMLMG
		{
			recoil_vals_ov( -1.25f, -2.5f, -3.f, -4.f, recoil_ov );
		}
		else if ( itemname == "smg.mp5" ) // MP5
		{
			recoil_vals_ov( -1.f, 1.f, -1.f, -3.f, recoil_ov );
		}
		else if ( itemname == "smg.thompson" ) // THOMMY
		{
			recoil_vals_ov( -1.f, 1.f, -1.5f, -2.f, recoil_ov );
		}
		else if ( itemname == "smg.2" ) // CUSTOM
		{
			recoil_vals_ov( -1.f, 1.f, -1.5f, -2.f, recoil_ov );
		}
		else if ( itemname == "pistol.m92" ) // M92
		{
			recoil_vals_ov( -1.f, 1.f, -2.f, -2.5f, recoil_ov );
		}
		else if ( itemname == "pistol.semiauto" ) // SARP
		{
			recoil_vals_ov( -1.f, 1.f, -7.f, -8.f, recoil_ov );
		}
	}

	auto no_recoil_prop( std::string itemname, c_recoil_properties *recoil_prop ) -> void
	{
		if ( itemname == "pistol.nailgun" ) // NAILGUN
		{
			recoil_vals_prop( -1.f, 1.f, -3.f, -6.f, recoil_prop );
		}
		else if ( itemname == "pistol.python" ) // PYTHON
		{
			recoil_vals_prop( -2.f, 2.f, -15.f, -16.f, recoil_prop );
		}
		else if ( itemname == "pistol.revolver" ) // REVO
		{
			recoil_vals_prop( -1.f, 1.f, -3.f, -6.f, recoil_prop );
		}
		else if ( itemname == "shotgun.pump" ) // PUMP
		{
			recoil_vals_prop( 4.f, 8.f, -10.f, -14.f, recoil_prop );
		}
		else if ( itemname == "shotgun.double" ) // DOUBLEB
		{
			recoil_vals_prop( 8.f, 15.f, -10.f, -15.f, recoil_prop );
		}
		else if ( itemname == "shotgun.spas12" ) // SPAS12
		{
			recoil_vals_prop( 4.f, 8.f, -10.f, -14.f, recoil_prop );
		}
		else if ( itemname == "shotgun.waterpipe" ) // WATERPIPE
		{
			recoil_vals_prop( 4.f, 8.f, -10.f, -14.f, recoil_prop );
		}
		else if ( itemname == "crossbow" ) // CROSSY
		{
			recoil_vals_prop( -3.f, 3.f, -3.f, -6.f, recoil_prop );
		}
		else if ( itemname == "rifle.l96" ) // L9
		{
			recoil_vals_prop( -2.f, 2.f, -1.f, -1.5f, recoil_prop );
		}
		else if ( itemname == "rifle.bolt" ) // CROSSY
		{
			recoil_vals_prop( -4.f, 4.f, -2.f, -3.f, recoil_prop );
		}
		else if ( itemname == "pistol.prototype17" ) // GLOCK
		{
			recoil_vals_prop( -1.f, 1.f, -2.f, -2.5f, recoil_prop );
		}
	}

	auto infinite_jump( c_playermovement *movement ) -> void
	{
		if ( !GetAsyncKeyState( VK_SPACE ) )
		{
			return;
		}

		movement->set_jump_time( 0.51f );
		movement->set_land_time( 0.3f );
		movement->set_ground_time( 99999.f );
	}

	auto spiderman( c_playermovement *movement ) -> void
	{
		movement->set_ground_new_angle( 0.f );
	}

	auto fat_bullet( c_held *held )
	{
		auto set_thickness = []( std::uintptr_t each ) -> void
		{
			driver->write<float>( each + 0x2C, config.Includes.bulletsize );
		};

		held->get_created_projectiles( set_thickness );
	}

	auto admin_flags( baseplayer *player ) -> void
	{
		player->SetFlags( 4 );

		const auto convar_client = assembly->get_convar_client( );

		convar_client->set_camlerp( 1.f );
		convar_client->set_camlookspeed( 1.f );
		convar_client->set_camspeed( 1.f );
	}

	auto night_mode( c_tod_sky *tod_sky ) -> void
	{
		uintptr_t TOD_Sky = driver->read<uintptr_t>( game_assembly + m_tod_sky_c ); // tod_sky_c*
		uintptr_t TOD_AimbientParameters = driver->read_chain<uintptr_t>( TOD_Sky, { 0xB8, 0x0, 0x10, 0x20, Offsets::Classes::TOD_Sky::Ambient } );
		uintptr_t TOD_CloudParameters = driver->read_chain<uintptr_t>( TOD_Sky, { 0xB8, 0x0, 0x10, 0x20, Offsets::Classes::TOD_Sky::Clouds } );
		uintptr_t TOD_NightParameters = driver->read_chain<uintptr_t>( TOD_Sky, { 0xB8, 0x0, 0x10, 0x20, Offsets::Classes::TOD_Sky::Night } );
		uintptr_t TOD_StarParameters = driver->read_chain<uintptr_t>( TOD_Sky, { 0xB8, 0x0, 0x10, 0x20, Offsets::Classes::TOD_Sky::Stars } );
		uintptr_t TOD_MoonParameters = driver->read_chain<uintptr_t>( TOD_Sky, { 0xB8, 0x0, 0x10, 0x20, Offsets::Classes::TOD_Sky::Moon } );
		uintptr_t TOD_SunParameters = driver->read_chain<uintptr_t>( TOD_Sky, { 0xB8, 0x0, 0x10, 0x20, Offsets::Classes::TOD_Sky::Sun } );
		uintptr_t TOD_DayParameters = driver->read_chain<uintptr_t>( TOD_Sky, { 0xB8, 0x0, 0x10, 0x20, Offsets::Classes::TOD_Sky::Day } );

		if ( config.Includes.beautifulnight == true )
		{
			//Cloud Stuff

			//Day Stuff
			driver->write<float>( TOD_DayParameters + Offsets::Classes::TOD_DayParameters::ReflectionMultiplier, 0.f );
			driver->write<float>( TOD_DayParameters + Offsets::Classes::TOD_DayParameters::ShadowStrength, 0.f );
			//Aimbient Stuff

			//Moon Stuff	

			//Star Stuff
			driver->write<float>( TOD_StarParameters + Offsets::Classes::TOD_StarParameters::Brightness, 256.f );
			driver->write<float>( TOD_StarParameters + Offsets::Classes::TOD_StarParameters::Size, 0.5f );
			//Night Stuff
			driver->write<float>( TOD_NightParameters + Offsets::Classes::TOD_NightParameters::LightIntensity, 8.f );
			driver->write<float>( TOD_NightParameters + Offsets::Classes::TOD_NightParameters::AmbientMultiplier, 10.f );
			//ImColor White = { 255,255,255 };
			//driver->write<ImColor>(TOD_NightParameters + Offsets::Classes::TOD_NightParameters::MoonColor, &White);
		}
	}

	auto flyhack_bar( baseplayer *player, c_playermovement *movement ) -> void
	{
		const auto grounded = movement->get_grounded( );
		auto position = player->player_model( )->position( );
		if ( position.is_empty( ) ) return;

		static auto start = Vector3( );
		if ( !grounded && start.is_empty( ) )
			start = position;
		else if ( grounded )
		{
			start = Vector3( 0.00f, 0.00f, 0.00f );
			config.Includes.m_height = 0.00f;
			config.Includes.m_direction = 0.00f;
		}
		else if ( !start.is_empty( ) )
		{
			config.Includes.m_height = position.y - start.y;
			config.Includes.m_direction = Vector2( position.x, position.z ).distance( { start.x, start.z } );
		}
	}

	auto omnisprint( c_playermovement *movement ) -> void
	{
		movement->set_running( 1.f );
	}

	auto automatic( c_held *held ) -> void
	{
		held->automatic( );
		held->set_auto_burst( 0 );
	}

	auto no_sway( c_held *held ) -> void
	{
		held->set_aim_sway( 0.f );
		held->set_aim_sway_speed( 0.f );
	}

	auto no_spread( c_held *held ) -> void
	{
		held->set_aimcone( 0.f );
		held->set_aimcone_penalty_per_shot( 0.f );
		held->set_aimcone_penalty( 0.f );
		held->set_hip_aimcone( 0.f );
		held->set_stance_penalty( 0.f );
		held->set_aimcone_penalty_max( 0.f );
		held->set_aimcone_penalty_recover_time( 0.f );
		held->set_aimcone_penalty_recover_delay( 0.f );
		held->set_sight_aimcone_scale( 0.f );
		held->set_sight_aimcone_offset( 0.f );
		held->set_hip_aimcone_scale( 0.f );
		held->set_hip_aimcone_offset( 0.f );
	}

	auto super_eoka( c_projectile *projectile, c_held *held ) -> void
	{
		auto itemname = entityloop::held_item->get_item_name( );
		if ( itemname.find( "eoka" ) == std::string::npos || itemname.find( "shotgun" ) == std::string::npos )
		{
			if ( !projectile->is_valid_weapons( ) )
			{
				const auto list = driver->read<std::uintptr_t>( (uintptr_t)held + Classes::BaseProjectile::createdProjectiles );

				if ( !list )
				{
					return;
				}

				const auto key = driver->read<std::uintptr_t>( list + 0x10 );

				if ( !key )
				{
					return;
				}

				const auto size = driver->read<int>( list + 0x18 );

				if ( !size )
				{
					return;
				}

				for ( int i = 0; i < size; ++i )
				{
					const auto projectile = driver->read<std::uintptr_t>( key + 0x20 + ( i * 0x8 ) );

					if ( !projectile )
					{
						continue;
					}
					const auto item_projectile_mod = driver->read<c_item_projectile_mod *>( projectile + m_mod );

					if ( !item_projectile_mod )
					{
						return;
					}

					item_projectile_mod->set_projectile_spread( 0.f );
					item_projectile_mod->set_projectile_velocity_spread( 0.f );
					held->set_success_fraction( 1.f );
				}
			}
		}
	}

	auto no_flashbang( ) -> void
	{
		auto flashbangoverlay = driver->read<uintptr_t>( game_assembly + m_flashbangoverlay_c ); //flashbangoverlay_c
		auto flashbangeffect = driver->read<uintptr_t>( flashbangoverlay + 0xB8 );
		auto flash = driver->read<uintptr_t>( flashbangeffect + 0x00 );
		driver->write<float>( flash + 0x40, 0.f );
	}

	auto fly_hack( c_playermovement *movement) -> void
	{
		if ( GetAsyncKeyState( 0x43 ) )
		{
			movement->set_capusle_center( -300.f);

		}
		else
		{
			movement->set_capusle_center( 0.9f );

		}

	}

	auto silent_walk( c_modelstate *state_model, c_playermovement *movement ) -> void
	{
		state_model->SetFlag( OnGround );
		movement->set_grounded( 1.f );
	}


	

	auto quick_process( baseplayer *player ) -> void
	{
		if ( !player )
			return;

		const auto movement = player->player_movement( );

		if ( config.Includes.omnisprint )
		{
			features::omnisprint( movement );
		}
	}

	auto tod_sky( baseplayer *player ) -> void
	{
		if ( !player )
			return;

		if ( GetAsyncKeyState( VK_MBUTTON ) ) //UP
			player->player_eyes( )->ViewOffset( Vector3( 0.0f, 1.f, 0.f ) );
		else if ( GetAsyncKeyState( 89 ) ) //LEFT
			player->player_eyes( )->ViewOffset( Vector3( -1.f, 0.f, 0.f ) );
		else if ( GetAsyncKeyState( 88 ) ) //RIGHT
			player->player_eyes( )->ViewOffset( Vector3( 1.f, 0.f, 0.f ) );

		if ( config.Includes.beautifulnight )
		{
			features::night_mode( entityloop::tod_sky );
		}
	}

	auto process( baseplayer *player ) -> void
	{
		if ( !player )
			return;

		if ( config.Includes.fakeadmin )
		{
			features::admin_flags( player );
		}

		const auto movement = player->player_movement( );

		if ( movement )
		{
			if ( config.Includes.omnisprint )
			{
				features::omnisprint( movement );
			}

			if ( config.Includes.infinitejump )
			{
				features::infinite_jump( movement );
			}

			if ( config.Includes.spiderman )
			{
				features::spiderman( movement );
			}

			if ( config.Includes.flyhackbar == true )
			{
				features::flyhack_bar( player, movement );
				config.Includes.fly_height = config.Includes.m_height * 52.f;
				config.Includes.fly_direction = config.Includes.m_direction * 52.f;
				if ( config.Includes.antiflyhackkick == true )
				{
					if ( config.Includes.fly_height >= 240.f ) movement->set_target_movement( { 0.00f, -250.f, 0.00f } );
					if ( config.Includes.fly_direction >= 240.f ) movement->set_target_movement( { 0.00f, -250.f, 0.00f } );
				}
			}
		}

		if ( config.Includes.timechanger )
		{
			ConVars::convar_admin( )->admintime( config.Includes.clienttime );
		}

		if ( GetAsyncKeyState( 70 ) & 0x8000 )
			player->changefov( 45.f );
		else
			player->changefov( config.Includes.playerfov );

		if ( config.Includes.noflashbang )
		{
			features::no_flashbang( );
		}

		if (config.Includes.flyhack )
		{
			features::fly_hack( movement );

		}

		if ( config.Includes.airjump )
		{
			if ( GetAsyncKeyState( VK_SPACE ) )
			{
				features::silent_walk( entityloop::_model_c, movement );
			}
 		}

	


		//if ( config.Includes.shootincopter )
		//{
		//	const auto mounted = player->base_mountable ( );

		//	if ( mounted )
		//	{
		//		mounted->set_can_wield_items ( true );
		//	}
		//}

		const auto projectile = player->get_projectile( );
		std::string itemname = projectile->get_item_name( );

		if ( projectile && projectile->is_weapon( ) )
		{
			const auto held = projectile->get_held( );

			if ( held )
			{
				if ( config.Includes.thickbullet )
				{
					features::fat_bullet( held );
				}

				const auto recoil_propreties = held->get_recoil_propreties( );
				const auto new_recoil_override = recoil_propreties->get_new_recoil_override( );

				if ( recoil_propreties || new_recoil_override )
				{
					if ( config.Includes.norecoil )
					{
						features::no_recoil_ov( itemname, new_recoil_override );
						features::no_recoil_prop( itemname, recoil_propreties );
					}
				}

				if ( config.Includes.nosway )
				{
					features::no_sway( held );
				}

				if ( config.Includes.nospread )
				{
					features::no_spread( held );
				}

				if ( config.Includes.nospread )
				{
					features::super_eoka( projectile, held );
				}

				static auto start = 0ll;
				if ( config.Includes.reloadindicator && held->get_is_reloading( ) )
				{
					if ( !start )
						start = std::chrono::duration_cast<std::chrono::milliseconds>( std::chrono::steady_clock::now( ).time_since_epoch( ) ).count( );

					config.Includes.m_reload_duration = held->get_reload_time( ) * 1000.00f;
					config.Includes.m_reload_time = static_cast<std::int32_t>( start + held->get_reload_time( ) * 1000.00f ) -
						std::chrono::duration_cast<std::chrono::milliseconds>( std::chrono::steady_clock::now( ).time_since_epoch( ) ).count( );
					//quick::draw_horizontal_bar(draw, 90.00f, 7.00f, { globals::m_width / 2.00f, globals::m_height / 2.00f + 125.00f }, this->m_reload_time, this->m_reload_duration);
					//DrawFilledRect(width / 1.95, height / 2.006, reloadTime * 20.f, 5, ImColor(56, 55, 55));
				}
				else
				{
					start = 0ll;
					config.Includes.m_reload_duration = 0.00f;
					config.Includes.m_reload_time = 0.00f;
				}

				if ( config.Includes.automatic )
				{
					features::automatic( held );
				}

				if ( config.Includes.noanimation && !projectile->is_valid_weapons( ) )
				{
					const auto view_model = player->get_projectile( )->get_held( )->get_view_model( )->instance( );
					view_model->set_animator( 0 ); view_model->get_bob( )->set_bobanim( 0 ); view_model->get_sway( )->set_swayanim( 0 ); view_model->get_punch( )->set_punchanim( 0 );
				}

				if ( config.Includes.instanteoka && itemname == "pistol.eoka" )
					projectile->get_held( )->instant_eoka( );

				if ( config.Includes.instantbow && itemname == "bow.hunting" )
					projectile->get_held( )->instant_bow( );

				if ( config.Includes.instantbow && itemname == "bow.compound" )
					projectile->get_held( )->instant_compound( );

				if ( config.Includes.fastshoot )
					held->repeatDelay( config.Includes.repeatdelay );
				else
					held->repeatDelay( GetWeaponRepeatDelay( itemname ) );

			}
		}
	}

	float AimFov( baseplayer *ply )
	{
		Vector2 ScreenPos;
		if ( !entityloop::camera->WorldToScreen( &entityloop::projection_matrix, ply->get_bone( bone_list::head ), &ScreenPos ) ) return 1000.f;
		return calculate_2d_distance( Vector2( config.Includes.width / 2, config.Includes.height / 2 ), ScreenPos );
	}

	std::map<std::wstring, float> bullets =
	{
		{  ( L"ammo.rifle" ), 1.0f },
		{  ( L"ammo.rifle.hv" ), 1.2f },
		{  ( L"ammo.rifle.explosive" ), 0.49f },
		{  ( L"ammo.rifle.incendiary" ), 0.55f },

		{  ( L"ammo.pistol" ), 1.0f },
		{  ( L"ammo.pistol.hv" ), 1.33333f },
		{  ( L"ammo.pistol.fire" ), 0.75f },

		{  ( L"arrow.wooden" ), 1.0f },
		{  ( L"arrow.hv" ), 1.6f },
		{  ( L"arrow.fire" ), 0.8f },
		{  ( L"arrow.bone" ), 0.9f },

		{  ( L"ammo.handmade.shell" ), 1.0f },
		{  ( L"ammo.shotgun.slug" ), 2.25f },
		{  ( L"ammo.shotgun.fire" ), 1.0f },
		{  ( L"ammo.shotgun" ), 2.25f },

		{  ( L"ammo.nailgun.nails" ), 1.f }
	};

	auto get_projectile_speed( c_projectile *projectile ) -> const float
	{
		const auto item_definition = projectile->get_item_definition( );

		if ( !item_definition )
		{
			return 300.f;
		}

		const auto shortname = item_definition->get_shortname( );

		if ( shortname.empty( ) )
		{
			return 300.f;
		}

		const auto held = projectile->get_held( );

		if ( !held )
		{
			return 300.f;
		}

		const auto primary_magazine = held->get_primary_magazine( );

		if ( !primary_magazine )
		{
			return 300.f;
		}

		const auto magazine_item_definition = primary_magazine->get_item_definition( );

		if ( !magazine_item_definition )
		{
			return 300.f;
		}

		const auto magazine_shortname = magazine_item_definition->get_shortname( );

		if ( magazine_shortname.empty( ) )
		{
			return 300.f;
		}

		if ( shortname == ( L"rifle.ak" ) )                return 360.0f * bullets[magazine_shortname];
		if ( shortname == ( L"hmlmg" ) )					 return 503 * bullets[magazine_shortname];
		else if ( shortname == ( L"rifle.lr300" ) )             return 340.2f * bullets[magazine_shortname];
		else if ( shortname == ( L"rifle.bolt" ) )              return 542.f * bullets[magazine_shortname];
		else if ( shortname == ( L"rifle.l96" ) )               return 1125.0f * bullets[magazine_shortname];
		else if ( shortname == ( L"rifle.m39" ) )               return 674.f * bullets[magazine_shortname];
		else if ( shortname == ( L"rifle.semiauto" ) )		  return 360.0f * bullets[magazine_shortname];
		else if ( shortname == ( L"lmg.m249" ) )                return 560.0f * bullets[magazine_shortname];
		else if ( shortname == ( L"smg.thompson" ) )            return 272.0f * bullets[magazine_shortname];
		else if ( shortname == ( L"smg.2" ) )					  return 240.0f * bullets[magazine_shortname];
		else if ( shortname == ( L"smg.mp5" ) )                 return 222.8f * bullets[magazine_shortname];
		else if ( shortname == ( L"pistol.python" ) )           return 300.0f * bullets[magazine_shortname];
		else if ( shortname == ( L"pistol.semiauto" ) )         return 300.0f * bullets[magazine_shortname];
		else if ( shortname == ( L"pistol.revolver" ) )         return 270.0f * bullets[magazine_shortname];
		else if ( shortname == ( L"pistol.m92" ) )              return 300.0f * bullets[magazine_shortname];
		else if ( shortname == ( L"pistol.eoka" ) )             return 90.0f * bullets[magazine_shortname];
		else if ( shortname == ( L"pistol.nailgun" ) )          return 59.85f;
		else if ( shortname == ( L"crossbow" ) )                return 88.0f * bullets[magazine_shortname];
		else if ( shortname == ( L"bow.compound" ) )            return 100.0f * bullets[magazine_shortname];
		else if ( shortname == ( L"bow.hunting" ) )             return 59.5f * bullets[magazine_shortname];
		else if ( shortname == ( L"shotgun.pump" ) )            return 100.0f * bullets[magazine_shortname];
		else if ( shortname == ( L"shotgun.spas12" ) )          return 100.0f * bullets[magazine_shortname];
		else if ( shortname == ( L"shotgun.waterpipe" ) )       return 100.0f * bullets[magazine_shortname];
		else if ( shortname == ( L"shotgun.doublebarrel" ) )    return 100.0f * bullets[magazine_shortname];

		return 300.0f;
	}

	auto predict_position( float distance, float bullet_speed, Vector3 velocity, Vector3 position ) -> Vector3
	{
		if ( distance > 0.001f )
		{
			const auto time = distance / bullet_speed; // bullet speed

			velocity.x *= 0.55f * time;
			velocity.y *= 0.55f * time;
			velocity.z *= 0.55f * time;

			position.x += velocity.x;
			position.y += velocity.y;
			position.z += velocity.z;

			position.y += ( 4.905f * time * time ) + 0.08;
		}

		return position;
	};

	float distance_cursor( Vector2 vec )
	{
		POINT p;
		if ( GetCursorPos( &p ) )
		{
			float ydist = ( vec.y - p.y );
			float xdist = ( vec.x - p.x );
			float ret = sqrt( pow( ydist, 2 ) + pow( xdist, 2 ) );
			return ret;
		}
	}
}

namespace visuals
{
	std::string string_To_UTF8( const std::string &str ) {
		int nwLen = ::MultiByteToWideChar( CP_ACP, 0, str.c_str( ), -1, NULL, 0 );
		wchar_t *pwBuf = new wchar_t[nwLen + 1];
		ZeroMemory( pwBuf, nwLen * 2 + 2 );
		::MultiByteToWideChar( CP_ACP, 0, str.c_str( ), str.length( ), pwBuf, nwLen );
		int nLen = ::WideCharToMultiByte( CP_UTF8, 0, pwBuf, -1, NULL, NULL, NULL, NULL );
		char *pBuf = new char[nLen + 1];
		ZeroMemory( pBuf, nLen + 1 );
		::WideCharToMultiByte( CP_UTF8, 0, pwBuf, nwLen, pBuf, nLen, NULL, NULL );
		std::string retStr( pBuf );
		delete[]pwBuf;
		delete[]pBuf;
		pwBuf = NULL;
		pBuf = NULL;
		return retStr;
	}

	void StrokeText( int x, int y, ImColor color, std::string str ) {
		ImFont a;
		std::string utf_8_1 = std::string( str );
		std::string utf_8_2 = string_To_UTF8( utf_8_1 );
		ImGui::GetBackgroundDrawList( )->AddText( ImVec2( x, y - 1 ), ImGui::ColorConvertFloat4ToU32( ImVec4( 1 / 255.0, 1 / 255.0, 1 / 255.0, 255 / 255.0 ) ), utf_8_2.c_str( ) );
		ImGui::GetBackgroundDrawList( )->AddText( ImVec2( x, y + 1 ), ImGui::ColorConvertFloat4ToU32( ImVec4( 1 / 255.0, 1 / 255.0, 1 / 255.0, 255 / 255.0 ) ), utf_8_2.c_str( ) );
		ImGui::GetBackgroundDrawList( )->AddText( ImVec2( x - 1, y ), ImGui::ColorConvertFloat4ToU32( ImVec4( 1 / 255.0, 1 / 255.0, 1 / 255.0, 255 / 255.0 ) ), utf_8_2.c_str( ) );
		ImGui::GetBackgroundDrawList( )->AddText( ImVec2( x + 1, y ), ImGui::ColorConvertFloat4ToU32( ImVec4( 1 / 255.0, 1 / 255.0, 1 / 255.0, 255 / 255.0 ) ), utf_8_2.c_str( ) );
		ImGui::GetBackgroundDrawList( )->AddText( ImVec2( x, y ), color, utf_8_2.c_str( ) );
	}

	void FilledRect( int x, int y, int w, int h, ImColor color )
	{
		ImGui::GetBackgroundDrawList( )->AddRectFilled( ImVec2( x, y ), ImVec2( x + w, y + h ), color, 0, 0 );
	}

	void Line( ImVec2 pos, ImVec2 size, ImU32 color, float thickness )
	{
		ImGui::GetBackgroundDrawList( )->AddLine( pos, size, color, thickness );
	}

	void DrawHealthBar( baseplayer *player, float health, Vector2 Size, Vector2 Box, Vector2 BoxTop, ImDrawList *GUI ) {
		/*
		Vector3 head = ( player->get_bone( bone_list::head ) + Vector3( 0, 0.2, 0 ) );
		Vector3 feet = ( player->get_bone( bone_list::l_foot ) + player->get_bone( bone_list::r_foot ) ) / 2.f;
		Vector2 tempFeet, tempHead;

		GUI->AddRectFilled( { Box.x + Size.y / 4 + 5, BoxTop.y }, { Box.x + Size.y / 4 + 5, Box.y + 3 }, ImColor( 80, 80, 80, 160 ) );*/


		//if ( entityloop::camera->WorldToScreen( &entityloop::projection_matrix, head, &tempHead ) && entityloop::camera->WorldToScreen( &entityloop::projection_matrix, feet, &tempFeet ) ) {
		//	float height = ( tempHead.y - tempFeet.y );
		//	float width = height / 4.0f;

		//	float Entity_x = tempFeet.x - width;
		//	float Entity_y = tempFeet.y;
		//	float flBoxes = std::ceil( health / 10.f );
		//	float flX = Entity_x + 4; float flY = Entity_y;
		//	float flHeight = height / 10.f;
		//	float flMultiplier = 12 / 360.f; flMultiplier *= flBoxes - 1;
		//	Color ColHealth = Color::FromHSB( flMultiplier, 1, 1 );

		//	StrokeText( flX, flY, ImColor( 255, 255, 255, 255 ), std::to_string( (int)health ) );

		//	FilledRect( flX + 1, flY, 2, flHeight * flBoxes + 1, ImColor( ColHealth.R, ColHealth.G, ColHealth.B, ColHealth.A ) );
		//	FilledRect( flX, flY, 4, height + 2, ImColor( 80, 80, 80, 160 ) );
		//	//for ( int i = 0; i < 10; i++ )
		//	//	Line ( ImVec2 ( flX, flY + i * flHeight ), ImVec2 ( flX + 4, flY + i * flHeight ), ImColor ( 0, 0, 0, 255 ), 1.5f );
		//}
	}

	auto chams( baseplayer *player, c_tod_sky *tod_sky )
	{
		const auto tod_components = tod_sky->get_tod_components( );

		if ( !tod_components )
		{
			return;
		}

		const auto tod_scattering = tod_components->get_scattering( );

		if ( !tod_scattering )
		{
			return;
		}

		const auto material = tod_scattering->get_material( );

		if ( !material )
		{
			return;
		}

		const auto model = player->player_model( );

		if ( !model )
		{
			return;
		}

		const auto skin = ( model->get_skin_type( ) == 1 ? model->female_skin( ) : model->male_skin( ) );

		if ( !skin )
		{
			return;
		}

		const auto skin_set = skin->get_skin_set( );

		if ( !skin_set )
		{
			return;
		}

		for ( std::uint8_t i = 0; i < skin_set->size( ); i++ )
		{
			const auto set = skin_set->get( i );

			if ( !set )
			{
				continue;
			}

			set->set_eye_material( material );
			set->set_head_material( material );
			set->set_body_material( material );
		}
	}

	void draw_loop( )
	{
		ImDrawList *gui = ImGui::GetBackgroundDrawList( );

		for ( auto &player : rainy.player_list )
		{
			if ( player->player_model( )->is_npc( ) )
				continue;

			if ( player->player_model( )->is_local( ) )
				continue;

			if ( player->isDead( ) )
				continue;

			if ( player->player_model( )->position( ) == Vector3( 0, 0, 0 ) )
				continue;

			if ( player->HasFlags( 16 ) )
				continue;

			float w = 4;
			bones_t bones = player->get_bones( );
			Vector2 top, bottom, size;
			Vector3 player_centre = ( bones.left_ankle + bones.right_ankle ) / 2;

			int distance = rainy.player->get_bones( ).head.distance( player->get_bones( ).head );
			int health = player->health( );
			const auto projectile = player->get_projectile( );
			std::string itemname = projectile->get_item_name( );
			if ( entityloop::camera->WorldToScreen( &entityloop::projection_matrix, { bones.head.x, bones.head.y + 0.25f, bones.head.z }, &top ) )
			{
				if ( entityloop::camera->WorldToScreen( &entityloop::projection_matrix, { player_centre.x, player_centre.y - 0.35f, player_centre.z }, &bottom ) )
				{
					if ( distance < config.Includes.playerdistance )
					{
						if ( config.Includes.esp )
						{
							size = { ( bottom.y - top.y ) / 2 , bottom.y - top.y };
							if ( config.Includes.name )
							{
								std::string utf_8_1 = string_To_UTF8( player->display_name( ) );
								gui->AddText( { top.x - ( ImGui::CalcTextSize( utf_8_1.c_str( ) ).x / 2 ), top.y - 14 }, ImColor( 0, 0, 0 ), utf_8_1.c_str( ) );
								gui->AddText( { top.x - ( ImGui::CalcTextSize( utf_8_1.c_str( ) ).x / 2 ), top.y - 14 }, ImColor( 255, 255, 255 ), utf_8_1.c_str( ) );
							}
							if ( config.Includes.boxesp )
							{
								gui->AddRect( { top.x - size.y / w , top.y }, { bottom.x + size.y / w, bottom.y + 3 }, ImColor( 1, 1, 1, 255 ), 0, 0, 3 );
								gui->AddRect( { top.x - size.y / w , top.y }, { bottom.x + size.y / w, bottom.y + 3 }, ImColor( 255, 255, 255, 255 ), 0, 0, 1 );
							}
							if ( config.Includes.distance )
							{
								std::string distanceStr = "[M]" + std::to_string( distance );
								std::string utf_8_1 = string_To_UTF8( distanceStr );
								gui->AddText( { top.x - ( ImGui::CalcTextSize( utf_8_1.c_str( ) ).x / 2 ), top.y - 24 }, ImColor( 0, 0, 0 ), utf_8_1.c_str( ) );
								gui->AddText( { top.x - ( ImGui::CalcTextSize( utf_8_1.c_str( ) ).x / 2 ), top.y - 24 }, ImColor( 255, 255, 255 ), utf_8_1.c_str( ) );
							}
							if ( config.Includes.health )
							{
								//std::string healthStr = "[HP]" + std::to_string ( health );
								//std::string utf_8_1 = string_To_UTF8 ( healthStr );
								//gui->AddText ( { top.x - (ImGui::CalcTextSize ( utf_8_1.c_str ( ) ).x / 2), top.y - 34 }, ImColor ( 0, 0, 0 ), utf_8_1.c_str ( ) );
								//gui->AddText ( { top.x - (ImGui::CalcTextSize ( utf_8_1.c_str ( ) ).x / 2), top.y - 34 }, ImColor ( 255, 255, 255 ), utf_8_1.c_str ( ) );
								//DrawHealthBar( player, health, size, bottom, top, gui);

								//float BoxHeight = bottom.x - top.y;
								float BoxHeight = size.y;
								float HealthPosVal = ( BoxHeight - ( BoxHeight * float( (float)health / 100.f ) ) );

								gui->AddRectFilled( { bottom.x + size.y / w + 5, top.y }, { bottom.x + size.y / w + 8, bottom.y + 3 }, ImColor( 80, 80, 80, 160 ) );

								gui->AddRectFilled( { bottom.x + size.y / w + 6, top.y + HealthPosVal }, { bottom.x + size.y / w + 7, bottom.y + 3 }, ImColor( 0, 255, 0, 255 ) );
							}

							if ( config.Includes.weapon )
							{
								std::string  utf_8_1 = string_To_UTF8( itemname );
								gui->AddText( { bottom.x - ( ImGui::CalcTextSize( utf_8_1.c_str( ) ).x / 2 ), bottom.y + 12 }, ImColor( 0, 0, 0 ), utf_8_1.c_str( ) );
								gui->AddText( { bottom.x - ( ImGui::CalcTextSize( utf_8_1.c_str( ) ).x / 2 ), bottom.y + 12 }, ImColor( 255, 255, 255 ), utf_8_1.c_str( ) );
							}
							if ( config.Includes.snaplines )
							{
								gui->AddLine( ImVec2( config.Includes.width / 2, config.Includes.height / 2 ), ImVec2( bottom.x, bottom.y ), ImColor( 255, 255, 255 ), 1.f );
							}

							if ( config.Includes.chams )
							{
								chams(player, entityloop::tod_sky );
								player->needs_clothes_rebuild( true );
							}

							if ( config.Includes.fillrect )
							{
								gui->AddRectFilled( { top.x - size.y / w , top.y }, { bottom.x + size.y / w, bottom.y + 3 }, ImColor( 80, 80, 80, 160 ) );

							}

						}
					}
				}
			}
		}
	}

	void draw_prefab_loop( )
	{
		ImDrawList *gui = ImGui::GetBackgroundDrawList( );

		for ( auto &prefab : rainy.prefab_list )
		{
			if ( config.Includes.prefabesp )
			{
				auto position_2d = Vector2( );

				if ( entityloop::camera->WorldToScreen( &entityloop::projection_matrix, std::get<0>( prefab ), &position_2d ) )
				{
					if ( selected )
					{
						auto local_head_3d = rainy.player->get_bone( head );

						const auto distance = std::get<0>( prefab ).distance( local_head_3d );
						std::string distanceStr = " [M]" + std::to_string( (int)distance );

						std::string utf_8_1 = string_To_UTF8( std::get<1>( prefab ) + distanceStr );
						gui->AddText( { position_2d.x - ( ImGui::CalcTextSize( utf_8_1.c_str( ) ).x / 2 ), position_2d.y }, ImColor( 0, 0, 0 ), utf_8_1.c_str( ) );
						gui->AddText( { position_2d.x - ( ImGui::CalcTextSize( utf_8_1.c_str( ) ).x / 2 ), position_2d.y }, ImColor( 255, 255, 255 ), utf_8_1.c_str( ) );
					}
				}
			}
		}
	}
}

static int aimBone;
const char *aimBoneStr[5]{
	"Head",
	"Neck",
	"Body",
	"Pelivs",
	"Nearest"
};

namespace loops
{
	auto fast_loop( ) -> void
	{
		while ( true )
		{
			if ( !rainy.player )
			{
				continue;
			}

			features::quick_process( rainy.player );
		}
	}

	auto tod_sky( ) -> void
	{
		while ( true )
		{
			if ( !rainy.player )
			{
				continue;
			}

			features::tod_sky( rainy.player );
			Sleep( 2 );
		}
	}

	Vector3 aimbone;
	bool docross = true;

	auto aimbot_loop( ) -> void
	{
		while ( true )
		{
			for ( auto &ply : rainy.player_list )
			{
				if ( ply->player_model( )->is_npc( ) )
					continue;

				if ( ply->player_model( )->is_local( ) )
					continue;

				if ( ply->isDead( ) )
					continue;

				if ( ply->player_model( )->position( ) == Vector3( 0, 0, 0 ) )
					continue;

				if ( ply->HasFlags( 16 ) )
					continue;

				if ( !ply->player_model( )->IsVisible( ) )
					continue;

				float distance = rainy.player->player_model( )->position( ).distance( ply->player_model( )->position( ) );
				std::string helditem = entityloop::held_item->get_item_name( );
				std::string displayName = ply->display_name( );
				float health = ply->health( );
				Vector2 center = { (float)config.Includes.width / 2, (float)config.Includes.height / 2 };

				if ( features::AimFov( ply ) < config.Includes.aimfov )
				{
					docross = true;
					const auto projectile = rainy.player->get_projectile( );
					if ( aimBone == 0 )
						aimbone = features::predict_position( distance, features::get_projectile_speed( projectile ), ply->player_model( )->NewVelocity( ), ply->get_bone( head ) );
					if ( aimBone == 1 )
						aimbone = features::predict_position( distance, features::get_projectile_speed( projectile ), ply->player_model( )->NewVelocity( ), ply->get_bone( neck ) );
					if ( aimBone == 2 )
						aimbone = features::predict_position( distance, features::get_projectile_speed( projectile ), ply->player_model( )->NewVelocity( ), ply->get_bone( spine1 ) );
					if ( aimBone == 3 )
						aimbone = features::predict_position( distance, features::get_projectile_speed( projectile ), ply->player_model( )->NewVelocity( ), ply->get_bone( pelvis ) );
					if ( aimBone == 4 )
					{
						Vector3 head = ply->get_bone( bone_list::head );
						Vector2 head_screen{};

						if ( !entityloop::camera->WorldToScreen( &entityloop::projection_matrix, head, &head_screen ) )
							continue;

						Vector3 body = ply->get_bone( bone_list::pelvis );
						Vector2 body_screen{};

						if ( !entityloop::camera->WorldToScreen( &entityloop::projection_matrix, body, &body_screen ) )
							continue;

						float body_distance = body_screen.distance( center );
						float head_distance = head_screen.distance( center );

						if ( body_distance < head_distance )
							aimbone = features::predict_position( distance, features::get_projectile_speed( projectile ), ply->player_model( )->NewVelocity( ), ply->get_bone( pelvis ) );

						if ( head_distance < body_distance )
							aimbone = features::predict_position( distance, features::get_projectile_speed( projectile ), ply->player_model( )->NewVelocity( ), ply->get_bone( neck ) );
					}
					if ( config.Includes.aimbot )
					{
						if ( GetAsyncKeyState( VK_XBUTTON2 ) )
						{
							rainy.player->player_input( )->set_view_angles( calculate_angle( entityloop::camera->position( ), aimbone ) );
						}
					}
					else if ( config.Includes.silentaim )
					{

						if ( GetAsyncKeyState( VK_LBUTTON ) )
						{
							rainy.player->player_eyes( )->look_at( calculate_angle( entityloop::camera->position( ), aimbone ) );
						}
					}
				}
			}
			Sleep( 1 );
		}
	}

	auto self_loop( ) -> void
	{
		while ( true )
		{
			if ( !rainy.player )
			{
				continue;
			}

			if ( !get_process_id( "RustClient.exe" ) )
				exit( 0 );

			features::process( rainy.player );
			Sleep( 20 );
		}
	}
}

auto LoopSetup( ) -> void
{
	std::thread( [&]( ) { entityloop::get_list( ); } ).detach( );
	std::thread( [&]( ) { entityloop::get_instances( ); } ).detach( );
	std::thread( [&]( ) { entityloop::get_camera_fields( ); } ).detach( );
	//Sleep( 150 );
	std::thread( [&]( ) { loops::self_loop( ); } ).detach( );
	std::thread( [&]( ) { loops::fast_loop( ); } ).detach( );
	std::thread( [&]( ) { loops::tod_sky( ); } ).detach( );
	std::thread( [&]( ) { features::silent_walk; } ).detach( );
	std::thread( [&]( ) { loops::aimbot_loop( ); } ).detach( );
}