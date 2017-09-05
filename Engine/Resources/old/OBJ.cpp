#include "..\pch.h"
#include "OBJ.h"

SBR::OBJ::OBJ()
{
	this->objObjects = std::vector<OBJ_Object*>();
	mtllib = nullptr;
}

SBR::OBJ::~OBJ()
{
}