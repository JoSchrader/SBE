#pragma once
#include "Model.h"

namespace SBR
{
	namespace f3fPc3fN2sT
	{
		class CompressedVertex
		{
		public:
			GLfloat posX; // 4byte
			GLfloat posY; // 4byte
			GLfloat posZ; // 4byte
			GLuint packedNormals; //4 byte
			GLshort uvX; // 2byte
			GLshort uvY; // 2byte
		};

		class SBE_EXPORT ModelPart
		{
		public:
			CompressedVertex* triangles;
			int amountOfTriangles;
		};

		class SBE_EXPORT Model
		{
			
		};
	}
}