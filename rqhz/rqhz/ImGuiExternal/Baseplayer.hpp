#pragma once
#include "Imports.hpp"

using namespace Offsets;

static enum ModelStateFlags
{
	Ducked = 1,
	Jumped = 2,
	OnGround = 4,
	Sprinting = 16,
	OnLadder = 32,
	Flying = 64,
	Prone = 256,
	Mounted = 512,
	OnPhone = 2048,
	Crawling = 4096
};

static enum PlayerFlags
{
	Unused1 = 1,
	Unused2 = 2,
	IsAdmin = 4,
	ReceivingSnapshot = 8,
	Sleeping = 16,
	Spectating = 32,
	Wounded = 64,
	IsDeveloper = 128,
	Connected = 256,
	ThirdPersonViewmode = 1024,
	EyesViewmode = 2048,
	ChatMute = 4096,
	NoSprint = 8192,
	Aiming = 16384,
	DisplaySash = 32768,
	Relaxed = 65536,
	SafeZone = 131072,
	ServerFall = 262144,
	Incapacitated = 524288,
	Workbench1 = 1048576,
	Workbench2 = 2097152,
	Workbench3 = 4194304
};

enum bone_list
{
	pelvis = 1,
	l_hip = 2,
	l_knee = 3,
	l_foot = 4,
	l_toe = 5,
	l_ankle_scale = 6,
	penis = 7,
	GenitalCensor = 8,
	GenitalCensor_LOD0 = 9,
	Inner_LOD0 = 10,
	GenitalCensor_LOD1 = 11,
	GenitalCensor_LOD2 = 12,
	r_hip = 13,
	r_knee = 14,
	r_foot = 15,
	r_toe = 16,
	r_ankle_scale = 17,
	spine1 = 18,
	spine1_scale = 19,
	spine2 = 20,
	spine3 = 21,
	spine4 = 22,
	l_clavicle = 23,
	l_upperarm = 24,
	l_forearm = 25,
	l_hand = 26,
	l_index1 = 27,
	l_index2 = 28,
	l_index3 = 29,
	l_little1 = 30,
	l_little2 = 31,
	l_little3 = 32,
	l_middle1 = 33,
	l_middle2 = 34,
	l_middle3 = 35,
	l_prop = 36,
	l_ring1 = 37,
	l_ring2 = 38,
	l_ring3 = 39,
	l_thumb1 = 40,
	l_thumb2 = 41,
	l_thumb3 = 42,
	IKtarget_righthand_min = 43,
	IKtarget_righthand_max = 44,
	l_ulna = 45,
	neck = 46,
	head = 47,
	jaw = 48,
	eyeTranform = 49,
	l_eye = 50,
	l_Eyelid = 51,
	r_eye = 52,
	r_Eyelid = 53,
	r_clavicle = 54,
	r_upperarm = 55,
	r_forearm = 56,
	r_hand = 57,
	r_index1 = 58,
	r_index2 = 59,
	r_index3 = 60,
	r_little1 = 61,
	r_little2 = 62,
	r_little3 = 63,
	r_middle1 = 64,
	r_middle2 = 65,
	r_middle3 = 66,
	r_prop = 67,
	r_ring1 = 68,
	r_ring2 = 69,
	r_ring3 = 70,
	r_thumb1 = 71,
	r_thumb2 = 72,
	r_thumb3 = 73,
	IKtarget_lefthand_min = 74,
	IKtarget_lefthand_max = 75,
	r_ulna = 76,
	l_breast = 77,
	r_breast = 78,
	BoobCensor = 79,
	BreastCensor_LOD0 = 80,
	BreastCensor_LOD1 = 81,
	BreastCensor_LOD2 = 82,
	collision = 83,
	displacement = 84
};

struct bones_t
{
public:

	Vector3 head{};

	Vector3 upper_spine{};

	Vector3 left_shoulder{};
	Vector3 left_elbow{};
	Vector3 left_wrist{};

	Vector3 right_shoulder{};
	Vector3 right_elbow{};
	Vector3 right_wrist{};

	Vector3 lower_spine{};

	Vector3 left_hip{};
	Vector3 left_knee{};
	Vector3 left_ankle{};

	Vector3 right_hip{};
	Vector3 right_knee{};
	Vector3 right_ankle{};
};

struct transform_access_read_only_t
{
	uint64_t transform_data{};
};

struct transform_data_t
{
	uint64_t transform_array{};
	uint64_t transform_indices{};
};

struct matrix34_t
{
	Vector4 vec0{};
	Vector4 vec1{};
	Vector4 vec2{};
};

