#pragma once
#include "..\pch.h"
#include "Vector3.h"

namespace SBM
{
	class SBE_EXPORT AxisAngle
	{
		public:
			Vector3 axis;
			float angle;

			AxisAngle(void);
			AxisAngle(Vector3 const& axis,float angle);
			AxisAngle(float x,float y,float z,float angle);
			~AxisAngle(void);

	};
}