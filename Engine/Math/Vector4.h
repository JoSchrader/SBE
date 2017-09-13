#pragma once
#include "..\SBE_Internal.h"

namespace SBM
{
	class SBE_API Vector4
	{
	public:
		float x, y, z, w;
		Vector4(float x, float y, float z, float w);
		Vector4(void);
		Vector4(float val);


		Vector4& operator*=(Vector4 const& rhs);
		Vector4   operator*(Vector4 const& rhs) const;
		Vector4& operator+=(Vector4 const& rhs);
		Vector4   operator+(Vector4 const& rhs) const;


		~Vector4(void);
	};
}