class transform_c
{
public:
	Vector3 get_position_injected ( )
	{
		uintptr_t transform = driver->read<uintptr_t> ( reinterpret_cast<uintptr_t>(this) + 0x10 );

		__m128 result{};

		const __m128 mulVec0 = { -2.000, 2.000, -2.000, 0.000 };
		const __m128 mulVec1 = { 2.000, -2.000, -2.000, 0.000 };
		const __m128 mulVec2 = { -2.000, -2.000, 2.000, 0.000 };

		transform_access_read_only_t transform_access_read_only = driver->read<transform_access_read_only_t> ( transform + 0x38 );
		unsigned int index = driver->read<unsigned int> ( transform + 0x40 );
		transform_data_t transform_data = driver->read<transform_data_t> ( transform_access_read_only.transform_data + 0x18 );

		if ( transform_data.transform_array && transform_data.transform_indices )
		{
			result = driver->read<__m128> ( transform_data.transform_array + 0x30 * index );
			int transform_index = driver->read<int> ( transform_data.transform_indices + 0x4 * index );
			int safe = 0;
			while ( transform_index >= 0 && safe++ < 200 )
			{
				matrix34_t matrix = driver->read<matrix34_t> ( transform_data.transform_array + 0x30 * transform_index );

				__m128 xxxx = _mm_castsi128_ps ( _mm_shuffle_epi32 ( *(__m128i*)(&matrix.vec1), 0x00 ) );	// xxxx
				__m128 yyyy = _mm_castsi128_ps ( _mm_shuffle_epi32 ( *(__m128i*)(&matrix.vec1), 0x55 ) );	// yyyy
				__m128 zwxy = _mm_castsi128_ps ( _mm_shuffle_epi32 ( *(__m128i*)(&matrix.vec1), 0x8E ) );	// zwxy
				__m128 wzyw = _mm_castsi128_ps ( _mm_shuffle_epi32 ( *(__m128i*)(&matrix.vec1), 0xDB ) );	// wzyw
				__m128 zzzz = _mm_castsi128_ps ( _mm_shuffle_epi32 ( *(__m128i*)(&matrix.vec1), 0xAA ) );	// zzzz
				__m128 yxwy = _mm_castsi128_ps ( _mm_shuffle_epi32 ( *(__m128i*)(&matrix.vec1), 0x71 ) );	// yxwy
				__m128 tmp7 = _mm_mul_ps ( *(__m128*)(&matrix.vec2), result );

				result = _mm_add_ps ( _mm_add_ps (
					_mm_add_ps (
						_mm_mul_ps (
							_mm_sub_ps (
								_mm_mul_ps ( _mm_mul_ps ( xxxx, mulVec1 ), zwxy ),
								_mm_mul_ps ( _mm_mul_ps ( yyyy, mulVec2 ), wzyw ) ),
							_mm_castsi128_ps ( _mm_shuffle_epi32 ( _mm_castps_si128 ( tmp7 ), 0xAA ) ) ),
						_mm_mul_ps (
							_mm_sub_ps (
								_mm_mul_ps ( _mm_mul_ps ( zzzz, mulVec2 ), wzyw ),
								_mm_mul_ps ( _mm_mul_ps ( xxxx, mulVec0 ), yxwy ) ),
							_mm_castsi128_ps ( _mm_shuffle_epi32 ( _mm_castps_si128 ( tmp7 ), 0x55 ) ) ) ),
					_mm_add_ps (
						_mm_mul_ps (
							_mm_sub_ps (
								_mm_mul_ps ( _mm_mul_ps ( yyyy, mulVec0 ), yxwy ),
								_mm_mul_ps ( _mm_mul_ps ( zzzz, mulVec1 ), zwxy ) ),
							_mm_castsi128_ps ( _mm_shuffle_epi32 ( _mm_castps_si128 ( tmp7 ), 0x00 ) ) ),
						tmp7 ) ), *(__m128*)(&matrix.vec0) );

				transform_index = driver->read<int>( transform_data.transform_indices + 0x4 * transform_index );
			}
		}

		return Vector3 ( result.m128_f32[0], result.m128_f32[1], result.m128_f32[2] );
	}
};

class c_itemdefinition
{
public:

	auto get_shortname ( ) -> const std::wstring
	{
		const auto shortname = driver->read<std::uintptr_t> ( reinterpret_cast<std::uintptr_t> (this) + 0x20 );

		if ( !shortname )
		{
			return std::wstring ( );
		}

		const auto buffer = std::make_unique<wchar_t[]> ( 64 );

		driver->read ( shortname + 0x14, buffer.get ( ), 64 * sizeof ( wchar_t ) );

		return std::wstring ( buffer.get ( ) );
	}
};

class Admin {
public:

	auto admintime ( float d ) -> void
	{
		driver->write<float> ( (const uintptr_t)this + 0x0, d );
	}
};

class ConVars {
public:

	static auto convar_admin ( ) -> Admin*
	{
		DWORD64 convar = driver->read<DWORD64> ( game_assembly + m_convar_admin_c );
		return(Admin*)driver->read<DWORD64> ( convar + 0xb8 );
	}
};

class weaponbob {
public:

	void set_bobanim ( float n )
	{
		driver->write<uint64_t> ( reinterpret_cast<uintptr_t>(this) + 0x18, n ); // bob
		driver->write<uint64_t> ( reinterpret_cast<uintptr_t>(this) + 0x1c, n ); // bob
		driver->write<uint64_t> ( reinterpret_cast<uintptr_t>(this) + 0x20, n ); // bob
		driver->write<uint64_t> ( reinterpret_cast<uintptr_t>(this) + 0x24, n ); // bob
	}
};

class weaponsway {
public:

	void set_swayanim ( float n )
	{
		driver->write<uint64_t> ( reinterpret_cast<uintptr_t>(this) + Offsets::Classes::ViewmodelSway::positionalSwaySpeed, n ); // sway
		driver->write<uint64_t> ( reinterpret_cast<uintptr_t>(this) + Offsets::Classes::ViewmodelSway::rotationSwayAmount, n ); // sway
	}
};

class weaponpunch {
public:

	void set_punchanim ( float n )
	{
		driver->write<uint64_t> ( reinterpret_cast<uintptr_t>(this) + Offsets::Classes::ViewmodelPunch::punchDuration, n ); // sway
		driver->write<uint64_t> ( reinterpret_cast<uintptr_t>(this) + Offsets::Classes::ViewmodelPunch::punchMagnitude, n ); // sway
	}
};

class weaponviewmodel
{
public:

	void set_animator ( int n )
	{
		driver->write<uintptr_t> ( reinterpret_cast<uintptr_t>(this) + Offsets::Classes::BaseViewModel::animator, n ); // Instance
	}

	auto get_bob ( ) -> weaponbob*
	{
		return driver->read<weaponbob*> ( reinterpret_cast<uintptr_t>(this) + Offsets::Classes::BaseViewModel::bob ); // Instance
	}

	auto get_sway ( ) -> weaponsway*
	{
		return driver->read<weaponsway*> ( reinterpret_cast<uintptr_t>(this) + Offsets::Classes::BaseViewModel::sway ); // Instance
	}

	auto get_punch ( ) -> weaponpunch*
	{
		return driver->read<weaponpunch*> ( reinterpret_cast<uintptr_t>(this) + Offsets::Classes::BaseViewModel::punch ); // Instance
	}
};

class baseviewmodel
{
public:

	auto instance ( ) -> weaponviewmodel*
	{
		return driver->read<weaponviewmodel*> ( reinterpret_cast<uintptr_t>(this) + 0x28 ); // Instance
	}
};

class c_primary_magazine
{
public:

