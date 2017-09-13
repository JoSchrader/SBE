#pragma once
#include "..\SBE_Internal.h"

#include "Program.h"

namespace SBR
{
	class VBO;

	class SBE_API VAO
	{
	public:
		GLuint glid;

		VAO(VBO* vbo, SBR::Program* program)
		{
			glid = -1;
			glGenVertexArrays(1, &glid);
			glBindVertexArray(glid);

			int shaderPosIndex = glGetAttribLocation(program->glid, "position");
			int shaderNormalIndex = glGetAttribLocation(program->glid, "normal");
			int shaderTextureIndex = glGetAttribLocation(program->glid, "UV");

			glEnableVertexAttribArray(shaderPosIndex);
			glEnableVertexAttribArray(shaderNormalIndex);
			glEnableVertexAttribArray(shaderTextureIndex);

			glVertexArrayAttribFormat(glid, shaderPosIndex, 3, GL_FLOAT, GL_FALSE, 0);// 3 GLFloat Position
			glVertexArrayAttribFormat(glid, shaderNormalIndex, 4, GL_INT_2_10_10_10_REV, GL_TRUE, 12);// Packed normals
			glVertexArrayAttribFormat(glid, shaderNormalIndex, 2, GL_SHORT, GL_TRUE, 16);// Packed uvs

			glVertexArrayAttribBinding(glid, shaderPosIndex, 0);
			glVertexArrayAttribBinding(glid, shaderNormalIndex, 0);
			glVertexArrayAttribBinding(glid, shaderTextureIndex, 0);
		}

		~VAO()
		{
			glDeleteVertexArrays(1, &glid);
		}
	};
}
