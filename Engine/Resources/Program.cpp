#include "..\pch.h"
#include "Shader.h"
#include "Program.h"


GLint CreateProgram(std::vector<SBR::Shader*> shaders)
{
	GLint glid = glCreateProgram();
	int a = 0;
	for (auto shader = shaders.begin(); shader != shaders.end(); shader++)
		if ((*shader)->glid > 0)
			glAttachShader(glid, (*shader)->glid);

	glLinkProgram(glid);

	for (auto shader = shaders.begin(); shader != shaders.end(); shader++)
		if ((*shader)->glid > 0)
			glDetachShader(glid, (*shader)->glid);

	GLint isLinked = 0;
	glGetProgramiv(glid, GL_LINK_STATUS, (int *)&isLinked);
	if (isLinked == GL_FALSE)
	{
		GLint maxLength = 0;
		glGetProgramiv(glid, GL_INFO_LOG_LENGTH, &maxLength);
		std::vector<GLchar> infoLog(maxLength);
		glGetProgramInfoLog(glid, maxLength, &maxLength, &infoLog[0]);
		glDeleteProgram(glid);
		glid = -1;
	}

	return glid;
}

SBR::Program::Program(std::vector<SBR::Shader*> shaders)
{
	this->glid = CreateProgram(shaders);
}

SBR::Program::Program(SBR::Shader* s1)
{
	std::vector<SBR::Shader*> shaders;
	shaders.push_back(s1);
	this->glid = CreateProgram(shaders);
}

SBR::Program::Program(SBR::Shader* s1, SBR::Shader* s2)
{
	std::vector<SBR::Shader*> shaders;
	shaders.push_back(s1);
	shaders.push_back(s2);
	this->glid = CreateProgram(shaders);
}