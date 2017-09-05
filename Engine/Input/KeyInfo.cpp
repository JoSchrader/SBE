#include "..\pch.h"
#include "KeyInfo.h"

using namespace SBI;

KeyInfo::KeyInfo(void)
{
	this->deltaTime=0;
	this->key=(Keys)0;
	this->pressed=false;
	this->toDown=false;
	this->toUp=false;
}

KeyInfo::KeyInfo(Keys key)
{
	this->deltaTime=0;
	this->key=key;
	this->pressed=false;
	this->toDown=false;
	this->toUp=false;
}


KeyInfo::~KeyInfo(void)
{
}