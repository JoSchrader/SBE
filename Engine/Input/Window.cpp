#include "..\SBE_Internal.h"
#include "Input.h"
#include "Window.h"
#include "Keyboard.h"
#include "Cursor.h"
#include "Time.h"

SBI::Window::Window(GLFWwindow* glfwwindow)
{
	this->glfwWindow = glfwwindow;
	this->keyboard = new Keyboard(this);
	this->cursor = new Cursor(this);
	this->time = new Time();

	this->MakeCurrent();
}

SBI::Window::~Window()
{
	delete keyboard;
	delete cursor;
	delete time;
}

GLvoid SBI::Window::GetWindowSize(GLint* width, GLint* height)
{
	glfwGetWindowSize(this->glfwWindow, width, height);
}

GLvoid SBI::Window::SetWindowSize(GLint width, GLint height)
{
	glfwSetWindowSize(this->glfwWindow, width, height);
}

GLvoid SBI::Window::GetFramebufferSize(GLint* width, GLint* height)
{
	glfwGetFramebufferSize(this->glfwWindow, width, height);
}

GLvoid SBI::Window::GetWindowPos(GLint* width, GLint* height)
{
	glfwGetWindowPos(this->glfwWindow, width, height);
}

GLvoid SBI::Window::SetWindowPos(GLint width, GLint height)
{
	glfwSetWindowPos(this->glfwWindow, width, height);
}

GLvoid SBI::Window::SetTitle(const char* title)
{
	this->title = title;
	glfwSetWindowTitle(this->glfwWindow, title);
}

GLboolean SBI::Window::IsFocused()
{
	return(GLboolean)glfwGetWindowAttrib(this->glfwWindow, GLFW_FOCUSED);
}

GLboolean SBI::Window::IsIconified()
{
	return(GLboolean)glfwGetWindowAttrib(this->glfwWindow, GLFW_ICONIFIED);
}
GLboolean SBI::Window::IsVisible()
{
	return (GLboolean)glfwGetWindowAttrib(this->glfwWindow, GLFW_VISIBLE);
}

GLboolean SBI::Window::ShouldClose()
{
	return glfwWindowShouldClose(this->glfwWindow);
}

GLvoid SBI::Window::MakeCurrent()
{
	glfwMakeContextCurrent(this->glfwWindow);
	SBI::Input::currentWindow = this;
}

GLvoid SBI::Window::Hide()
{
	glfwHideWindow(this->glfwWindow);
}

GLvoid SBI::Window::Show()
{
	glfwShowWindow(this->glfwWindow);
}

GLvoid SBI::Window::Iconify()
{
	glfwIconifyWindow(this->glfwWindow);
}

GLvoid SBI::Window::SwapBuffers()
{
	glfwSwapBuffers(this->glfwWindow);
}

GLvoid SBI::Window::CatchCursor()
{
	glfwSetInputMode(glfwWindow, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	GLdouble x, y;
	glfwGetCursorPos(this->glfwWindow, &x, &y);

	this->cursor->posX = (GLint)x;
	this->cursor->posY = (GLint)y;
}

GLvoid SBI::Window::ReleaseCursor()
{
	glfwSetInputMode(glfwWindow, GLFW_CURSOR, GLFW_CURSOR_NORMAL);

	GLdouble x, y;
	glfwGetCursorPos(this->glfwWindow, &x, &y);

	this->cursor->posX = (GLint)x;
	this->cursor->posY = (GLint)y;
}

GLvoid SBI::Window::Update()
{
	this->cursor->Update();
	this->keyboard->Update();
	this->time->Update();
}

SBI::WindowHint SBI::Window::GetWindowHint()
{
	SBI::WindowHint windowHint;

	windowHint.resizable = (GLboolean)glfwGetWindowAttrib(this->glfwWindow, GLFW_RESIZABLE);
	windowHint.visible = (GLboolean)glfwGetWindowAttrib(this->glfwWindow, GLFW_VISIBLE);
	windowHint.decorated = (GLboolean)glfwGetWindowAttrib(this->glfwWindow, GLFW_DECORATED);
	windowHint.red_bits = glfwGetWindowAttrib(this->glfwWindow, GLFW_RED_BITS);
	windowHint.green_bits = glfwGetWindowAttrib(this->glfwWindow, GLFW_GREEN_BITS);
	windowHint.blue_bits = glfwGetWindowAttrib(this->glfwWindow, GLFW_BLUE_BITS);
	windowHint.alpha_bits = glfwGetWindowAttrib(this->glfwWindow, GLFW_ALPHA_BITS);
	windowHint.stencil_bits = glfwGetWindowAttrib(this->glfwWindow, GLFW_STENCIL_BITS);
	windowHint.accum_red_bits = glfwGetWindowAttrib(this->glfwWindow, GLFW_ACCUM_RED_BITS);
	windowHint.accum_green_bits = glfwGetWindowAttrib(this->glfwWindow, GLFW_ACCUM_GREEN_BITS);
	windowHint.accum_blue_bits = glfwGetWindowAttrib(this->glfwWindow, GLFW_ACCUM_BLUE_BITS);
	windowHint.accum_alpha_bits = glfwGetWindowAttrib(this->glfwWindow, GLFW_ACCUM_ALPHA_BITS);
	windowHint.aux_buffer = glfwGetWindowAttrib(this->glfwWindow, GLFW_AUX_BUFFERS);
	windowHint.samples = glfwGetWindowAttrib(this->glfwWindow, GLFW_SAMPLES);
	windowHint.refresh_rate = glfwGetWindowAttrib(this->glfwWindow, GLFW_REFRESH_RATE);
	windowHint.stereo = (GLboolean)glfwGetWindowAttrib(this->glfwWindow, GLFW_STEREO);
	windowHint.srgb_capable = (GLboolean)glfwGetWindowAttrib(this->glfwWindow, GLFW_SRGB_CAPABLE);
	windowHint.client_api = (SBI::CLIENT_API)glfwGetWindowAttrib(this->glfwWindow, GLFW_CLIENT_API);
	windowHint.context_version_major = glfwGetWindowAttrib(this->glfwWindow, GLFW_CONTEXT_VERSION_MAJOR);
	windowHint.context_version_minor = glfwGetWindowAttrib(this->glfwWindow, GLFW_CONTEXT_VERSION_MINOR);
	windowHint.context_robustness = (SBI::CONTEXT_ROBUSTNESS)glfwGetWindowAttrib(this->glfwWindow, GLFW_CONTEXT_ROBUSTNESS);
	windowHint.opengl_forward_compatible = (GLboolean)glfwGetWindowAttrib(this->glfwWindow, GLFW_OPENGL_FORWARD_COMPAT);
	windowHint.opengl_debug_context = (GLboolean)glfwGetWindowAttrib(this->glfwWindow, GLFW_OPENGL_DEBUG_CONTEXT);
	windowHint.opengl_profile = (SBI::OPENGL_PROFILE)glfwGetWindowAttrib(this->glfwWindow, GLFW_OPENGL_PROFILE);

	return windowHint;
}

GLvoid SBI::Window::WindowSizeCallback(GLint width, GLint height)
{
	this->width = width;
	this->height = height;
}