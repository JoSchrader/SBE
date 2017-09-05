#include "..\pch.h"
#include "ResourceLoader.h"
#include "..\Math\Vector3.h"
#include "..\Math\Vector2.h"
using namespace SBM;

GLint SBR::ResourceLoader::LoadShader(std::string path)
{
	int glid = 0;

	if (boost::filesystem::exists(path))
	{
		int byteSize = (int)boost::filesystem::file_size(path);
		GLchar* shaderString = (GLchar*)calloc(byteSize + 1, sizeof(GLchar));
		FILE* file;
		errno_t err = fopen_s(&file, path.c_str(), "rb");
		if (err != 0)
		{
			return 0;
		}

		fread(shaderString, sizeof(GLchar), byteSize, file);
		shaderString[byteSize] = 0;
		fclose(file);

		std::string extension = boost::filesystem::extension(path);

		if (extension == ".vert")
			glid = glCreateShader(GL_VERTEX_SHADER);
		else if (extension == ".tesc")
			glid = glCreateShader(GL_TESS_CONTROL_SHADER);
		else if (extension == ".tese")
			glid = glCreateShader(GL_TESS_EVALUATION_SHADER);
		else if (extension == ".geom")
			glid = glCreateShader(GL_GEOMETRY_SHADER);
		else if (extension == ".frag")
			glid = glCreateShader(GL_FRAGMENT_SHADER);
		else if (extension == ".comp")
			glid = glCreateShader(GL_COMPUTE_SHADER);
		else
			glid = 0;

		if (glid == 0)
		{
			free(shaderString);
			return 0;
		}

		glShaderSource(glid, 1, (const GLchar**)&shaderString, NULL);
		glCompileShader(glid);

		GLint shaderCompiled = GL_FALSE;
		glGetShaderiv(glid, GL_COMPILE_STATUS, &shaderCompiled);
		if (shaderCompiled != GL_TRUE)
		{
			glDeleteShader(glid);
			glid = 0;
		}

		free(shaderString);
	}

	return glid;
}