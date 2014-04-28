#include "GameConfig.h"

namespace GameMatrix
{
// 	std::tuple<float,float,float>   fromrotmat( const D3DXMATRIXA16 &m ) 
// 	{// Setup the Euler angles, given a rotation matrix.
// 		float pitch, heading, bank;
// 		float	sp = -m._23;// Extract sin(pitch) from _23.
// 		
// 		heading = atan2( m._13, m._33 );
// 		pitch = asin( sp );
// 		bank = atan2( m._21, m._22 );
// 		
// 		return std::make_tuple( pitch, heading, bank );
// 	}
// 
// 	std::tuple<float,float,float> AxisAngleToYawPitchRoll( float x, float y, float z, float angle )
// 	{
// 		float yaw = 0;
// 		float roll = 0;
// 		float pitch = 0;
// 
// 		float s = sin( angle );
// 		float c = cos( angle );
// 		float t = 1 - c;
// 		//  if axis is not already normalised then uncomment this
// 		// double magnitude = sqrt(x*x + y*y + z*z);
// 		// if (magnitude==0) throw error;
// 		// x /= magnitude;
// 		// y /= magnitude;
// 		// z /= magnitude;
// 		if ( ( x*y*t + z*s ) > 0.998 ) { // north pole singularity detected
// 			yaw = 2 * atan2( x*sin( angle / 2 ), cos( angle / 2 ) );
// 			roll = D3DX_PI/ 2;
// 			pitch = 0;
// 			return std::make_tuple( yaw, pitch, roll );
// 		}
// 		if ( ( x*y*t + z*s ) < -0.998 ) { // south pole singularity detected
// 			yaw = -2 * atan2( x*sin( angle / 2 ), cos( angle / 2 ) );
// 			roll = -D3DX_PI/ 2;
// 			pitch = 0;
// 			return std::make_tuple( yaw, pitch, roll );
// 		}
// 		yaw = atan2( y * s - x * z * t, 1 - ( y*y + z*z ) * t );
// 		roll = asin( x * y * t + z * s );
// 		pitch = atan2( x * s - y * z * t, 1 - ( x*x + z*z ) * t );
// 
// 		return std::make_tuple( yaw, pitch, roll );
// 	}

	// quaternion 값을 yaw pitch roll 로 변환
	// return 값이 tuple이므로 auto로 받을 것..
	// 04.28 김성환
	std::tuple<float, float, float> QuaternionToYawPitchRoll( D3DXQUATERNION q1 ) {
		float yaw = 0;
		float roll = 0;
		float pitch = 0;

		float test = q1.x*q1.y + q1.z*q1.w;
		if ( test > 0.499 ) { // singularity at north pole
			yaw = 2 * atan2( q1.x, q1.w );
			roll = D3DX_PI / 2;
			pitch = 0;
			return std::make_tuple( yaw, pitch, roll );
		}
		if ( test < -0.499 ) { // singularity at south pole
			yaw = -2 * atan2( q1.x, q1.w );
			roll = -D3DX_PI / 2;
			pitch = 0;
			return std::make_tuple( yaw, pitch, roll );
		}
		float  sqx = q1.x*q1.x;
		float  sqy = q1.y*q1.y;
		float  sqz = q1.z*q1.z;
		yaw = atan2( 2 * q1.y*q1.w - 2 * q1.x*q1.z, 1 - 2 * sqy - 2 * sqz );
		roll = asin( 2 * test );
		pitch = atan2( 2 * q1.x*q1.w - 2 * q1.y*q1.z, 1 - 2 * sqx - 2 * sqz );
		
		return std::make_tuple( yaw, pitch, roll );
	}
}
