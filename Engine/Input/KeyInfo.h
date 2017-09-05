#pragma once
#include "..\pch.h"
#include "Keys.h"

namespace SBI
{
	class SBE_EXPORT KeyInfo
	{
	public:
		Keys key;
		GLboolean pressed;
		GLboolean toDown;
		GLboolean toUp;
		GLfloat deltaTime;

		KeyInfo(void);
		KeyInfo(Keys key);
		~KeyInfo(void);
	};
}