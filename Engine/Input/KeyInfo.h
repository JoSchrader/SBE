#pragma once
#include "..\SBE_Internal.h"
#include "Keys.h"

namespace SBI
{
	class SBE_API KeyInfo
	{
	public:
		Keys key;
		bool pressed;
		bool toDown;
		bool toUp;
		float deltaTime;

		KeyInfo(void);
		KeyInfo(Keys key);
		~KeyInfo(void);
	};
}