	auto get_item_definition ( ) -> c_itemdefinition*
	{
		return driver->read<c_itemdefinition*> ( reinterpret_cast<std::uintptr_t>(this) + m_item_definition );
	}
};

class c_new_recoil_override
{
public:

	auto set_time_to_take_max ( const float time ) -> void
	{
		driver->write<float> ( reinterpret_cast<std::uintptr_t> (this) + Classes::RecoilProperties::timeToTakeMax, time );
	}

	auto set_aimcone_curve_scale ( const float scale ) -> void
	{
		driver->write<float> ( reinterpret_cast<std::uintptr_t> (this) + Classes::RecoilProperties::aimconeCurveScale, scale );
	}

	auto get_time_to_take_max ( ) -> const float
	{
		return driver->read<float> ( reinterpret_cast<std::uintptr_t> (this) + Classes::RecoilProperties::timeToTakeMax );
	}

	auto get_aimcone_curve_scale ( ) -> const float
	{
		return driver->read<float> ( reinterpret_cast<std::uintptr_t> (this) + Classes::RecoilProperties::aimconeCurveScale );
	}

	auto set_recoil_yaw_min ( const float min ) -> void
	{
		driver->write<float> ( reinterpret_cast<std::uintptr_t> (this) + Classes::RecoilProperties::recoilYawMin, min );
	}

	auto set_recoil_yaw_max ( const float max ) -> void
	{
		driver->write<float> ( reinterpret_cast<std::uintptr_t> (this) + Classes::RecoilProperties::recoilYawMax, max );
	}

	auto set_recoil_pitch_min ( const float min ) -> void
	{
		driver->write<float> ( reinterpret_cast<std::uintptr_t> (this) + Classes::RecoilProperties::recoilPitchMin, min );
	}

	auto set_recoil_pitch_max ( const float max ) -> void
	{
		driver->write<float> ( reinterpret_cast<std::uintptr_t> (this) + Classes::RecoilProperties::recoilPitchMax, max );
	}
};

class c_recoil_properties
{
public:

	auto set_time_to_take_max ( const float time ) -> void
	{
		driver->write<float> ( reinterpret_cast<std::uintptr_t> (this) + Classes::RecoilProperties::timeToTakeMax, time );
	}

	auto set_aimcone_curve_scale ( const float scale ) -> void
	{
		driver->write<float> ( reinterpret_cast<std::uintptr_t> (this) + Classes::RecoilProperties::aimconeCurveScale, scale );
	}

	auto set_recoil_yaw_min ( const float min ) -> void
	{
		driver->write<float> ( reinterpret_cast<std::uintptr_t> (this) + Classes::RecoilProperties::recoilYawMin, min );
	}

	auto set_recoil_yaw_max ( const float max ) -> void
	{
		driver->write<float> ( reinterpret_cast<std::uintptr_t> (this) + Classes::RecoilProperties::recoilYawMax, max );
	}

	auto set_recoil_pitch_min ( const float min ) -> void
	{
		driver->write<float> ( reinterpret_cast<std::uintptr_t> (this) + Classes::RecoilProperties::recoilPitchMin, min );
	}

	auto set_recoil_pitch_max ( const float max ) -> void
	{
		driver->write<float> ( reinterpret_cast<std::uintptr_t> (this) + Classes::RecoilProperties::recoilPitchMax, max );
	}

	auto get_new_recoil_override ( ) -> c_new_recoil_override*
	{
		return driver->read<c_new_recoil_override*> ( reinterpret_cast<std::uintptr_t>(this) + Classes::RecoilProperties::newRecoilOverride );
	}
};

class c_held
{
public:

	auto get_view_model ( ) -> baseviewmodel*
	{
		return driver->read<baseviewmodel*> ( reinterpret_cast<uintptr_t>(this) + Offsets::Classes::HeldEntity::viewModel ); // HeldEntity : viewModel
	}

	auto set_did_spark_this_time ( const bool sparked ) -> auto
	{
		driver->write<float> ( reinterpret_cast<std::uintptr_t>(this) + Classes::FlintStrikeWeapon::_didSparkThisFrame, sparked );
	}

	auto set_success_fraction ( const float fraction ) -> auto
	{
		driver->write<float> ( reinterpret_cast<std::uintptr_t>(this) + Classes::FlintStrikeWeapon::successFraction, fraction );
	}

	auto set_aimcone ( const float aimcone ) -> void
	{
		driver->write<float> ( reinterpret_cast<std::uintptr_t> (this) + Classes::BaseProjectile::aimCone, aimcone );
	}

	auto set_hip_aimcone ( const float aimcone ) -> void
	{
		driver->write<float> ( reinterpret_cast<std::uintptr_t> (this) + Classes::BaseProjectile::hipAimCone, aimcone );
	}

	auto set_aimcone_penalty_per_shot ( const float penalty ) -> void
	{
		driver->write<float> ( reinterpret_cast<std::uintptr_t> (this) + Classes::BaseProjectile::aimconePenaltyPerShot, penalty );
	}

	auto set_aimcone_penalty_max ( const float penalty ) -> void
	{
		driver->write<float> ( reinterpret_cast<std::uintptr_t> (this) + Classes::BaseProjectile::aimConePenaltyMax, penalty );
	}

	auto set_aimcone_penalty_recover_time ( const float penalty ) -> void
	{
		driver->write<float> ( reinterpret_cast<std::uintptr_t> (this) + Classes::BaseProjectile::aimconePenaltyRecoverTime, penalty );
	}

	auto set_aimcone_penalty_recover_delay ( const float penalty ) -> void
	{
		driver->write<float> ( reinterpret_cast<std::uintptr_t> (this) + Classes::BaseProjectile::aimconePenaltyRecoverDelay, penalty );
	}

	auto set_aim_sway ( const float sway ) -> void
	{
		driver->write<float> ( reinterpret_cast<std::uintptr_t> (this) + Classes::BaseProjectile::aimSway, sway );
	}

	auto set_stance_penalty ( const float penalty ) -> void
	{
		driver->write<float> ( reinterpret_cast<std::uintptr_t> (this) + Classes::BaseProjectile::stancePenalty, penalty );
	}

