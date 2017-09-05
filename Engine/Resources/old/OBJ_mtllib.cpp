#include "..\pch.h"
#include "OBJ_mtllib.h"

SBR::OBJ_mtllib::OBJ_mtllib()
{
	this->materials = std::vector<OBJ_mtl*>();
}

SBR::OBJ_mtllib::~OBJ_mtllib()
{
}

SBR::OBJ_mtl* SBR::OBJ_mtllib::GetMaterial(std::string mtlName)
{
	for (int i = 0; i < this->materials.size(); i++)
		if (mtlName.compare(this->materials[i]->name) == 0)
			return this->materials[i];
	
	return nullptr;
}
