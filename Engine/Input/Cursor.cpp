#include "..\SBE_Internal.h"
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
	double oldPosX = posX;
	double oldPosY = posY;

	glfwGetCursorPos(this->relatedWindow->glfwWindow, &posX, &posY);
	
	moveX = posX - oldPosX;
	moveY = posY - oldPosY;
	
	posXi = (int)floor(posX);
	posYi = (int)floor(posY);
}
