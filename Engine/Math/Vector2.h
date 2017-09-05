#pragma once
#include "..\pch.h"

namespace SBM
{
	class SBE_EXPORT Vector2
	{
	public:
		float x, y;

		Vector2(void);
		Vector2(float x, float y);
		~Vector2(void);
	};
}