	auto set_aimcone_penalty ( const float penalty ) -> void
	{
		driver->write<float> ( reinterpret_cast<std::uintptr_t> (this) + Classes::BaseProjectile::aimconePenalty, penalty );
	}

	auto set_sight_aimcone_scale ( const float scale ) -> void
	{
		driver->write<float> ( reinterpret_cast<std::uintptr_t> (this) + Classes::BaseProjectile::sightAimConeScale, scale );
	}

	auto set_sight_aimcone_offset ( const float offset ) -> void
	{
		driver->write<float> ( reinterpret_cast<std::uintptr_t> (this) + Classes::BaseProjectile::sightAimConeOffset, offset );
	}

	auto set_hip_aimcone_scale ( const float scale ) -> void
	{
		driver->write<float> ( reinterpret_cast<std::uintptr_t> (this) + Classes::BaseProjectile::hipAimConeScale, scale );
	}

	auto set_hip_aimcone_offset ( const float offset ) -> void
	{
		driver->write<float> ( reinterpret_cast<std::uintptr_t> (this) + Classes::BaseProjectile::hipAimConeOffset, offset );
	}

	auto set_aim_sway_speed ( const float speed ) -> void
	{
		driver->write<float> ( reinterpret_cast<std::uintptr_t> (this) + Classes::BaseProjectile::aimSwaySpeed, speed );
	}

	auto get_primary_magazine ( ) -> c_primary_magazine*
	{
		return driver->read<c_primary_magazine*> ( reinterpret_cast<std::uintptr_t> (this) + Classes::BaseProjectile::primaryMagazine );
	}

	auto get_reload_time ( ) -> float
	{
		return driver->read<float> ( (const uintptr_t)this + Offsets::Classes::BaseProjectile::reloadTime );
	}

	void repeatDelay ( float d )
	{
		driver->write<float> ( (const uintptr_t)this + Offsets::Classes::AttackEntity::repeatDelay, d );
	}

	float getrepeatDelay ( )
	{
		return driver->read<float> ( (const uintptr_t)this + Offsets::Classes::AttackEntity::repeatDelay );
	}

	auto instant_eoka ( ) -> void
	{
		driver->write<float> ( reinterpret_cast<uintptr_t>(this) + Offsets::Classes::FlintStrikeWeapon::successFraction, 100.f );//successFraction
		driver->write<bool> ( reinterpret_cast<uintptr_t>(this) + Offsets::Classes::FlintStrikeWeapon::_didSparkThisFrame, true );//_didSparkThisFrame
		driver->write<int> ( reinterpret_cast<uintptr_t>(this) + Offsets::Classes::FlintStrikeWeapon::strikes, 1 );//strikes
	}

	auto automatic ( ) -> void
	{
		driver->write<bool> ( reinterpret_cast<uintptr_t>(this) + Offsets::Classes::BaseProjectile::automatic, true ); //automatic
	}

	auto instant_bow ( ) -> void
	{
		driver->write<bool> ( reinterpret_cast<uintptr_t>(this) + Offsets::Classes::BowWeapon::attackReady, true ); //attackReady
	}

	auto set_auto_burst( int d) -> void
	{
		driver->write<int>( reinterpret_cast<uintptr_t>( this ) + Offsets::Classes::AttackEntity::CurrentBurst, d );

	}

	auto instant_compound ( )-> void
	{
		driver->write<float> ( reinterpret_cast<uintptr_t>(this) + Offsets::Classes::CompoundBowWeapon::stringHoldDurationMax, 0 );//stringHoldDurationMax
		driver->write<float> ( reinterpret_cast<uintptr_t>(this) + Offsets::Classes::CompoundBowWeapon::stringBonusDamage, 1000000 );//stringBonusDamage
		driver->write<float> ( reinterpret_cast<uintptr_t>(this) + Offsets::Classes::CompoundBowWeapon::movementPenaltyRampUpTime, 1000000 );//movementPenaltyRampUpTime
	}

	auto get_is_reloading ( ) -> bool
	{
		bool Reloading = driver->read<bool> ( reinterpret_cast<uintptr_t>(this) + Offsets::Classes::BaseProjectile::isReloading );
		return Reloading;
	}


	auto get_recoil_propreties ( ) -> c_recoil_properties*
	{
		return driver->read<c_recoil_properties*> ( reinterpret_cast<std::uintptr_t>(this) + Classes::BaseProjectile::recoil );
	}

	auto get_created_projectiles ( void (*each)(std::uintptr_t) ) -> void
	{
		const auto list = driver->read<std::uintptr_t> ( reinterpret_cast<std::uintptr_t>(this) + Classes::BaseProjectile::createdProjectiles );

		if ( !list )
		{
			return;
		}

		const auto key = driver->read<std::uintptr_t> ( list + 0x10 );

		if ( !key )
		{
			return;
		}

		const auto size = driver->read<int> ( list + 0x18 );

		if ( !size )
		{
			return;
		}

		for ( int i = 0; i < size; ++i )
		{
			const auto projectile = driver->read<std::uintptr_t> ( key + 0x20 + (i * 0x8) );

			if ( !projectile )
			{
				continue;
			}

			each ( projectile );
		}
	}

	auto current_velocity( float d ) -> void
	{
		driver->write<float>( reinterpret_cast<std::uintptr_t>( this ) + Classes::BaseProjectile::projectileVelocityScale, d );
	}

};

class c_item_definition
{
public:

	auto get_shortname ( ) -> const std::wstring
	{
		const auto shortname = driver->read<std::uintptr_t> ( reinterpret_cast<std::uintptr_t> (this) + Classes::ItemDefinition::shortname );

		if ( !shortname )
		{
			return std::wstring ( );
		}

		const auto buffer = std::make_unique<wchar_t[]> ( 64 );

		driver->read ( shortname + 0x14, buffer.get ( ), 64 * sizeof ( wchar_t ) );

		return std::wstring ( buffer.get ( ) );
	}
};

class c_item_projectile_mod
{
public:

	auto set_projectile_spread ( const float spread ) -> void
	{
		driver->write<float> ( reinterpret_cast<std::uintptr_t>(this) + m_projectile_spread, spread );
	}

