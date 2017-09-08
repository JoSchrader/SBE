#pragma once
#include "..\pch.h"
#include "..\Math\SBM.h"
#include "Program.h"

#include "Model.h"

namespace SBR
{
	class SBE_EXPORT Vertex
	{
	public:
		SBM::Vector3 position;
		SBM::Vector3 normal;
		SBM::Vector2 uv;

		Vertex(SBM::Vector3 position, SBM::Vector3 normal, SBM::Vector2 uv)
		{
			this->position = position;
			this->normal = normal;
			this->uv = uv;
		}

		Vertex()
		{

		}
	};

	class SBE_EXPORT Triangle
	{
	public:
		Vertex vertices[3];

		Triangle(Vertex v1, Vertex v2, Vertex v3)
		{
			vertices[0] = v1;
			vertices[1] = v2;
			vertices[2] = v3;
		}

		Vertex operator[](int index)
		{
			return vertices[index];
		}
	};

	class SBE_EXPORT VertexIndex
	{
	public:
		int posIndex;
		int uvIndex;
		int normalIndex;

		VertexIndex(int posIndex, int uvIndex, int normalIndex)
		{
			this->posIndex = posIndex;
			this->uvIndex = uvIndex;
			this->normalIndex = normalIndex;
		}

		VertexIndex()
		{
			posIndex = -1;
			uvIndex = -1;
			normalIndex = -1;
		}
	};

	class SBE_EXPORT TriangleIndex
	{
	public:
		VertexIndex verticeIndices[3];

		TriangleIndex(VertexIndex v1, VertexIndex v2, VertexIndex v3)
		{
			verticeIndices[0] = v1;
			verticeIndices[1] = v2;
			verticeIndices[2] = v3;
		}

		VertexIndex operator[](int index)
		{
			return verticeIndices[index];
		}

	};

	class SBE_EXPORT Mesh
	{
	public:
		std::vector<SBM::Vector3> positions;
		std::vector<SBM::Vector3> normals;
		std::vector<SBM::Vector2> uvs;

		std::vector<TriangleIndex> triangleIndexes;

		Mesh()
		{

		}

		~Mesh()
		{

		}

		SBR::i3fP3fN2fT::Model* To_i3fP3fN2fT_Model()
		{
			SBR::i3fP3fN2fT::Model* model = new SBR::i3fP3fN2fT::Model();

		/*	model->amountOfParts = 1;
			model->parts = (ModelPart**) malloc(sizeof(ModelPart*) * 1);
			model->name = "BlahBlahModelName";

			SBR::i3fP3fN2fT::ModelPart* part = new SBR::i3fP3fN2fT::ModelPart();
			part->texturePath = "BlahBlahTexturePath";
			part->name = "BlahBlahModelPartName";
			part->materialPath = "BlahBlahMaterialName";
			part->amountOfTriangles = (int) this->triangleIndexes.size();
			part->triangles = (SBR::i3fP3fN2fT::TriangleIndexData*) &triangleIndexes[0];

			model->meshData = new SBR::i3fP3fN2fT::MeshData();
			model->meshData->amountOfNormals = (int)this->normals.size();
			model->meshData->amountOfPositions = (int)this->positions.size();
			model->meshData->amountOfUVs = (int)this->uvs.size();
			model->meshData->normalData = &this->normals[0];
			model->meshData->positionData = &this->positions[0];
			model->meshData->uvData = &this->uvs[0];

			model->parts[0] = part;*/

			return model;
		}
	};

	class SBE_EXPORT VBO
	{
	public:
		class SBE_EXPORT VBO_Vertex
		{
		public:
			GLfloat posX; // 4byte
			GLfloat posY; // 4byte
			GLfloat posZ; // 4byte
			GLuint packedNormals; //4 byte
			GLshort uvX; // 2byte
			GLshort uvY; // 2byte


			//Assuming normal and uv are normalised
			VBO_Vertex(Vertex vertex)
			{
				this->posX = vertex.position.x;
				this->posY = vertex.position.y;
				this->posZ = vertex.position.z;

				this->packedNormals = 0;
				this->packedNormals = this->packedNormals | (0 << 30); // upper 2 bit not used
				this->packedNormals = this->packedNormals | ((int)(vertex.normal.x * 1023) << 20); // map normalised normal to [0,1023] integer
				this->packedNormals = this->packedNormals | ((int)(vertex.normal.y * 1023) << 10); // map normalised normal to [0,1023] integer
				this->packedNormals = this->packedNormals | ((int)(vertex.normal.z * 1023) << 0); // map normalised normal to [0,1023] integer

				this->uvX = (GLshort)(vertex.uv.x * 65535); // map normalised uv to [0,65535]
				this->uvY = (GLshort)(vertex.uv.y * 65535); // map normalised uv to [0,65535]
			}
		};

		GLuint glid;
		int vertexCount;

		VBO(Mesh* mesh)
		{
			glid = -1;
			vertexCount = (int)mesh->triangleIndexes.size() * 3;

			VBO_Vertex* vertecis;
			vertecis = (VBO_Vertex*)malloc(sizeof(VBO_Vertex)*mesh->triangleIndexes.size() * 3);

			int vertexIndex = 0;
			for (auto triangle = mesh->triangleIndexes.begin(); triangle != mesh->triangleIndexes.end(); triangle++)
				for (int i = 0; i < 3; i++)
					vertecis[vertexIndex++] = VBO_Vertex(Vertex(mesh->positions[(*triangle)[i].posIndex], mesh->normals[(*triangle)[i].normalIndex], mesh->uvs[(*triangle)[i].normalIndex]));

			UploadToGPU(vertecis, vertexCount);

			delete vertecis;
		}

		~VBO()
		{
			FreeBufferGPU();
		}
	private:
		void UploadToGPU(VBO_Vertex* vertecis, int vertexCount)
		{
			glGenBuffers(1, &glid);
			glBindBuffer(GL_ARRAY_BUFFER, glid);
			glBufferData(GL_ARRAY_BUFFER, vertexCount * sizeof(VBO::VBO_Vertex), vertecis, GL_STATIC_DRAW);

			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

			glBindVertexArray(0);
			glBindBuffer(GL_ARRAY_BUFFER, 0);
		}

		void FreeBufferGPU()
		{
			if (glid > 0)
			{
				glDeleteBuffers(1, &glid);
				glid = -1;
			}
		}
	};

	class SBE_EXPORT VAO
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
