#include "..\pch.h"
#include "Pipeline.h"

SBGM::Pipeline::Pipeline(void)
{
	modelMatrix.push_back(SBM::Matrix4::Identity());
	viewMatrix = SBM::Matrix4::Identity();
	projectionMatrix = SBM::Matrix4::Identity();
}

SBGM::Pipeline::~Pipeline(void)
{
}

void SBGM::Pipeline::Push()
{
	modelMatrix.push_back(SBM::Matrix4(modelMatrix.back()));
}

void SBGM::Pipeline::Pop()
{
	modelMatrix.pop_back();
}

void SBGM::Pipeline::UpdateMatrices(unsigned int programId)
{
	SBM::Matrix4 modelViewMatrix;						//only to save time for vertexshader
	SBM::Matrix4 modelViewProjectionMatrix;				//only to save time for vertexshader
	SBM::Matrix4 normalMatrix;							//only to save time for vertexshader

	modelViewMatrix = viewMatrix * modelMatrix.back();
	modelViewProjectionMatrix = projectionMatrix * viewMatrix * modelMatrix.back();
	normalMatrix = modelMatrix.back().Inversed();

	GLint pmodelMatrix = glGetUniformLocation(programId, "modelMatrix");
	GLint pviewMatrix = glGetUniformLocation(programId, "viewMatrix");
	GLint pmodelViewMatrix = glGetUniformLocation(programId, "modelViewMatrix");
	GLint pmodelViewProjectionMatrix = glGetUniformLocation(programId, "modelViewProjectionMatrix");
	GLint pnormalMatrix = glGetUniformLocation(programId, "normalMatrix");

	glUniformMatrix4fv(pmodelMatrix, 1, GL_FALSE, &modelMatrix.back().m[0]);
	glUniformMatrix4fv(pviewMatrix, 1, GL_FALSE, &viewMatrix.m[0]);
	glUniformMatrix4fv(pmodelViewMatrix, 1, GL_FALSE, &modelViewMatrix.m[0]);
	glUniformMatrix4fv(pmodelViewProjectionMatrix, 1, GL_FALSE, &modelViewProjectionMatrix.m[0]);
	glUniformMatrix3fv(pnormalMatrix, 1, GL_FALSE, &normalMatrix.m[0]);
}

void SBGM::Pipeline::operator*=(SBM::Matrix4 other)
{
	this->modelMatrix.back() *= other;
}

void SBGM::Pipeline::operator=(SBM::Matrix4 other)
{
	this->modelMatrix.back() = other;
}