	auto set_projectile_velocity_spread ( const float spread ) -> void
	{
		driver->write<float> ( reinterpret_cast<std::uintptr_t>(this) + m_projectile_velocity_spread, spread );
	}
};

class c_hit_test
{
public:
	auto did_hit ( ) -> bool
	{
		bool didhit = driver->read<bool> ( reinterpret_cast<uintptr_t>(this) + Classes::HitTest::DidHit );
		return didhit;
	}
};

class c_projectile
{
public:
	auto hittest ( ) -> void
	{
		c_hit_test* hittest = driver->read<c_hit_test*> ( reinterpret_cast<uintptr_t>(this) + Classes::Projectile::hitTest );
		std::cout << hittest->did_hit ( ) << std::endl;
	}

	auto get_item_name ( ) -> std::string
	{
		uint64_t info = driver->read<uint64_t> ( reinterpret_cast<uintptr_t>(this) + 0x20 );

		uint64_t display_name = driver->read<uint64_t> ( info + 0x20 );

		std::wstring wide_name = driver->read_string ( display_name + 0x14 );

		if ( !wide_name.empty ( ) )
			return std::string ( wide_name.begin ( ), wide_name.end ( ) ).c_str ( );

		return "No Item";
	}

	auto get_item_definition ( ) -> c_item_definition*
	{
		return driver->read<c_item_definition*> ( reinterpret_cast<std::uintptr_t>(this) + m_item_definition );
	}

	auto is_weapon ( ) -> bool
	{
		const auto name = this->get_item_name ( );

		if ( name.empty ( ) )
		{
			return false;
		}

		if ( name.find ( ("rifle") ) != std::string::npos )
		{
			return true;
		}

		if ( name.find ( ("pistol") ) != std::string::npos )
		{
			return true;
		}

		if ( name.find ( ("bow") ) != std::string::npos )
		{
			return true;
		}

		if ( name.find ( ("lmg") ) != std::string::npos )
		{
			return true;
		}

		if ( name.find ( ("shotgun") ) != std::string::npos )
		{
			return true;
		}

		if ( name.find ( ("smg") ) != std::string::npos )
		{
			return true;
		}

		return false;
	}

	auto is_valid_weapons ( ) -> bool
	{
		const auto name = this->get_item_name ( );

		if ( name.empty ( ) )
		{
			return false;
		}

		if ( name.find ( "bow" ) != std::string::npos )
		{
			return true;
		}

		if ( name.find ( "eoka" ) != std::string::npos )
		{
			return true;
		}

		return false;
	}

	auto is_valid_automatic ( ) -> bool
	{
		const auto name = this->get_item_name ( );

		if ( name.empty ( ) )
		{
			return false;
		}

		if ( name.find ( "bow" ) != std::string::npos )
		{
			return true;
		}

		if ( name.find ( "shotgun" ) != std::string::npos )
		{
			return true;
		}

		if ( name.find ( "eoka" ) != std::string::npos )
		{
			return true;
		}

		return false;
	}

	auto is_valid_weapon ( ) -> bool
	{
		const auto name = this->get_item_name ( );

		if ( name.empty ( ) )
		{
			return false;
		}

		if ( name.find ( "eoka" ) != std::string::npos )
		{
			return true;
		}

		return false;
	}

	auto get_uid ( ) -> int
	{
		return driver->read<int> ( reinterpret_cast<std::uintptr_t> (this) + 0x28 );
	}

	auto get_id ( ) -> int
	{
		return driver->read_chain<int> ( reinterpret_cast<std::uintptr_t> (this), { 0x20, 0x18 } );
	}

	int GetItemID ( )
	{
		UINT64 Info = driver->read<UINT64> ( (const uintptr_t)this + 0x20 );
		return driver->read<int> ( Info + 0x18 );
	}

	int UID ( )
	{
		return driver->read<int> ( (const uintptr_t)this + 0x28 );// public uint uid; //public class Item
	}

	auto get_held ( ) -> c_held*
	{
		return driver->read<c_held*> ( reinterpret_cast<std::uintptr_t>(this) + Classes::Item::heldEntity );
	}

	

};

class list_c
{
public:

	template<typename T>
	std::vector<T> data ( )
	{
		std::vector<T> temp_list{};

		uintptr_t start = driver->read<uintptr_t> ( reinterpret_cast<uintptr_t>(this) + 0x10 );
		int size = driver->read<int> ( reinterpret_cast<uintptr_t>(this) + 0x18 );

		for ( int i = 0; i < size; i++ ) {
			temp_list.push_back ( driver->read<T> ( start + (0x20 + (i * 0x8)) ) );
		}

		return temp_list;
	}
};

class item_container_c
{
public:

	std::vector<c_projectile*> item_list ( )
	{
		return driver->read<list_c*> ( reinterpret_cast<uintptr_t>(this) + 0x38 )->data<c_projectile*> ( );
	}
};

class c_playerinventory
{
public:

	item_container_c* main ( )
	{
		return driver->read<item_container_c*> ( reinterpret_cast<uintptr_t>(this) + 0x20 );
	}

	item_container_c* belt ( )
	{
		return driver->read<item_container_c*> ( reinterpret_cast<uintptr_t>(this) + 0x28 );
	}

	item_container_c* wear ( )
	{
		return driver->read<item_container_c*> ( reinterpret_cast<uintptr_t>(this) + 0x30 );
	}
};

class c_playereyes
{
public:

	void look_at ( Vector2 angles )
	{
		angles.normalize ( );
		driver->write<Vector4> ( reinterpret_cast<uintptr_t>(this) + 0x44, to_quat ( { angles.x,angles.y, 0 } ) );
	}

	void ViewOffset ( Vector3 view_offset )
	{
		driver->write<Vector3> ( reinterpret_cast<uintptr_t>(this) + 0x38, view_offset );
	}
};

class c_playerinput
{
public:

	void set_view_angles ( Vector2 angles )
	{
		driver->write<Vector2> ( reinterpret_cast<uintptr_t>(this) + 0x3c, angles ); // bodyRotation
	}
};

template <typename t>
class c_array
{
public:

	auto size( ) -> const std::uint32_t
	{
		return driver->read<std::uint32_t>( reinterpret_cast<std::uintptr_t>( this ) + 0x18 );
	}

