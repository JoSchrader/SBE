#pragma once
#include "..\SBE_Internal.h"

namespace SBI
{
	class  Window;

	class SBE_API Cursor
	{
	private:
		Window* relatedWindow;

	public:
		double posX;
		double posY;
		double moveX;
		double moveY;
		int posXi;
		int posYi;
				
		Cursor(Window* relatedWindow);
		~Cursor();
		
		void Update();
	};
}