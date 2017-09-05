#pragma once
#include "..\pch.h"
#include "Resource.h"
#include "OBJ_mtl.h"

namespace SBR
{
	class OBJ_mtllib : public Resource
	{
	public:
		std::vector<OBJ_mtl*> materials;
		OBJ_mtl* GetMaterial(std::string mtlName);
		OBJ_mtllib();
		~OBJ_mtllib();
	};	
}