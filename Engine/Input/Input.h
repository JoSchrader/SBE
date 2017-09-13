#pragma once
#include "..\SBE_Internal.h"
#include <GLEW\glew.h>
#include <GLFW\glfw3.h>

#include <vector>

namespace SBI
{
	class Monitor;
	class Window;
	class WindowHint;

	class SBE_API Input
	{
	public:
		static std::vector<Monitor*> *monitors;
		static Monitor *primaryMonitor;

		static std::vector<Window*> *windows;
		static Window* currentWindow;

		static GLint SBI_Init();

		static GLint GLEW_Init_ForCurrentContext()
		{
			glewExperimental = GL_TRUE;
			GLenum err = glewInit();
			if (err != GLEW_OK)
			{
				fprintf(stderr, "Error: %s\n", glewGetErrorString(err));
				return -1;
			}
			return 0;
		}

	private:
		static Window*  CreateWindowXX_Actual(GLint width, GLint height, const char* title, Monitor* monitor, SBI::Window* shareWindow, WindowHint* windowHint);
	public:

		static Window*  CreateWindowXX(GLint width, GLint height, const char* title, Monitor* monitor, SBI::Window* shareWindow, WindowHint* windowHint)
		{
			Window* ret = CreateWindowXX_Actual(width, height, title, monitor, shareWindow, windowHint);
			GLEW_Init_ForCurrentContext();
			return ret;
		}
		static Window*  CreateWindowXX(GLint width, GLint height, const char* title) { return CreateWindowXX(width, height, title, nullptr, nullptr, nullptr); };
		static Window*  CreateWindowXX(GLint width, GLint height, const char* title, Monitor* monitor) { return CreateWindowXX(width, height, title, monitor, nullptr, nullptr); };
		static Window*  CreateWindowXX(GLint width, GLint height, const char* title, WindowHint* windowHint) { return CreateWindowXX(width, height, title, nullptr, nullptr, windowHint); };

		static GLvoid DestroyWindow(Window* window);

		static GLvoid Error_Callback(GLint error, const char* description);
		static GLvoid Resize_Callback(GLFWwindow* window, GLint width, GLint height);

		static GLvoid PoolEvents();

		static GLvoid  Teminate();
	};

}