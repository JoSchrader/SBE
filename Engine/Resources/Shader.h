#pragma once
#include "..\SBE_Internal.h"
#include <GLEW\glew.h>
#include <string.h>

namespace SBR
{
	enum SBE_API ShaderType
	{
		VERTEX_SHADER = GL_VERTEX_SHADER,
		TESS_CONTROL_SHADER = GL_TESS_CONTROL_SHADER,
		TESS_EVALUATION_SHADER = GL_TESS_EVALUATION_SHADER,
		GEOMETRY_SHADER = GL_GEOMETRY_SHADER,
		FRAGMENT_SHADER = GL_FRAGMENT_SHADER,
		COMPUTE_SHADER = GL_COMPUTE_SHADER,
		UNDEFINED_SHADER = -1
	};

	class SBE_API Shader
	{
	public:
		GLint glid;
		ShaderType type;
		
		Shader(ShaderType type, char* source)
		{
			this->glid = -1;
			this->type = type;

			if (source == nullptr)
				return;

			glid = glCreateShader(type);
			int srcLen = (int) strlen(source);
			glShaderSource(glid, 1, &source, &srcLen);
			glCompileShader(glid);

			GLint success = 0;
			glGetShaderiv(glid, GL_COMPILE_STATUS, &success);
			if (success == GL_FALSE)
			{
				glDeleteShader(glid);
				glid = -1;
			}
		}

		~Shader()
		{

		}
	};	
}