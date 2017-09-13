#include "..\SBE_Internal.h"
#include "VBO.h"
#include "Model_f3fPc3fN2sT.h"

SBR::VBO::VBO(SBR::f3fPc3fN2sT::ModelPart* part)
{
	this->vertexCount = part->amountOfVertexes;
	glGenBuffers(1, &this->glid);
	glBindBuffer(GL_ARRAY_BUFFER, this->glid);
	glBufferData(GL_ARRAY_BUFFER, part->amountOfVertexes * sizeof(SBR::f3fPc3fN2sT::CompressedVertex), part->vertexes, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}