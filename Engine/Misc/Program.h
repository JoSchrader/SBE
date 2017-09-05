#include "../pch.h"

#include "..\Resources\SBR.h"

class Program
{
public:
	std::string vertPath;
	std::string fragPath;

	int vertID = 0;
	int fragID = 0;
	int ID = 0;

	Program(std::string vertPath, std::string fragPath) : vertPath(vertPath), fragPath(fragPath)
	{
	}

	bool Load()
	{
		if (vertID != 0) glDeleteShader(vertID);
		if (fragID != 0) glDeleteShader(fragID);
		if (ID != 0) glDeleteProgram(ID);

		//vertID = SBR::ResourceLoader::LoadShader(vertPath);
		//fragID = SBR::ResourceLoader::LoadShader(fragPath);

		if (vertID != 0 && fragID != 0)
		{
			ID = glCreateProgram();
			if (ID != 0)
			{
				glAttachShader(ID, vertID);
				glAttachShader(ID, fragID);
				glLinkProgram(ID);

				GLint programSuccess = GL_TRUE;
				glGetProgramiv(ID, GL_LINK_STATUS, &programSuccess);
				if (programSuccess == GL_TRUE)
				{
					glUseProgram(ID);
					return true;

				}					
			}
		}
		return false;
	}
};