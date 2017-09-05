#include "..\pch.h"
#include "Time.h"
#include "Input.h"
#include "Window.h"

SBI::Time::Time(void)
{
	this->deltaTime = 0;
	this->fps = 0;
	this->ellapsedTime = 0;
	this->timeScale = 1;
	this->fixedTime = 0;
}

SBI::Time::~Time(void)
{
}

void SBI::Time::Update()
{
	if (this->fixedTime == 0)
	{
		GLfloat tempTime = (GLfloat)glfwGetTime();
		deltaTime = (tempTime - this->ellapsedTime)*timeScale;
		ellapsedTime = tempTime;
		fps = 1.0f / deltaTime;
	}
	else
	{
		ellapsedTime += fixedTime;
		deltaTime = fixedTime;
		fps = 1.0f / deltaTime;
	}
}


GLfloat SBI::Time::EllapsedTime()
{
	return SBI::Input::currentWindow->time->ellapsedTime;
}

GLfloat SBI::Time::DeltaTime()
{
	return SBI::Input::currentWindow->time->deltaTime;
}

GLfloat SBI::Time::Fps()
{
	return SBI::Input::currentWindow->time->fps;
}