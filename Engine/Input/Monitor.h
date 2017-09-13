#pragma once
#include "..\SBE_Internal.h"
#include "VideoMode.h"
#include <GLEW\glew.h>
#include <GLFW\glfw3.h>

#include <vector>

namespace SBI
{
	class SBE_API Monitor
	{
	public:
		GLFWmonitor* glfwMonitor;
		GLboolean isPrimary;
		GLint physical_width, physical_height;
		GLint MonitorPos_X, MonitorPos_Y;
		const char* name;
		std::vector<VideoMode*> *videoModes;

		Monitor(GLFWmonitor* monitor);
		~Monitor();
		VideoMode CurrentVideoMode();
	};
}