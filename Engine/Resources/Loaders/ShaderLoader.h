#pragma once
#include "FileOperations.h"
#include "..\Shader.h"

namespace SBR
{
	class SBE_EXPORT ShaderLoader
	{
	public:
		static SBR::Shader* Load(char* path)
		{
			if (SBR::File::Exist(path))
			{
				char extension[10];
				SBR::File::Extension(path, extension, 10);

				int size = 0;
				char* source = SBR::File::Read(path, &size);

				SBR::Shader* shader;

				if (strcmp(extension, ".vert") == 0)
					shader = new SBR::Shader(SBR::ShaderType::VERTEX_SHADER, source);
				else if (strcmp(extension, ".tesc") == 0)
					shader = new SBR::Shader(SBR::ShaderType::TESS_CONTROL_SHADER, source);
				else if (strcmp(extension, ".tese") == 0)
					shader = new SBR::Shader(SBR::ShaderType::TESS_EVALUATION_SHADER, source);
				else if (strcmp(extension, ".geom") == 0)
					shader = new SBR::Shader(SBR::ShaderType::GEOMETRY_SHADER, source);
				else if (strcmp(extension, ".frag") == 0)
					shader = new SBR::Shader(SBR::ShaderType::FRAGMENT_SHADER, source);
				else if (strcmp(extension, ".comp") == 0)
					shader = new SBR::Shader(SBR::ShaderType::COMPUTE_SHADER, source);
				else
					shader = new SBR::Shader(SBR::ShaderType::UNDEFINED_SHADER, nullptr);

				free(source);
				return shader;
			}
			else
			{
				return new SBR::Shader(SBR::ShaderType::UNDEFINED_SHADER, nullptr);
			}
		}
	};
}
