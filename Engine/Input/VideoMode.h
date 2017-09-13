#pragma once
#include "..\SBE_Internal.h"

namespace SBI
{
	class SBE_API VideoMode
	{
	public:
		int width;
		int height;
		int redBits;
		int greenBits;
		int blueBits;
		int refreshRate;

	public:
		VideoMode();
		VideoMode(int width, int height, int redBits, int greenBits, int blueBits, int refreshRate);
		~VideoMode();
	};
}