	auto get( const std::uint32_t idx ) -> t
	{
		return driver->read<t>( reinterpret_cast<std::uintptr_t>( this ) + 0x20ull + ( idx * 0x8ull ) );
	}
};

class c_skin_set
{
public:

	auto set_head_material( const std::uintptr_t material ) -> void
	{
		driver->write<std::uintptr_t>( reinterpret_cast<std::uintptr_t>( this ) + Classes::SkinSet::HeadMaterial, material );
	}

	auto set_body_material( const std::uintptr_t material ) -> void
	{
		driver->write<std::uintptr_t>( reinterpret_cast<std::uintptr_t>( this ) + Classes::SkinSet::BodyMaterial, material );
	}

	auto set_eye_material( const std::uintptr_t material ) -> void
	{
		driver->write<std::uintptr_t>( reinterpret_cast<std::uintptr_t>( this ) + Classes::SkinSet::EyeMaterial, material );
	}

	auto get_head_material( ) -> const std::uintptr_t
	{
		return driver->read<std::uintptr_t>( reinterpret_cast<std::uintptr_t>( this ) + Classes::SkinSet::HeadMaterial );
	}

	auto get_body_material( ) -> const std::uintptr_t
	{
		return driver->read<std::uintptr_t>( reinterpret_cast<std::uintptr_t>( this ) + Classes::SkinSet::BodyMaterial );
	}

	auto get_eye_material( ) -> const std::uintptr_t
	{
		return driver->read<std::uintptr_t>( reinterpret_cast<std::uintptr_t>( this ) + Classes::SkinSet::EyeMaterial );
	}
};

class c_skin
{
public:

	auto get_skin_set( ) -> c_array<c_skin_set *> *
	{
		return driver->read< c_array<c_skin_set *> *>( reinterpret_cast<std::uintptr_t>( this ) + 0x18 );
	}
};

class c_playermodel
{
public:

	bool is_local( )
	{
		return driver->read<bool>( reinterpret_cast<uintptr_t>( this ) + 0x299 );
	}

	bool is_npc( )
	{
		return driver->read<bool>( reinterpret_cast<uintptr_t>( this ) + Classes::PlayerModel::IsNpck__BackingField );
	}

	c_skin *male_skin( )
	{
		return driver->read<c_skin *>( reinterpret_cast<uintptr_t>( this ) + 0x1a0 );
	}

	c_skin *female_skin( )
	{
		return driver->read<c_skin *>( reinterpret_cast<uintptr_t>( this ) + 0x1a8 );
	}

	auto get_skin_type( ) -> int
	{
		return driver->read<int>( reinterpret_cast<std::uintptr_t>( this ) + Classes::PlayerModel::skinType );
	}

	Vector3 position( )
	{
		return driver->read<Vector3>( reinterpret_cast<uintptr_t>( this ) + 0x218 );
	}

	Vector3 NewVelocity( )
	{
		return driver->read<Vector3>( reinterpret_cast<uintptr_t>( this ) + Classes::PlayerModel::newVelocity );
	}

	uint8_t IsNPC( )
	{
		return driver->read<uint8_t>( reinterpret_cast<uintptr_t>( this ) + 0x320 );
	}

	bool IsVisible( ) {
		return driver->read<bool>( reinterpret_cast<uintptr_t>( this ) + Classes::PlayerModel::visible ); // PlayerModel: visible
	}
};

class c_playermovement
{
public:

	auto set_ground_new_angle ( const float angle ) -> void
	{
		driver->write<float> ( reinterpret_cast<std::uintptr_t> (this) + Classes::PlayerWalkMovement::groundAngleNew, angle );
	}

	auto get_ground_new_angle ( ) -> const float
	{
		return driver->read<float> ( reinterpret_cast<std::uintptr_t> (this) + Classes::PlayerWalkMovement::groundAngleNew );
	}

	auto set_jump_time ( const float time ) -> void
	{
		driver->write<float> ( reinterpret_cast<std::uintptr_t> (this) + Classes::PlayerWalkMovement::jumpTime, time );
	}

	auto set_running ( const float running ) -> void
	{
		driver->write<float> ( reinterpret_cast<std::uintptr_t> (this) + Classes::BaseMovement::Runningk__BackingField, running );
	}

	auto set_grounded ( const float grounded ) -> void
	{
		driver->write<float> ( reinterpret_cast<std::uintptr_t> (this) + Classes::PlayerWalkMovement::grounded, grounded );
	}

	auto get_grounded ( ) -> const float
	{
		return driver->read<float> ( reinterpret_cast<std::uintptr_t> (this) + Classes::PlayerWalkMovement::grounded );
	}

	auto set_target_movement ( Vector3  d ) -> void
	{
		driver->write<Vector3> ( (const uintptr_t)this + Offsets::Classes::BaseMovement::TargetMovementk__BackingField, d );
	}

	auto get_target_movement ( ) -> Vector3
	{
		driver->read<Vector3> ( (const uintptr_t)this + Offsets::Classes::BaseMovement::TargetMovementk__BackingField );
	}

	auto get_jump_time ( ) -> const float
	{
		driver->read<float> ( reinterpret_cast<std::uintptr_t> (this) + Classes::PlayerWalkMovement::jumpTime );
	}

	auto set_land_time ( const float time ) -> void
	{
		driver->write<float> ( reinterpret_cast<std::uintptr_t> (this) + Classes::PlayerWalkMovement::landTime, time );
	}

	auto get_land_time ( ) -> const float
	{
		driver->read<float> ( reinterpret_cast<std::uintptr_t> (this) + Classes::PlayerWalkMovement::landTime );
	}

	auto set_ground_time ( const float time ) -> void
	{
		driver->write<float> ( reinterpret_cast<std::uintptr_t> (this) + Classes::PlayerWalkMovement::groundTime, time );
	}

	auto get_ground_time ( ) -> const float
	{
		driver->read<float> ( reinterpret_cast<std::uintptr_t> (this) + Classes::PlayerWalkMovement::groundTime );
	}

	auto get_rotation ( ) -> const Vector4
	{
		return driver->read<Vector4> ( reinterpret_cast<std::uintptr_t> (this) + Classes::PlayerModel::rotation );
	}

