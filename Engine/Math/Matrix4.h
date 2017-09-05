#pragma once
#include "..\pch.h"

#define _USE_MATH_DEFINES

#include "Vector3.h"
#include <math.h>

namespace SBM
{
	class SBE_EXPORT Matrix4
	{
		public:
			float m[16];

			Matrix4(void);
			Matrix4(float m00,float m01,float m02,float m03,float m04,float m05,float m06,float m07,float m08,float m09,float m10,float m11,float m12,float m13,float m14,float m15);
			~Matrix4(void);

				
			Matrix4& operator*=(Matrix4 const& rhs);
			Matrix4   operator*(Matrix4 const& rhs) const;
			
			Vector3 operator*(Vector3 const& rhs);
	
			float operator [](int i) const; 
			float & operator [](int i);

			void Set(Matrix4 const& mat);
			void Inverse();
			
			Matrix4 Inversed();
			
			static Matrix4 Identity();

			static Matrix4 Translation(float x,float y, float z);
			static Matrix4 Translation(Vector3 const& translation){return Translation(translation.x,translation.y,translation.z);}
			
			static Matrix4 Scale(float x,float y,float z);
			static Matrix4 Scale(Vector3 const& scale){return Scale(scale.x,scale.y,scale.z);}
			
			static Matrix4 RotationX(float x);
			static Matrix4 RotationY(float y);
			static Matrix4 RotationZ(float z);
			static Matrix4 Rotation(float x,float y,float z);
			static Matrix4 Rotation(Vector3 const& rot){return Rotation(rot.x,rot.y,rot.z);}

			static Matrix4 LookAt(Vector3 const& pos,Vector3 const& dir,Vector3 const& up);	
			static Matrix4 LookAt(float eye_x,float eye_y,float eye_z,float lookAt_X,float lookAt_Y,float lookAt_Z,float up_X,float up_Y,float up_Z);
	
			static Matrix4 Perspective(float fov,float aspect,float nearr,float farr);
			static Matrix4 Ortho(float left,float right,float bottom,float top,float nearr,float farr);
	};
}