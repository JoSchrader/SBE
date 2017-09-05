#pragma once
#include "..\pch.h"

namespace SBI
{
	class  Window;

	class SBE_EXPORT Cursor
	{
	private:
		Window* relatedWindow;

	public:
		GLdouble posX;
		GLdouble posY;
		GLdouble moveX;
		GLdouble moveY;
		GLint posXi;
		GLint posYi;
				
		Cursor(Window* relatedWindow);
		~Cursor();
		
		GLvoid Update();
	};
}