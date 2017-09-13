#include "..\SBE_Internal.h"

#include "VideoMode.h"

SBI::VideoMode::VideoMode()
{
}

SBI::VideoMode::VideoMode(int width, int height, int redBits, int greenBits, int blueBits, int refreshRate)
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
