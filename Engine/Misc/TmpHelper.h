#pragma once
#include "pch.h"
#include "..\Math\SBM.h"
#include "..\Input\SBI.h"

using namespace SBM;

struct  V3_T2_N3
{
	Vector3 vertex;
	Vector2 texture;
	Vector3 normal;

	V3_T2_N3(Vector3 vertex, Vector2 texture, Vector3 normal)
	{
		this->vertex = vertex;
		this->texture = texture;
		this->normal = normal;
	}
	V3_T2_N3(float vx, float vy, float vz, float tx, float ty, float nx, float ny, float nz)
	{
		this->vertex = Vector3(vx, vy, vz);
		this->texture = Vector2(tx, ty);
		this->normal = Vector3(nx, ny, nz);
	}

	V3_T2_N3()
	{
		this->vertex = Vector3();
		this->texture = Vector2();
		this->normal = Vector3();
	}
};

int LoadProgram(int vertexShader, int fragmentShader, int geometryShader)
{
	GLuint programHandle = glCreateProgram();
	if(vertexShader > 0)
		glAttachShader(programHandle, vertexShader);
	if(fragmentShader > 0)
		glAttachShader(programHandle, fragmentShader);
	if(geometryShader > 0)
		glAttachShader(programHandle, geometryShader);
	glLinkProgram(programHandle);

	GLint programSuccess = GL_TRUE;
	glGetProgramiv(programHandle, GL_LINK_STATUS, &programSuccess);
	if (programSuccess != GL_TRUE)
	{
		printf("Error linking program %d!\n", programHandle);
		glDeleteProgram(programHandle);
		programHandle = 0;
	}

	return programHandle;
}

GLint CreateCube(int* vertexCount)
{
	// 3 vertices for a triangle - 2 triangles for one side - 6 sides
	int vertexAmount = 3 * 2 * 6;

	V3_T2_N3* plane = (V3_T2_N3*)malloc(sizeof(V3_T2_N3)*vertexAmount);

	//oben  
	int i = 0;
	plane[i++] = V3_T2_N3(1, 1, -1, 0, 0, 0, 1, 0);
	plane[i++] = V3_T2_N3(-1, 1, -1, 0, 1, 0, 1, 0);
	plane[i++] = V3_T2_N3(-1, 1, 1, 1, 1, 0, 1, 0);

	plane[i++] = V3_T2_N3(-1, 1, 1, 1, 1, 0, 1, 0);
	plane[i++] = V3_T2_N3(1, 1, 1, 1, 0, 0, 1, 0);
	plane[i++] = V3_T2_N3(1, 1, -1, 0, 0, 0, 1, 0);

	//unten
	plane[i++] = V3_T2_N3(1, -1, 1, 1, 0, 0, -1, 0);
	plane[i++] = V3_T2_N3(-1, -1, 1, 1, 1, 0, -1, 0);
	plane[i++] = V3_T2_N3(-1, -1, -1, 0, 1, 0, -1, 0);

	plane[i++] = V3_T2_N3(-1, -1, -1, 0, 1, 0, -1, 0);
	plane[i++] = V3_T2_N3(1, -1, -1, 0, 0, 0, -1, 0);
	plane[i++] = V3_T2_N3(1, -1, 1, 1, 0, 0, -1, 0);

	//links
	plane[i++] = V3_T2_N3(-1, -1, -1, 1, 0, -1, 0, 0);
	plane[i++] = V3_T2_N3(-1, -1, 1, 1, 1, -1, 0, 0);
	plane[i++] = V3_T2_N3(-1, 1, 1, 0, 1, -1, 0, 0);

	plane[i++] = V3_T2_N3(-1, 1, 1, 0, 1, -1, 0, 0);
	plane[i++] = V3_T2_N3(-1, 1, -1, 0, 0, -1, 0, 0);
	plane[i++] = V3_T2_N3(-1, -1, -1, 1, 0, -1, 0, 0);

	//recht
	plane[i++] = V3_T2_N3(1, 1, -1, 0, 0, 1, 0, 0);
	plane[i++] = V3_T2_N3(1, 1, 1, 0, 1, 1, 0, 0);
	plane[i++] = V3_T2_N3(1, -1, 1, 1, 1, 1, 0, 0);

	plane[i++] = V3_T2_N3(1, -1, 1, 1, 1, 1, 0, 0);
	plane[i++] = V3_T2_N3(1, -1, -1, 1, 0, 1, 0, 0);
	plane[i++] = V3_T2_N3(1, 1, -1, 0, 0, 1, 0, 0);

	//vorne
	plane[i++] = V3_T2_N3(-1, 1, 1, 0, 1, 0, 0, 1);
	plane[i++] = V3_T2_N3(-1, -1, 1, 1, 1, 0, 0, 1);
	plane[i++] = V3_T2_N3(1, -1, 1, 1, 0, 0, 0, 1);

	plane[i++] = V3_T2_N3(1, -1, 1, 1, 0, 0, 0, 1);
	plane[i++] = V3_T2_N3(1, 1, 1, 0, 0, 0, 0, 1);
	plane[i++] = V3_T2_N3(-1, 1, 1, 0, 1, 0, 0, 1);

	//Hinten
	plane[i++] = V3_T2_N3(1, -1, -1, 1, 0, 0, 0, -1);
	plane[i++] = V3_T2_N3(-1, -1, -1, 1, 1, 0, 0, -1);
	plane[i++] = V3_T2_N3(-1, 1, -1, 0, 1, 0, 0, -1);

	plane[i++] = V3_T2_N3(-1, 1, -1, 0, 1, 0, 0, -1);
	plane[i++] = V3_T2_N3(1, 1, -1, 0, 0, 0, 0, -1);
	plane[i++] = V3_T2_N3(1, -1, -1, 1, 0, 0, 0, -1);


	GLuint cube_id = 0;
	glGenBuffers(1, &cube_id);
	glBindBuffer(GL_ARRAY_BUFFER, cube_id);
	glBufferData(GL_ARRAY_BUFFER, vertexAmount*sizeof(V3_T2_N3), plane, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	*vertexCount = vertexAmount;
	return cube_id;
}

void DrawVBO(int vboid, int vertexCount, int shaderProgId)
{
	int vertex = glGetAttribLocation(shaderProgId, "vertex"); //0
	int UV = glGetAttribLocation(shaderProgId, "UV"); //0
	int normal = glGetAttribLocation(shaderProgId, "normal"); //0

	glBindBuffer(GL_ARRAY_BUFFER, vboid);

	glEnableVertexAttribArray(vertex);
	glVertexAttribPointer(vertex, 3, GL_FLOAT, GL_FALSE, sizeof(V3_T2_N3), 0);
	glEnableVertexAttribArray(UV);
	glVertexAttribPointer(UV, 2, GL_FLOAT, GL_FALSE, sizeof(V3_T2_N3), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(normal);
	glVertexAttribPointer(normal, 3, GL_FLOAT, GL_FALSE, sizeof(V3_T2_N3), (void*)(5 * sizeof(float)));

	glDrawArrays(GL_TRIANGLES, 0, vertexCount);

	glDisableVertexAttribArray(vertex);
	glDisableVertexAttribArray(UV);
	glDisableVertexAttribArray(normal);	

	glBindBuffer(GL_ARRAY_BUFFER, 0);
}
