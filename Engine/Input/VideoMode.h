#pragma once
#include "..\pch.h"

namespace SBI
{
	class SBE_EXPORT VideoMode
	{
	public:
		GLint width;
		GLint height;
		GLint redBits;
		GLint greenBits;
		GLint blueBits;
		GLint refreshRate;
		
	public:
		VideoMode();
		VideoMode(GLint width, GLint height,GLint redBits,GLint greenBits,GLint blueBits,GLint refreshRate);
		~VideoMode();
	};
}