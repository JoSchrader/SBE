#pragma once
#include "..\pch.h"
#include "VideoMode.h"

namespace SBI
{
	class SBE_EXPORT Monitor
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