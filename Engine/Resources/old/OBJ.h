#pragma once
#include "..\pch.h"
#include "Resource.h"
#include "OBJ_Object.h"
#include "OBJ_mtllib.h"

namespace SBR
{
	class OBJ : public Resource
	{
	public:
		std::vector<OBJ_Object*> objObjects;
		OBJ_mtllib* mtllib;
		OBJ();
		~OBJ();
	};	
}