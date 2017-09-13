#pragma once
#include "..\SBE_Internal.h"

namespace SBM
{
	class SBE_API Vector2
	{
	public:
		float x, y;

		Vector2(void);
		Vector2(float x, float y);
		~Vector2(void);
	};
}