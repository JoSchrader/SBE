#pragma once
#include "..\SBE_Internal.h"
#include "KeyInfo.h"

namespace SBI
{
	class Window;

	class SBE_API Keyboard
	{
	private:
		Window* relatedWindow;
		float time;

	public:
		float lastChanged[static_cast<int>(SBI::Keys::Last) + 1];
		KeyInfo infos[static_cast<int>(SBI::Keys::Last) + 1];

		Keyboard(Window* relatedWindow);
		~Keyboard(void);

		void Update();
		void UpdateKey(SBI::Keys index, int pressed);

		static KeyInfo GetKey(SBI::Keys key);
		static bool GetKeyPressed(SBI::Keys key);
	};
}
