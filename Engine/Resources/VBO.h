#pragma once
#include "..\SBE_Internal.h"
#include <GLEW\glew.h>

namespace SBR
{
	namespace f3fPc3fN2sT
	{
		class ModelPart;
		class Model;
	}

	class SBE_API VBO
	{
	public:
		GLuint glid;
		int vertexCount;

		VBO(SBR::f3fPc3fN2sT::ModelPart* part);
		
		void FreeBufferGPU()
		{
			if (glid > 0)
			{
				glDeleteBuffers(1, &glid);
				glid = -1;
			}
		}
	};
}