#include "..\SBE_Internal.h"
#include "Input.h"
#include "Monitor.h"
#include "WindowHint.h"
#include "Window.h"

GLint SBI::Input::SBI_Init()
{

	if (!glfwInit())
	{
		return -1;
	}
	
	monitors = new std::vector<Monitor*>();
	windows = new std::vector<Window*>();

	glfwSetErrorCallback(Input::Error_Callback);

	int* monitorCount = new int();
	GLFWmonitor** monitors = glfwGetMonitors(monitorCount);

	for (int i = 0; i < *monitorCount; i++)
	{
		Monitor *monitor = new Monitor(monitors[i]);
		Input::monitors->push_back(monitor);

		if (monitor->isPrimary == GL_TRUE)
		{
			Input::primaryMonitor = monitor;
		}
	}

	return 0;
}

SBI::Window* SBI::Input::CreateWindowXX_Actual(GLint width, GLint height, const char* title, SBI::Monitor *monitor, SBI::Window* shareWindow, SBI::WindowHint *windowHint)
{
	if (windowHint == nullptr)
	{
		glfwDefaultWindowHints();
	}
	else
	{
		glfwWindowHint(GLFW_RESIZABLE, windowHint->resizable);
		glfwWindowHint(GLFW_VISIBLE, windowHint->visible);
		glfwWindowHint(GLFW_DECORATED, windowHint->decorated);
		glfwWindowHint(GLFW_RED_BITS, windowHint->red_bits);
		glfwWindowHint(GLFW_GREEN_BITS, windowHint->green_bits);
		glfwWindowHint(GLFW_BLUE_BITS, windowHint->blue_bits);
		glfwWindowHint(GLFW_ALPHA_BITS, windowHint->alpha_bits);
		glfwWindowHint(GLFW_STENCIL_BITS, windowHint->stencil_bits);
		glfwWindowHint(GLFW_ACCUM_RED_BITS, windowHint->accum_red_bits);
		glfwWindowHint(GLFW_ACCUM_GREEN_BITS, windowHint->accum_green_bits);
		glfwWindowHint(GLFW_ACCUM_BLUE_BITS, windowHint->accum_blue_bits);
		glfwWindowHint(GLFW_ACCUM_ALPHA_BITS, windowHint->accum_alpha_bits);
		glfwWindowHint(GLFW_AUX_BUFFERS, windowHint->aux_buffer);
		glfwWindowHint(GLFW_SAMPLES, windowHint->samples);
		glfwWindowHint(GLFW_REFRESH_RATE, windowHint->refresh_rate);
		glfwWindowHint(GLFW_STEREO, windowHint->stereo);
		glfwWindowHint(GLFW_SRGB_CAPABLE, windowHint->srgb_capable);
		glfwWindowHint(GLFW_CLIENT_API, static_cast<int>(windowHint->client_api));
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, windowHint->context_version_major);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, windowHint->context_version_minor);
		glfwWindowHint(GLFW_CONTEXT_ROBUSTNESS, static_cast<int>(windowHint->context_robustness));
		glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, windowHint->opengl_forward_compatible);
		glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, windowHint->opengl_debug_context);
		glfwWindowHint(GLFW_OPENGL_PROFILE, static_cast<int>(windowHint->opengl_profile));
	}

	GLFWmonitor* glfwmonitor = NULL;
	GLFWwindow* glfwShareWindow = NULL;

	if (monitor != nullptr)
		glfwmonitor = monitor->glfwMonitor;

	if (shareWindow != nullptr)
		glfwShareWindow = shareWindow->glfwWindow;

	GLFWwindow* glfw_window = glfwCreateWindow(width, height, title, glfwmonitor, glfwShareWindow);
	

	if (glfw_window == NULL)
	{
		return nullptr;
	}
	else
	{
		SBI::Window *window = new SBI::Window(glfw_window);

		window->title = title;
		window->width = width;
		window->height = height;

		glfwSetWindowSizeCallback(glfw_window, Input::Resize_Callback);

		SBI::Input::windows->push_back(window);

		GLEW_Init_ForCurrentContext();

		return window;
	}
}

GLvoid SBI::Input::DestroyWindow(SBI::Window* window)
{
	glfwDestroyWindow(window->glfwWindow);

	if (SBI::Input::currentWindow->glfwWindow == window->glfwWindow)
	{
		SBI::Input::currentWindow = nullptr;
	}
}

GLvoid SBI::Input::Error_Callback(GLint error, const char* description)
{

}

GLvoid SBI::Input::Resize_Callback(GLFWwindow* window, GLint width, GLint height)
{
	for (std::vector<Window*>::iterator it = Input::windows->begin(); it != Input::windows->end(); it++)
	{
		if ((*it)->glfwWindow == window)
		{
			(*it)->WindowSizeCallback(width, height);
			break;
		}
	}
}

GLvoid SBI::Input::PoolEvents()
{
	glfwPollEvents();
}

GLvoid SBI::Input::Teminate()
{
	for (unsigned int i = 0; i < Input::monitors->size(); i++)
	{
		delete (*Input::monitors)[i];
	}

	for (unsigned int i = 0; i < Input::windows->size(); i++)
	{
		SBI::Input::DestroyWindow((*Input::windows)[i]);
		delete (*Input::windows)[i];
	}

	delete monitors;
	delete windows;
	glfwTerminate();
}

std::vector<SBI::Monitor*> *SBI::Input::monitors;
SBI::Monitor* SBI::Input::primaryMonitor;
std::vector<SBI::Window*> *SBI::Input::windows;
SBI::Window *SBI::Input::currentWindow;