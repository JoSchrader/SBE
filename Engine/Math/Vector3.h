#pragma once
#include "..\pch.h"
#include <math.h>

namespace SBM
{
	class SBE_EXPORT Vector3
	{
	public:
		float x, y, z;

		Vector3(void);
		Vector3(float x, float y, float z);
		Vector3(float val);
		~Vector3(void);

		static Vector3 Cross(Vector3 const& vec1, Vector3 const& vec2);
		static float     Dot(Vector3 const& vec1, Vector3 const& vec2);
		static float  Scalar(Vector3 const& vec1, Vector3 const& vec2) { return Dot(vec1, vec2); }

		Vector3& operator+=(const Vector3& rhs);
		Vector3   operator+(const Vector3& rhs) const;
		Vector3& operator-=(const Vector3& rhs);
		Vector3   operator-(const Vector3& rhs) const;
		Vector3& operator*=(const Vector3& rhs);
		Vector3   operator*(const Vector3& rhs) const;
		Vector3& operator/=(const Vector3& rhs);
		Vector3   operator/(const Vector3& rhs) const;

		Vector3 operator-() const;
		Vector3 operator+() const;

		float operator [](int i) const;
		float & operator [](int i);

		bool operator==(Vector3 const& rhs);
		bool operator!=(Vector3 const& rhs);

		float Magnitude(void);
		float sqrMagnitude();
		void  Magnitude(float magnitude);
		void  Normalise(void);
		Vector3 Normalised() { return Normalised(*this); }
		void  Set(float x, float y, float z);
		void  Set(Vector3 const& vec);

		Vector3 Cross(Vector3 const& vec2);

		static Vector3 Normalised(Vector3 const& vector);
		static Vector3 MoveToward(Vector3 const& from, Vector3 const& to, float step);
		static Vector3 Max(Vector3 const& lhs, Vector3 const& rhs);
		static Vector3 Min(Vector3 const& lhs, Vector3 const& rhs);
		static Vector3 ClampMagnitude(Vector3 const& vector, float maxLength);
		static Vector3 Project(Vector3 const& vector, Vector3 const& on);
		static float Angle(Vector3 const& from, Vector3 const& to);
		static Vector3 Reflection(Vector3 const& in, Vector3 const& normal);

		static inline Vector3 One() { return Vector3(1, 1, 1); }
		static inline Vector3 Zero() { return Vector3(0, 0, 0); }
		static inline Vector3 X() { return Vector3(1, 0, 0); }
		static inline Vector3 Y() { return Vector3(0, 1, 0); }
		static inline Vector3 Z() { return Vector3(0, 0, 1); }

	};
}

