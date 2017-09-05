#pragma once
#include "Model.h"

namespace SBR
{
	namespace i3fP3fN2fT
	{
		class SBE_EXPORT MeshData
		{
		public:
			SBM::Vector3* positionData;
			SBM::Vector3* normalData;
			SBM::Vector2* uvData;

			int amountOfPositions;
			int amountOfNormals;
			int amountOfUVs;
		};

		class SBE_EXPORT TriangleIndexData
		{
		public:
			int position1;
			int normal1;
			int texture1;
			int position2;
			int normal2;
			int texture2;
			int position3;
			int normal3;
			int texture3;
		};

		class SBE_EXPORT ModelPart : public  SBR::ModelPart
		{
		public:
			TriangleIndexData* triangles;
			int amountOfTriangles;

			int GetSize()
			{
				int size = 0;
				size += 4; //offset name
				size += 4; //offset texturePath
				size += 4; //offset materialPath
				size += 4; //amount of triangles
				size += 4; //offset triangle data
				size += (int)strlen(name) + 1;
				size += (int)strlen(texturePath) + 1;
				size += (int)strlen(materialPath) + 1;
				size += sizeof(TriangleIndexData) * amountOfTriangles;
				return size;
			}

			void Save(char* buffer)
			{
				int* offsetName = (int*)buffer;
				int* offsetTexturePath = (int*)(buffer + 4);
				int* offsetMaterialPath = (int*)(buffer + 8);
				int* amountOfTriangles = (int*)(buffer + 12);
				int* offsetTriangleData = (int*)(buffer + 16);

				char* name = buffer + 20;
				char* texturePath = name + strlen(this->name) + 1;
				char* materialPath = texturePath + strlen(this->texturePath) + 1;
				TriangleIndexData* triangleData = (TriangleIndexData*)(materialPath + strlen(this->materialPath) + 1);


				*offsetName = (int)(name - buffer);
				*offsetTexturePath = (int)(texturePath - buffer);
				*offsetMaterialPath = (int)(materialPath - buffer);
				*amountOfTriangles = (int)(this->amountOfTriangles);
				*offsetTriangleData = (int) ( ((char*)triangleData) - buffer);

				strcpy(name, this->name);
				strcpy(texturePath, this->texturePath);
				strcpy(materialPath, this->materialPath);
				memcpy(triangleData, this->triangles, sizeof(TriangleIndexData) * this->amountOfTriangles);
			}

			void Load(char* buffer)
			{
				int* offsetName = (int*)buffer;
				int* offsetTexturePath = (int*)(buffer + 4);
				int* offsetMaterialPath = (int*)(buffer + 8);
				int* amountOfTriangles = (int*)(buffer + 12);
				int* offsetTriangleData = (int*)(buffer + 16);

				this->name = buffer + *offsetName;
				this->texturePath = buffer + *offsetTexturePath;
				this->materialPath = buffer + *offsetMaterialPath;
				this->amountOfTriangles = *amountOfTriangles;
				this->triangles = (TriangleIndexData*)(buffer + *offsetTriangleData);
			}
		};

		class SBE_EXPORT Model : public SBR::Model
		{
		public:
			MeshData* meshData;

