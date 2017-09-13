#pragma once
#include "..\SBE_Internal.h"
#include<stdarg.h>

#include <vector>

namespace SBR
{
	class Shader;

	class SBE_API Program
	{
	public:
		GLint glid;

		Program(std::vector<Shader*> shaders);

		Program(SBR::Shader* s1);

		Program(SBR::Shader* s1, SBR::Shader* s2);
	};
}