	auto get_position ( ) -> const Vector3
	{
		return driver->read<Vector3> ( reinterpret_cast<std::uintptr_t> (this) + Classes::PlayerModel::position );
	}

	auto set_flying(const auto val ) -> bool
	{
		return driver->write<BYTE>( reinterpret_cast<std::uintptr_t> ( this ) + 0x149, val );

	}

	auto get_capusle_center( ) -> const float
	{
		return driver->read<float>( reinterpret_cast<std::uintptr_t> ( this ) + Classes::PlayerWalkMovement::capsuleCenter );
	}

	auto set_capusle_center( const float val ) -> const float
	{
		return driver->write<float>( reinterpret_cast<std::uintptr_t> ( this ) + Classes::PlayerWalkMovement::capsuleCenter, val );
	}
};

class c_modelstate {
public:
	void SetFlag ( ModelStateFlags flag )
	{
		driver->write ( reinterpret_cast<uintptr_t>(this) + 0x24, flag ); // flags
	}

	bool HasFlags ( int Flg )
	{
		return driver->read<int> ( reinterpret_cast<uintptr_t>(this) + 0x24 ) & Flg;
	}
};

class baseplayer {
public:
	static baseplayer* local_player ( )
	{
		return driver->read_chain<baseplayer*> ( game_assembly, { (uintptr_t)m_localplayer_c, 0xB8, 0x0 } );
	}

	c_playermodel* player_model ( )
	{
		return driver->read<c_playermodel*> ( reinterpret_cast<uintptr_t>(this) + Classes::BasePlayer::playerModel );
	}

	c_playerinput* player_input ( )
	{
		return driver->read<c_playerinput*> ( reinterpret_cast<uintptr_t>(this) + Classes::BasePlayer::input );
	}

	c_playereyes* player_eyes ( )
	{
		return driver->read<c_playereyes*> ( reinterpret_cast<uintptr_t>(this) + Classes::BasePlayer::eyes );
	}

	c_playerinventory* player_inventory ( )
	{
		return driver->read<c_playerinventory*> ( reinterpret_cast<uintptr_t>(this) + Classes::BasePlayer::inventory );
	}

	c_playermovement* player_movement ( )
	{
		return driver->read<c_playermovement*> ( reinterpret_cast<uintptr_t>(this) + Classes::BasePlayer::movement );
	}

	c_modelstate* modelstate ( )
	{
		return driver->read<c_modelstate*> ( reinterpret_cast<uintptr_t>(this) + Classes::BasePlayer::modelState ); // modelState
	}

	bool HasFlags( int Flg )
	{
		return driver->read<int>( reinterpret_cast<uintptr_t>( this ) + Classes::BasePlayer::playerFlags ) & Flg;
	}

	auto needs_clothes_rebuild( const bool rebuild ) -> void
	{
		driver->write<bool>( reinterpret_cast<std::uintptr_t> ( this ) + Classes::BasePlayer::needsClothesRebuild, rebuild );
	}

	Vector3 get_bone ( int bone_id )
	{
		uintptr_t player_model = driver->read<uintptr_t> ( reinterpret_cast<uintptr_t>(this) + 0x130 );
		uintptr_t bone_transforms = driver->read<uintptr_t> ( player_model + 0x48 );
		transform_c* transform = driver->read<transform_c*> ( bone_transforms + (0x20 + (bone_id * 0x8)) );

		return transform->get_position_injected ( );
	}

	bones_t get_bones ( )
	{
		bones_t bones{};

		bones.head = get_bone ( bone_list::head );
		bones.upper_spine = get_bone ( bone_list::neck );

		bones.left_shoulder = get_bone ( bone_list::l_upperarm );
		bones.right_shoulder = get_bone ( bone_list::r_upperarm );

		bones.left_elbow = get_bone ( bone_list::l_forearm );
		bones.right_elbow = get_bone ( bone_list::r_forearm );

		bones.left_wrist = get_bone ( bone_list::l_hand );
		bones.right_wrist = get_bone ( bone_list::r_hand );

		bones.lower_spine = get_bone ( bone_list::spine1 );

		bones.left_hip = get_bone ( bone_list::l_hip );
		bones.right_hip = get_bone ( bone_list::r_hip );

		bones.left_knee = get_bone ( bone_list::l_knee );
		bones.right_knee = get_bone ( bone_list::r_knee );

		bones.left_ankle = get_bone ( bone_list::l_ankle_scale );
		bones.right_ankle = get_bone ( bone_list::r_ankle_scale );

		return bones;
	}

	auto get_projectile ( ) -> c_projectile*
	{
		const auto active_uid = driver->read<int> ( reinterpret_cast<std::uintptr_t> (this) + Classes::BasePlayer::clActiveItem );

		if ( !active_uid )
		{
			return nullptr;
		}

		for ( int i = 0; i < 6; i++ )
		{
			const auto projectile = driver->read_chain<c_projectile*> ( reinterpret_cast<std::uintptr_t> (this), { Classes::BasePlayer::inventory, 0x28, 0x38, 0x10, 0x20ull + (i * 0x8) } );

			if ( !projectile )
			{
				continue;
			}

			if ( active_uid == projectile->get_uid ( ) )
			{
				return projectile;
			}
		}

		return nullptr;
	}

	/* - */

	void SetFlags ( int Flg )
	{
		driver->write<int> ( reinterpret_cast<uintptr_t>(this) + Classes::BasePlayer::playerFlags, Flg ); // playerFlags
	}

	bool isDead ( )
	{
		return driver->read<int> ( reinterpret_cast<uintptr_t>(this) + 0x224 ); // BaseCombatEntity
	}

	std::string display_name ( )
	{
		return driver->read_wstr ( driver->read<uintptr_t> ( reinterpret_cast<uintptr_t>(this) + Classes::BasePlayer::_displayName ) + 0x14); // _displayName
	}

	float health ( )
	{
		return driver->read<float> ( reinterpret_cast<uintptr_t>(this) + Classes::BaseCombatEntity::_health ); // BaseCombatEntity
	}

