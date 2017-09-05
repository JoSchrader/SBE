#pragma once
#include "..\pch.h"
#include<stdarg.h>

namespace SBR
{
	class Shader;

	class SBE_EXPORT Program
	{
	public:
		GLint glid;

		Program(std::vector<Shader*> shaders);

		Program(SBR::Shader* s1);

		Program(SBR::Shader* s1, SBR::Shader* s2);
	};
}