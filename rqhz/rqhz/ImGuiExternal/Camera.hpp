#pragma once
#include "Imports.hpp"

using namespace Offsets;

struct matrix_s
{
	union
	{
		struct
		{
			float _11, _12, _13, _14;
			float _21, _22, _23, _24;
			float _31, _32, _33, _34;
			float _41, _42, _43, _44;
		};
		float m[4][4];
	};
};

class camera_c
{
public:

	static camera_c* get_instance ( )
	{
		return driver->read_chain<camera_c*> ( game_assembly, { (uintptr_t)m_Maincamera_c, 0xB8, 0x0, 0x10 } );
	}

	matrix_s projection_matrix ( )
	{
		return driver->read<matrix_s> ( reinterpret_cast<uintptr_t>(this) + 0x2E4 );
	}

	Vector3 position ( )
	{
		return driver->read<Vector3> ( reinterpret_cast<uintptr_t>(this) + 0x42C );
	}

	bool WorldToScreen( matrix_s *matrix, Vector3 world, Vector2 *screen )
	{
		Vector3 TransVec = Vector3( matrix->_14, matrix->_24, matrix->_34 );
		Vector3 RightVec = Vector3( matrix->_11, matrix->_21, matrix->_31 );
		Vector3 UpVec = Vector3( matrix->_12, matrix->_22, matrix->_32 );

		const float w = TransVec.dot( world ) + matrix->_44;

		if ( w < 0.5f )return false; //0.098f

		const float x = RightVec.dot( world ) + matrix->_41;
		const float y = UpVec.dot( world ) + matrix->_42;

		*screen =
		{
			( (float)config.Includes.width * 0.5f ) * ( 1.f + x / w ),
			( (float)config.Includes.height * 0.5f + 1 ) * ( 1.f - y / w )
		};
		return true;
	}
};