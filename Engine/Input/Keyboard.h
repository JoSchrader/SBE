#pragma once
#include "..\pch.h"
#include "KeyInfo.h"

namespace SBI
{
	class Window;

	class SBE_EXPORT Keyboard
	{
	private:
		Window* relatedWindow;
		GLfloat time;

	public:
		GLfloat lastChanged[static_cast<int>(SBI::Keys::Last) + 1];
		KeyInfo infos[static_cast<int>(SBI::Keys::Last) + 1];

		Keyboard(Window* relatedWindow);
		~Keyboard(void);

		void Update();
		void UpdateKey(SBI::Keys index, int pressed);

		static KeyInfo GetKey(SBI::Keys key);
		static GLboolean GetKeyPressed(SBI::Keys key);
	};
}
