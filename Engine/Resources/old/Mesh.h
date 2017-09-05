#pragma once
#include "..\pch.h"

namespace SBR
{

	class SBE_EXPORT VertexIndex
	{
	public:
		int posIndex;
		int uvIndex;
		int normalIndex;
		
		VertexIndex()
		{

		}

		VertexIndex(int posIndex, int uvIndex, int normalIndex)
		{
			this->posIndex = posIndex;
			this->uvIndex = uvIndex;
			this->normalIndex = normalIndex;
		}
	};

	class SBE_EXPORT TriangleIndex
	{
	public:
		VertexIndex verticesIndexes[3];

		TriangleIndex(VertexIndex v1, VertexIndex v2, VertexIndex v3)
		{
			verticesIndexes[0] = v1;
			verticesIndexes[1] = v2;
			verticesIndexes[2] = v3;
		}

		VertexIndex* operator[] (const int index)
		{
			if (index < 0 || index > 2)
				return nullptr;
			else
				return &(verticesIndexes[index]);
		}
	};

	class SBE_EXPORT MeshData
	{
	public:
		std::vector<vec3> positions;
		std::vector<vec2> uvs;
		std::vector<vec3> normals;
	};

	class SBE_EXPORT Mesh
	{
	public:
		std::vector<TriangleIndex> triangleIndexes;
		MeshData* meshData;
	};

	class SBE_EXPORT Vertex
	{
	public:
		vec3 position;
		vec2 uv;
		vec3 normal;
	};

	class SBE_EXPORT Triangle
	{
	public:
		Vertex vertices[3];

		Vertex* operator[] (const int index)
		{
			if (index < 0 || index > 2)
				return nullptr;
			else
				return &(vertices[index]);
		}
	};

	class SBE_EXPORT TriangleIterator
	{
	public:
		Mesh* mesh;
		int index;

		TriangleIterator(Mesh* mesh) : mesh(mesh), index(0)
		{
		}


		TriangleIterator()
		{

		}

		bool HasNext()
		{
			return index < mesh->triangleIndexes.size();
		}

		Triangle Next()
		{
			Triangle ret;
			TriangleIndex triIndex = mesh->triangleIndexes[index];
			for (int i = 0; i < 3; i++)
			{
				ret[i]->normal = &mesh->meshData->positions[(triIndex[i])->posIndex];
				ret[i]->uv = &mesh->meshData->uvs[(triIndex[i])->uvIndex];
				ret[i]->normal = &mesh->meshData->normals[(triIndex[i])->normalIndex];
			}
			index++;
			return ret;
		}
	};
}