			void Save(char* buffer)
			{
				int* magicNumber = (int*)buffer;
				int* offsetName = (int*)(buffer + 4);
				int* amountOfParts = (int*)(buffer + 8);
				int* partsOffsetsOffset = (int*)(buffer + 12);

				int* amountOfPositions = (int*)(buffer + 16);
				int* amountOfNormals = (int*)(buffer + 20);
				int* amountOfUVs = (int*)(buffer + 24);

				int* positionDataOffset = (int*)(buffer + 28);
				int* normalDataOffset = (int*)(buffer + 32);
				int* uvDataOffset = (int*)(buffer + 36);

				char* name = buffer + 40;
				int* partOffsets = (int*)(name + strlen(this->name) + 1);


				*magicNumber = 555;
				*offsetName = (int)(name - buffer);
				*amountOfParts = this->amountOfParts;
				*partsOffsetsOffset = (int)(((char*)partOffsets) - buffer);

				*amountOfPositions = this->meshData->amountOfPositions;
				*amountOfNormals = this->meshData->amountOfNormals;
				*amountOfUVs = this->meshData->amountOfUVs;


				strcpy(name, this->name);
				char* currentPointer = (char*)(partOffsets + this->amountOfParts);

				memcpy(currentPointer, this->meshData->positionData, sizeof(SBM::Vector3)*this->meshData->amountOfPositions);
				*positionDataOffset = (int)(currentPointer - buffer);
				currentPointer += sizeof(SBM::Vector3)*this->meshData->amountOfPositions;

				memcpy(currentPointer, this->meshData->normalData, sizeof(SBM::Vector3)*this->meshData->amountOfNormals);
				*normalDataOffset = (int)(currentPointer - buffer);
				currentPointer += sizeof(SBM::Vector3)*this->meshData->amountOfNormals;

				memcpy(currentPointer, this->meshData->uvData, sizeof(SBM::Vector3)*this->meshData->amountOfUVs);
				*uvDataOffset = (int)(currentPointer - buffer);
				currentPointer += sizeof(SBM::Vector2) * this->meshData->amountOfUVs;

				for (int i = 0; i < this->amountOfParts; i++)
				{
					partOffsets[i] = (int)(currentPointer - buffer);
					this->parts[i]->Save(currentPointer);
					currentPointer += this->parts[i]->GetSize();
				}
			}

			void Load(char* buffer)
			{
				int* magicNumber = (int*)buffer;
				int* offsetName = (int*)(buffer + 4);
				int* amountOfParts = (int*)(buffer + 8);
				int* partsOffsetsOffset = (int*)(buffer + 12);	
				int* amountOfPositions = (int*)(buffer + 16);
				int* amountOfNormals = (int*)(buffer + 20);
				int* amountOfUVs = (int*)(buffer + 24);

				int* positionDataOffset = (int*)(buffer + 28);
				int* normalDataOffset = (int*)(buffer + 32);
				int* uvDataOffset = (int*)(buffer + 36);

				char* name = buffer + 40;

				if (*magicNumber != 555)
					return;

				this->name = name;
				this->amountOfParts = *amountOfParts;
				this->parts = (SBR::ModelPart**) malloc(sizeof(ModelPart*) * this->amountOfParts);

				this->meshData = new SBR::i3fP3fN2fT::MeshData();
				this->meshData->amountOfPositions = *amountOfPositions;
				this->meshData->amountOfNormals = *amountOfNormals;
				this->meshData->amountOfUVs = *amountOfUVs;
				this->meshData->positionData = (SBM::Vector3*) (buffer + *positionDataOffset);
				this->meshData->normalData = (SBM::Vector3*) (buffer + *normalDataOffset);
				this->meshData->uvData = (SBM::Vector2*) (buffer + *uvDataOffset);

				int* partOffsets = (int*)(buffer + *partsOffsetsOffset);

				for (int i = 0; i < this->amountOfParts; i++)
				{
					char* partBuffer = buffer + partOffsets[i];
					this->parts[i] = new SBR::i3fP3fN2fT::ModelPart();
					this->parts[i]->Load(partBuffer);
				}
			}

			int GetSize()
			{
				int size = 0;

				size += 4; //magic identifier
				size += 4; //offset Name
				size += 4; //amount of parts
				size += 4; //parts offsets offset
				size += 4; //amountOfPositions
				size += 4; //amountOfNormals
				size += 4; //amountOfUVs
				size += 4; //positionDataOffset
				size += 4; //normalDataOffset
				size += 4; //uvDataOffset
				size += (int) strlen(this->name) + 1; //length of name
				size += 4 * this->amountOfParts; //parts offsets

				size += this->meshData->amountOfPositions * sizeof(SBM::Vector3); // space for position data
				size += this->meshData->amountOfNormals * sizeof(SBM::Vector3); // space for normal data
				size += this->meshData->amountOfUVs * sizeof(SBM::Vector2); // space for uv data

				// size of parts
				for (int i = 0; i < this->amountOfParts; i++)
				{
					size += this->parts[i]->GetSize();
				}

				return size;
			}
		};
	}
}