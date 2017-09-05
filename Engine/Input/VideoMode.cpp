#include "..\pch.h"

#include "VideoMode.h"

SBI::VideoMode::VideoMode()
{
}

SBI::VideoMode::VideoMode(GLint width, GLint height, GLint redBits, GLint greenBits, GLint blueBits, GLint refreshRate)
{
	this->width = width;
	this->height = height;
	this->redBits = redBits;
	this->greenBits = greenBits;
	this->blueBits = blueBits;
	this->refreshRate = refreshRate;
}


SBI::VideoMode::~VideoMode()
{
}
