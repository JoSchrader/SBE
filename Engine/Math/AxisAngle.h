#pragma once
#include "..\SBE_Internal.h"
#include "Vector3.h"

namespace SBM
{
	class SBE_API AxisAngle
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