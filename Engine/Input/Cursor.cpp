#include "..\pch.h"
#include "Cursor.h"
#include "Window.h"
#include "Input.h"


SBI::Cursor::Cursor(Window* relatedWindow)
{
	this->relatedWindow = relatedWindow;
}

SBI::Cursor::~Cursor()
{
}

GLvoid SBI::Cursor::Update()
{
	GLdouble oldPosX = posX;
	GLdouble oldPosY = posY;

	glfwGetCursorPos(this->relatedWindow->glfwWindow, &posX, &posY);
	
	moveX = posX - oldPosX;
	moveY = posY - oldPosY;
	
	posXi = (GLint)floor(posX);
	posYi = (GLint)floor(posY);
}
