#pragma once
#include "..\pch.h"

#define _USE_MATH_DEFINES

#include <math.h>
#include "Matrix4.h"
#include "Vector3.h"
#include "AxisAngle.h"

namespace SBM
{
	class SBE_EXPORT Quaternion
	{
	public:
		float x,y,z,w;
		Quaternion(void);
		Quaternion(float x,float y,float z,float w);
		~Quaternion(void);

		Quaternion& operator+=(Quaternion const& rhs);
		Quaternion   operator+(Quaternion const& rhs) const;		
		Quaternion& operator-=(Quaternion const& rhs);
		Quaternion   operator-(Quaternion const& rhs) const;				
		Quaternion& operator*=(Quaternion const& rhs);
		Quaternion   operator*(Quaternion const& rhs) const;

		Vector3 operator*(Vector3 const& rhs) const;

		Quaternion operator-();
		Quaternion operator+();

		bool operator==(Quaternion const& rhs);
		bool operator!=(Quaternion const& rhs);

		float operator [](int i) const; 
		float & operator [](int i);

		float Magnitude();
		void Inverse();
		void Conjugate(){Inverse();}
		void Normalise();
		Matrix4 Matrix() const;
		Vector3 ToEuler();
		AxisAngle ToAxisAngle(); 

		static Quaternion Normalised(Quaternion const& quaternion);
		static Quaternion Inversed(Quaternion const& quaternion);
		
		static Quaternion Euler(float x,float y,float z);
		static Quaternion Euler(Vector3 const& vec){return Euler(vec.x,vec.y,vec.z);}

		static Quaternion AxisAngle(float x,float y,float z, float angle);
		static Quaternion AxisAngle(Vector3 const& axis, float angle){ return AxisAngle(axis.x,axis.y,axis.z,angle);}
		static Quaternion AxisAngle(SBM::AxisAngle const& axisAngle){ return AxisAngle(axisAngle.axis,axisAngle.angle);}
	
		//static Quaternion RotMat(Matrix4 const& mat);
	};
}