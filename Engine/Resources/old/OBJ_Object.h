#pragma once
#include "..\pch.h"
#include "Resource.h"

class Mesh;
namespace SBR
{
	class OBJ_mtl;
	class OBJ_Object: public Resource
	{
	public:
		GLint faceCount;
		OBJ_mtl* material;
		Mesh* mesh;
		std::string name;

		OBJ_Object(std::string& name);
		~OBJ_Object();
		void UploadToGPU();
	};	
}