	UINT64 GetItemsList ( ) {
		UINT64 Inventory = driver->read<UINT64> ( reinterpret_cast<uintptr_t>(this) + (uintptr_t)this->player_inventory ( ) );
		UINT64 Belt = driver->read<UINT64> ( Inventory + 0x28 );
		UINT64 ItemList = driver->read<UINT64> ( Belt + 0x38 );
		return driver->read<UINT64> ( ItemList + 0x10 );
	}

	std::string GetBeltItems ( UINT64 ItemsList, int Slot ) {
		UINT64 SlotItem;
		if ( Slot == 1 ) {
			SlotItem = driver->read<UINT64> ( ItemsList + 0x20 );
			if ( !SlotItem ) {
				return "None";
			}
		}
		else if ( Slot == 2 ) {
			SlotItem = driver->read<UINT64> ( ItemsList + 0x28 );
			if ( !SlotItem ) {
				return "None";
			}
		}
		else if ( Slot == 3 ) {
			SlotItem = driver->read<UINT64> ( ItemsList + 0x30 );
			if ( !SlotItem ) {
				return "None";
			}
		}
		else if ( Slot == 4 ) {
			SlotItem = driver->read<UINT64> ( ItemsList + 0x38 );
			if ( !SlotItem ) {
				return "None";
			}
		}
		else if ( Slot == 5 ) {
			SlotItem = driver->read<UINT64> ( ItemsList + 0x40 );
			if ( !SlotItem ) {
				return "None";
			}
		}
		else if ( Slot == 6 ) {
			SlotItem = driver->read<UINT64> ( ItemsList + 0x48 );
			if ( !SlotItem ) {
				return "None";
			}
		}

		UINT64 Item1Info = driver->read<UINT64> ( SlotItem + 0x20 );
		if ( !Item1Info ) {
			return "None";
		}

		UINT64 ItemDisplayName = driver->read<UINT64> ( Item1Info + 0x28 );
		if ( !ItemDisplayName ) {
			return "None";
		}

		UINT64 ItemDisplayEnglish = driver->read<UINT64> ( ItemDisplayName + 0x18 );
		if ( !ItemDisplayEnglish ) {
			return "None";
		}

		UINT64 NameTest = driver->read<UINT64> ( ItemDisplayEnglish + 0x14 );

		if ( !NameTest ) {
			return "None";
		}

		std::wstring Name = driver->read_string ( ItemDisplayEnglish + 0x14 );

		std::string output ( Name.begin ( ), Name.end ( ) );

		if ( output == "dxeso" ) {
			return "None";
		}
		return output;

	}

	UINT64 GetClothingItemsList ( ) {
		UINT64 Inventory = driver->read<UINT64> ( reinterpret_cast<uintptr_t>(this) + (uintptr_t)this->player_inventory ( ) );
		UINT64 Belt = driver->read<UINT64> ( Inventory + 0x30 );
		UINT64 ItemList = driver->read<UINT64> ( Belt + 0x38 );
		return driver->read<UINT64> ( ItemList + 0x10 );
	}

	std::string GetClothingItems ( UINT64 ItemsList, int Slot ) {
		UINT64 SlotItem;
		if ( Slot == 1 ) {
			SlotItem = driver->read<UINT64> ( ItemsList + 0x20 );
			if ( !SlotItem ) {
				return "None";
			}
		}
		else if ( Slot == 2 ) {
			SlotItem = driver->read<UINT64> ( ItemsList + 0x28 );
			if ( !SlotItem ) {
				return "None";
			}
		}
		else if ( Slot == 3 ) {
			SlotItem = driver->read<UINT64> ( ItemsList + 0x30 );
			if ( !SlotItem ) {
				return "None";
			}
		}
		else if ( Slot == 4 ) {
			SlotItem = driver->read<UINT64> ( ItemsList + 0x38 );
			if ( !SlotItem ) {
				return "None";
			}
		}
		else if ( Slot == 5 ) {
			SlotItem = driver->read<UINT64> ( ItemsList + 0x40 );
			if ( !SlotItem ) {
				return "None";
			}
		}
		else if ( Slot == 6 ) {
			SlotItem = driver->read<UINT64> ( ItemsList + 0x48 );
			if ( !SlotItem ) {
				return "None";
			}
		}
		else if ( Slot == 7 ) {
			SlotItem = driver->read<UINT64> ( ItemsList + 0x50 );
			if ( !SlotItem ) {
				return "None";
			}
		}

		UINT64 Item1Info = driver->read<UINT64> ( SlotItem + 0x20 );
		if ( !Item1Info ) {
			return "None";
		}

		UINT64 ItemDisplayName = driver->read<UINT64> ( Item1Info + 0x28 );
		if ( !ItemDisplayName ) {
			return "None";
		}

		UINT64 ItemDisplayEnglish = driver->read<UINT64> ( ItemDisplayName + 0x18 );
		if ( !ItemDisplayEnglish ) {
			return "None";
		}

		std::wstring Name = driver->read_string ( ItemDisplayEnglish + 0x14 );

		std::string output ( Name.begin ( ), Name.end ( ) );
		if ( output == "dxeso" ) {
			return "None";
		}

		return output;
	}

	long active_uid ( )
	{
		return driver->read<unsigned long> ( reinterpret_cast<uintptr_t>(this) + Classes::BasePlayer::clActiveItem ); // clActiveItem
	}

	auto is_valid ( bool local_player = false ) -> bool
	{
		if ( !this )
		{
			return false;
		}

		const auto health = this->health ( );

		if ( health > 150.f || health < 0.8f )
		{
			return false;
		}

		if ( local_player )
		{
			return !this->isDead ( );
		}

		return (!this->modelstate ( )->HasFlags ( 16 ) && !this->isDead ( ));
	}

	void changefov ( float n )
	{
		auto Class = driver->read<DWORD64> ( game_assembly + m_convar_graphics_c ); // convar_graphics_c
		auto Field = driver->read<DWORD64> ( Class + 0xB8 );
		driver->write<float> ( Field + 0x18, n );
	}
};

class pRainy {
public:
	std::mutex cache_mutex;
	std::vector<baseplayer*> player_list;
	std::vector<std::tuple<Vector3, const char*>> prefab_list;
	baseplayer* player;
}rainy;