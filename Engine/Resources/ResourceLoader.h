#pragma once
#include "..\SBE_Internal.h"

#include "Loaders\ShaderLoader.h"
#include "Loaders\OBJ_Loader.h"

namespace SBR
{
	class SBE_API Loader
	{
	public:
		static SBR::Shader* Shader(char* path) { return SBR::ShaderLoader::Load(path); }
		static SBR::i3fP3fN2fT::Model* OBJ(char* path) { return SBR::OBJ_Loader::Load(path); }
	};
}