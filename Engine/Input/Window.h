#pragma once
#include "..\pch.h"
#include "Monitor.h"
#include "WindowHint.h"

namespace SBI
{
	class Keyboard;
	class Cursor;
	class Time;

	class SBE_EXPORT Window
	{
		friend class Input;

	public:
		GLFWwindow* glfwWindow;
		GLint width, height;
		const char* title;
		Keyboard* keyboard;
		Cursor* cursor;
		Time* time;

		Window(GLFWwindow* glfwWindow);
		~Window();

		GLvoid GetWindowSize(GLint* width, GLint* height);
		GLvoid SetWindowSize(GLint width, GLint height);
		GLvoid GetFramebufferSize(GLint* width, GLint* height);
		GLvoid GetWindowPos(GLint* width, GLint* height);
		GLvoid SetWindowPos(GLint width, GLint height);
		GLvoid SetTitle(const char* title);

		GLboolean IsFocused();
		GLboolean IsIconified();
		GLboolean IsVisible();
		GLboolean ShouldClose();

		GLvoid MakeCurrent();
		GLvoid Hide();
		GLvoid Show();
		GLvoid Iconify();
		GLvoid SwapBuffers();

		GLvoid CatchCursor();
		GLvoid ReleaseCursor();

		GLvoid Update();

		WindowHint GetWindowHint();

	private:
		GLvoid WindowSizeCallback(GLint width, GLint height);

	};
}

