#include "..\SBE_Internal.h"
#include "Keyboard.h"
#include "Time.h"
#include "Window.h"
#include "Input.h"

SBI::Keyboard::Keyboard(SBI::Window* relatedWindow)
{
	this->relatedWindow = relatedWindow;

	int last = static_cast<int>(SBI::Keys::Last);
	for (int i = 0; i < last + 1; i++)
	{
		this->lastChanged[i] = 0;
		this->infos[i] = KeyInfo(((Keys)i));
	}
}

SBI::Keyboard::~Keyboard(void)
{
}

void SBI::Keyboard::Update()
{
	this->time = (GLfloat)glfwGetTime();
	UpdateKey(SBI::Keys::A, glfwGetKey(relatedWindow->glfwWindow, 'A'));
	UpdateKey(SBI::Keys::B, glfwGetKey(relatedWindow->glfwWindow, 'B'));
	UpdateKey(SBI::Keys::C, glfwGetKey(relatedWindow->glfwWindow, 'C'));
	UpdateKey(SBI::Keys::D, glfwGetKey(relatedWindow->glfwWindow, 'D'));
	UpdateKey(SBI::Keys::E, glfwGetKey(relatedWindow->glfwWindow, 'E'));
	UpdateKey(SBI::Keys::F, glfwGetKey(relatedWindow->glfwWindow, 'F'));
	UpdateKey(SBI::Keys::G, glfwGetKey(relatedWindow->glfwWindow, 'G'));
	UpdateKey(SBI::Keys::H, glfwGetKey(relatedWindow->glfwWindow, 'H'));
	UpdateKey(SBI::Keys::I, glfwGetKey(relatedWindow->glfwWindow, 'I'));
	UpdateKey(SBI::Keys::J, glfwGetKey(relatedWindow->glfwWindow, 'J'));
	UpdateKey(SBI::Keys::K, glfwGetKey(relatedWindow->glfwWindow, 'K'));
	UpdateKey(SBI::Keys::L, glfwGetKey(relatedWindow->glfwWindow, 'L'));
	UpdateKey(SBI::Keys::M, glfwGetKey(relatedWindow->glfwWindow, 'M'));
	UpdateKey(SBI::Keys::N, glfwGetKey(relatedWindow->glfwWindow, 'N'));
	UpdateKey(SBI::Keys::O, glfwGetKey(relatedWindow->glfwWindow, 'O'));
	UpdateKey(SBI::Keys::P, glfwGetKey(relatedWindow->glfwWindow, 'P'));
	UpdateKey(SBI::Keys::Q, glfwGetKey(relatedWindow->glfwWindow, 'Q'));
	UpdateKey(SBI::Keys::R, glfwGetKey(relatedWindow->glfwWindow, 'R'));
	UpdateKey(SBI::Keys::S, glfwGetKey(relatedWindow->glfwWindow, 'S'));
	UpdateKey(SBI::Keys::T, glfwGetKey(relatedWindow->glfwWindow, 'T'));
	UpdateKey(SBI::Keys::U, glfwGetKey(relatedWindow->glfwWindow, 'U'));
	UpdateKey(SBI::Keys::V, glfwGetKey(relatedWindow->glfwWindow, 'V'));
	UpdateKey(SBI::Keys::W, glfwGetKey(relatedWindow->glfwWindow, 'W'));
	UpdateKey(SBI::Keys::X, glfwGetKey(relatedWindow->glfwWindow, 'X'));
	UpdateKey(SBI::Keys::Y, glfwGetKey(relatedWindow->glfwWindow, 'Y'));
	UpdateKey(SBI::Keys::Z, glfwGetKey(relatedWindow->glfwWindow, 'Z'));

	//UpdateKey(SBI::Keys::UE,glfwGetKey(relatedWindow->glfwWindow,'Ü'));
	//UpdateKey(SBI::Keys::OE,glfwGetKey(relatedWindow->glfwWindow,'Ö'));
	//UpdateKey(SBI::Keys::AE,glfwGetKey(relatedWindow->glfwWindow,'Ä'));

	UpdateKey(SBI::Keys::_0, glfwGetKey(relatedWindow->glfwWindow, '0'));
	UpdateKey(SBI::Keys::_1, glfwGetKey(relatedWindow->glfwWindow, '1'));
	UpdateKey(SBI::Keys::_2, glfwGetKey(relatedWindow->glfwWindow, '2'));
	UpdateKey(SBI::Keys::_3, glfwGetKey(relatedWindow->glfwWindow, '3'));
	UpdateKey(SBI::Keys::_4, glfwGetKey(relatedWindow->glfwWindow, '4'));
	UpdateKey(SBI::Keys::_5, glfwGetKey(relatedWindow->glfwWindow, '5'));
	UpdateKey(SBI::Keys::_6, glfwGetKey(relatedWindow->glfwWindow, '6'));
	UpdateKey(SBI::Keys::_7, glfwGetKey(relatedWindow->glfwWindow, '7'));
	UpdateKey(SBI::Keys::_8, glfwGetKey(relatedWindow->glfwWindow, '8'));
	UpdateKey(SBI::Keys::_9, glfwGetKey(relatedWindow->glfwWindow, '9'));

	UpdateKey(SBI::Keys::F1, glfwGetKey(relatedWindow->glfwWindow, GLFW_KEY_F1));
	UpdateKey(SBI::Keys::F2, glfwGetKey(relatedWindow->glfwWindow, GLFW_KEY_F2));
	UpdateKey(SBI::Keys::F3, glfwGetKey(relatedWindow->glfwWindow, GLFW_KEY_F3));
	UpdateKey(SBI::Keys::F4, glfwGetKey(relatedWindow->glfwWindow, GLFW_KEY_F4));
	UpdateKey(SBI::Keys::F5, glfwGetKey(relatedWindow->glfwWindow, GLFW_KEY_F5));
	UpdateKey(SBI::Keys::F6, glfwGetKey(relatedWindow->glfwWindow, GLFW_KEY_F6));
	UpdateKey(SBI::Keys::F7, glfwGetKey(relatedWindow->glfwWindow, GLFW_KEY_F7));
	UpdateKey(SBI::Keys::F8, glfwGetKey(relatedWindow->glfwWindow, GLFW_KEY_F8));
	UpdateKey(SBI::Keys::F9, glfwGetKey(relatedWindow->glfwWindow, GLFW_KEY_F9));
	UpdateKey(SBI::Keys::F10, glfwGetKey(relatedWindow->glfwWindow, GLFW_KEY_F10));
	UpdateKey(SBI::Keys::F11, glfwGetKey(relatedWindow->glfwWindow, GLFW_KEY_F11));
	UpdateKey(SBI::Keys::F12, glfwGetKey(relatedWindow->glfwWindow, GLFW_KEY_F12));

	UpdateKey(SBI::Keys::Num0, glfwGetKey(relatedWindow->glfwWindow, GLFW_KEY_KP_0));
	UpdateKey(SBI::Keys::Num1, glfwGetKey(relatedWindow->glfwWindow, GLFW_KEY_KP_1));
	UpdateKey(SBI::Keys::Num2, glfwGetKey(relatedWindow->glfwWindow, GLFW_KEY_KP_2));
	UpdateKey(SBI::Keys::Num3, glfwGetKey(relatedWindow->glfwWindow, GLFW_KEY_KP_3));
	UpdateKey(SBI::Keys::Num4, glfwGetKey(relatedWindow->glfwWindow, GLFW_KEY_KP_4));
	UpdateKey(SBI::Keys::Num5, glfwGetKey(relatedWindow->glfwWindow, GLFW_KEY_KP_5));
	UpdateKey(SBI::Keys::Num6, glfwGetKey(relatedWindow->glfwWindow, GLFW_KEY_KP_6));
	UpdateKey(SBI::Keys::Num7, glfwGetKey(relatedWindow->glfwWindow, GLFW_KEY_KP_7));
	UpdateKey(SBI::Keys::Num8, glfwGetKey(relatedWindow->glfwWindow, GLFW_KEY_KP_8));
	UpdateKey(SBI::Keys::Num9, glfwGetKey(relatedWindow->glfwWindow, GLFW_KEY_KP_9));

	UpdateKey(SBI::Keys::Num_Divide, glfwGetKey(relatedWindow->glfwWindow, GLFW_KEY_KP_DIVIDE));
	UpdateKey(SBI::Keys::Num_Multiply, glfwGetKey(relatedWindow->glfwWindow, GLFW_KEY_KP_MULTIPLY));
	UpdateKey(SBI::Keys::Num_Subtract, glfwGetKey(relatedWindow->glfwWindow, GLFW_KEY_KP_SUBTRACT));
	UpdateKey(SBI::Keys::Num_Add, glfwGetKey(relatedWindow->glfwWindow, GLFW_KEY_KP_ADD));
	UpdateKey(SBI::Keys::Num_Enter, glfwGetKey(relatedWindow->glfwWindow, GLFW_KEY_KP_ENTER));
	UpdateKey(SBI::Keys::Num_Decimal, glfwGetKey(relatedWindow->glfwWindow, GLFW_KEY_KP_DECIMAL));
	UpdateKey(SBI::Keys::Num_Lock, glfwGetKey(relatedWindow->glfwWindow, GLFW_KEY_NUM_LOCK));

	UpdateKey(SBI::Keys::Up, glfwGetKey(relatedWindow->glfwWindow, GLFW_KEY_UP));
	UpdateKey(SBI::Keys::Down, glfwGetKey(relatedWindow->glfwWindow, GLFW_KEY_DOWN));
	UpdateKey(SBI::Keys::Left, glfwGetKey(relatedWindow->glfwWindow, GLFW_KEY_LEFT));
	UpdateKey(SBI::Keys::Right, glfwGetKey(relatedWindow->glfwWindow, GLFW_KEY_RIGHT));

	UpdateKey(SBI::Keys::Insert, glfwGetKey(relatedWindow->glfwWindow, GLFW_KEY_INSERT));
	UpdateKey(SBI::Keys::Del, glfwGetKey(relatedWindow->glfwWindow, GLFW_KEY_DELETE));
	UpdateKey(SBI::Keys::PageUp, glfwGetKey(relatedWindow->glfwWindow, GLFW_KEY_PAGE_UP));
	UpdateKey(SBI::Keys::PageDown, glfwGetKey(relatedWindow->glfwWindow, GLFW_KEY_PAGE_DOWN));
	UpdateKey(SBI::Keys::Home, glfwGetKey(relatedWindow->glfwWindow, GLFW_KEY_HOME));
	UpdateKey(SBI::Keys::End, glfwGetKey(relatedWindow->glfwWindow, GLFW_KEY_END));

	UpdateKey(SBI::Keys::Enter, glfwGetKey(relatedWindow->glfwWindow, GLFW_KEY_ENTER));
	UpdateKey(SBI::Keys::Backspace, glfwGetKey(relatedWindow->glfwWindow, GLFW_KEY_BACKSPACE));
	UpdateKey(SBI::Keys::LeftShift, glfwGetKey(relatedWindow->glfwWindow, GLFW_KEY_LEFT_SHIFT));
	UpdateKey(SBI::Keys::RightShift, glfwGetKey(relatedWindow->glfwWindow, GLFW_KEY_RIGHT_SHIFT));
	UpdateKey(SBI::Keys::Space, glfwGetKey(relatedWindow->glfwWindow, GLFW_KEY_SPACE));
	UpdateKey(SBI::Keys::Capslock, glfwGetKey(relatedWindow->glfwWindow, GLFW_KEY_CAPS_LOCK));
	UpdateKey(SBI::Keys::Tabulator, glfwGetKey(relatedWindow->glfwWindow, GLFW_KEY_TAB));
	UpdateKey(SBI::Keys::Zirkumflex, glfwGetKey(relatedWindow->glfwWindow, '^'));
	UpdateKey(SBI::Keys::Question, glfwGetKey(relatedWindow->glfwWindow, '?'));

	UpdateKey(SBI::Keys::Apostroph, glfwGetKey(relatedWindow->glfwWindow, '`'));
	UpdateKey(SBI::Keys::Add, glfwGetKey(relatedWindow->glfwWindow, '+'));
	UpdateKey(SBI::Keys::Hashmark, glfwGetKey(relatedWindow->glfwWindow, '#'));
	UpdateKey(SBI::Keys::Minus, glfwGetKey(relatedWindow->glfwWindow, '-'));
	UpdateKey(SBI::Keys::Period, glfwGetKey(relatedWindow->glfwWindow, '.'));
	UpdateKey(SBI::Keys::Comma, glfwGetKey(relatedWindow->glfwWindow, ','));
	UpdateKey(SBI::Keys::Pipe, glfwGetKey(relatedWindow->glfwWindow, '<'));
	UpdateKey(SBI::Keys::LeftCrtl, glfwGetKey(relatedWindow->glfwWindow, GLFW_KEY_LEFT_CONTROL));
	UpdateKey(SBI::Keys::RightCrtl, glfwGetKey(relatedWindow->glfwWindow, GLFW_KEY_RIGHT_CONTROL));
	UpdateKey(SBI::Keys::LeftAlt, glfwGetKey(relatedWindow->glfwWindow, GLFW_KEY_LEFT_ALT));
	UpdateKey(SBI::Keys::RightAlt, glfwGetKey(relatedWindow->glfwWindow, GLFW_KEY_RIGHT_ALT));
	UpdateKey(SBI::Keys::Menu, glfwGetKey(relatedWindow->glfwWindow, GLFW_KEY_MENU));
	UpdateKey(SBI::Keys::LeftWindows, glfwGetKey(relatedWindow->glfwWindow, GLFW_KEY_LEFT_SUPER));
	UpdateKey(SBI::Keys::RightWindows, glfwGetKey(relatedWindow->glfwWindow, GLFW_KEY_RIGHT_SUPER));
	//Key_Print
	UpdateKey(SBI::Keys::Pause, glfwGetKey(relatedWindow->glfwWindow, GLFW_KEY_PAUSE));

	UpdateKey(SBI::Keys::Mouse_1, glfwGetMouseButton(relatedWindow->glfwWindow, GLFW_MOUSE_BUTTON_1));
	UpdateKey(SBI::Keys::Mouse_2, glfwGetMouseButton(relatedWindow->glfwWindow, GLFW_MOUSE_BUTTON_2));
	UpdateKey(SBI::Keys::Mouse_3, glfwGetMouseButton(relatedWindow->glfwWindow, GLFW_MOUSE_BUTTON_3));
	UpdateKey(SBI::Keys::Mouse_4, glfwGetMouseButton(relatedWindow->glfwWindow, GLFW_MOUSE_BUTTON_4));
	UpdateKey(SBI::Keys::Mouse_5, glfwGetMouseButton(relatedWindow->glfwWindow, GLFW_MOUSE_BUTTON_5));
	UpdateKey(SBI::Keys::Mouse_6, glfwGetMouseButton(relatedWindow->glfwWindow, GLFW_MOUSE_BUTTON_6));
	UpdateKey(SBI::Keys::Mouse_7, glfwGetMouseButton(relatedWindow->glfwWindow, GLFW_MOUSE_BUTTON_7));
	UpdateKey(SBI::Keys::Mouse_8, glfwGetMouseButton(relatedWindow->glfwWindow, GLFW_MOUSE_BUTTON_8));
}

void SBI::Keyboard::UpdateKey(SBI::Keys key, int pressed)
{
	int key_int = static_cast<int>(key);
	this->infos[key_int].toDown = false;
	this->infos[key_int].toUp = false;

	if (this->infos[key_int].pressed)
	{
		if (!pressed)
		{
			this->infos[key_int].toUp = true;
			this->lastChanged[key_int] = time;
		}
	}
	else
	{
		if (pressed)
		{
			this->infos[key_int].toDown = true;
			this->lastChanged[key_int] = time;
		}
	}

	this->infos[key_int].pressed = pressed > 0;
	this->infos[key_int].deltaTime = time - this->lastChanged[key_int];
}

SBI::KeyInfo SBI::Keyboard::GetKey(SBI::Keys key)
{
	return SBI::Input::currentWindow->keyboard->infos[static_cast<int>(key)];
}

bool SBI::Keyboard::GetKeyPressed(SBI::Keys key)
{
	return SBI::Input::currentWindow->keyboard->infos[static_cast<int>(key)].pressed;
}