#include "..\SBE_Internal.h"
#include "Monitor.h"

SBI::Monitor::Monitor(GLFWmonitor* monitor)
{
	this->videoModes = new std::vector<VideoMode*>();

	this->glfwMonitor = monitor;
	
	/**
	int* videoModeCount = new int();
	const GLFWvidmode* videoModes = glfwGetVideoModes(monitor, videoModeCount);

	for (int k = 0; k < *videoModeCount; k++)
	{
		VideoMode* mode = new VideoMode(videoModes[k].width, videoModes[k].height, videoModes[k].redBits, videoModes[k].greenBits, videoModes[k].blueBits, videoModes[k].refreshRate);
		this->videoModes->push_back(mode);
	}**/

	if (monitor == glfwGetPrimaryMonitor())
	{
		this->isPrimary = true;
	}

	glfwGetMonitorPos(monitor, &this->MonitorPos_X, &this->MonitorPos_Y);
	glfwGetMonitorPhysicalSize(monitor, &this->physical_width, &this->physical_height);
	this->name = glfwGetMonitorName(monitor);
}

SBI::Monitor::~Monitor()
{
	for (unsigned int i = 0; i < this->videoModes->size(); i++)
	{
		delete (*videoModes)[i];
	}
	delete videoModes;
}

SBI::VideoMode SBI::Monitor::CurrentVideoMode()
{
	const GLFWvidmode* videoMode = glfwGetVideoMode(this->glfwMonitor);
	VideoMode mode = VideoMode(videoMode->width, videoMode->height, videoMode->redBits, videoMode->greenBits, videoMode->blueBits, videoMode->refreshRate);
	return mode;
}