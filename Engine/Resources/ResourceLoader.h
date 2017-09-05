#pragma once
#include "..\pch.h"

#include "Loaders\ShaderLoader.h"
#include "Loaders\OBJ_Loader.h"

namespace SBR
{
	class SBE_EXPORT Loader
	{
	public:
		static SBR::Shader* Shader(char* path) { return SBR::ShaderLoader::Load(path); }
		static SBR::OBJ* OBJ(char* path) { return SBR::OBJ_Loader::Load(path); }
	};
}