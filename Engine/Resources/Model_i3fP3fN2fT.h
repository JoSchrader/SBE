#pragma once
#include "Model.h"

namespace SBR
{
	namespace i3fP3fN2fT
	{
		class SBE_EXPORT ModelHeader
		{
		public:
			int magicNumber;
			SBR::ModelType modelType;

			int offsetName;
			int amountOfParts;
			int partsOffsetsOffset;

			int amountOfPositions;
			int positionDataOffset;

			int amountOfNormals;
			int normalDataOffset;

			int amountOfUVs;
			int uvDataOffset;
		};

		class SBE_EXPORT ModelPartHeader
		{
		public:
			SBR::ModelType modelType;
			int offsetName;
			int offsetTexturePath;
			int offsetMaterialPath;
			int amountOfTriangles;
			int offsetTriangleData;
		};

		class SBE_EXPORT MeshData
		{
		public:
			MeshData()
			{
				this->positionData = nullptr;
				this->normalData = nullptr;
				this->uvData = nullptr;
				this->amountOfPositions = -1;
				this->amountOfNormals = -1;
				this->amountOfUVs = -1;
			}

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

		class SBE_EXPORT ModelPart
		{
		public:
			TriangleIndexData* triangles;
			int amountOfTriangles;
			char* name;

			ModelPart()
			{
				this->triangles = nullptr;
				this->amountOfTriangles = -1;
			}

			// Returns needed Filesize in bytes
			int GetSize()
			{
				int size = 0;
				size += sizeof(ModelPartHeader);
				size += (int)strlen(name) + 1;
				size += sizeof(TriangleIndexData) * amountOfTriangles;
				return size;
			}

			void Save(char* buffer)
			{
				ModelPartHeader* modelPartHeader = (ModelPartHeader*)buffer;
				char* curBufferPosition = buffer + sizeof(ModelPartHeader);

				modelPartHeader->modelType = SBR::ModelType::i3fP3fN2fT_ID;

				//push name to buffer
				strcpy(curBufferPosition, this->name);
				modelPartHeader->offsetName = curBufferPosition - buffer;
				curBufferPosition += strlen(this->name) + 1;

				//push TriangleData
				memcpy(curBufferPosition, this->triangles, sizeof(TriangleIndexData) * this->amountOfTriangles);
				modelPartHeader->offsetTriangleData = curBufferPosition - buffer;
				modelPartHeader->amountOfTriangles = this->amountOfTriangles;
			}

			//Returns
			void Load(char* buffer)
			{
				ModelPartHeader* modelPartHeader = (ModelPartHeader*)buffer;

				if (modelPartHeader->modelType != SBR::ModelType::i3fP3fN2fT_ID)
				{
					int k = 2;
				}

				this->name = buffer + modelPartHeader->offsetName;
				this->amountOfTriangles = modelPartHeader->amountOfTriangles;
				this->triangles = (TriangleIndexData*)(buffer + modelPartHeader->offsetTriangleData);
			}
		};

		class SBE_EXPORT Model
		{
		public:
			MeshData meshData;
			char* name;
			SBR::i3fP3fN2fT::ModelPart* parts;
			int amountOfParts;

			Model()
			{
				this->amountOfParts = 0;
				this->name = nullptr;
				this->parts = nullptr;
			}

			void Save(char* buffer)
			{
				ModelHeader* modelHeader = (ModelHeader*)buffer;
				char* curBufferPointer = buffer + sizeof(ModelHeader);

				modelHeader->magicNumber = SBE_MODEL_MAGIC_BYTES;
				modelHeader->modelType = SBR::ModelType::i3fP3fN2fT_ID;

				//Push Name
				strcpy(curBufferPointer, this->name);
				modelHeader->offsetName = curBufferPointer - buffer;
				curBufferPointer += strlen(this->name) + 1;

				//Push PartOffsets
				modelHeader->amountOfParts = this->amountOfParts;
				modelHeader->partsOffsetsOffset = curBufferPointer - buffer;
				curBufferPointer += sizeof(int) * this->amountOfParts;

				//Push Positions
				modelHeader->amountOfPositions = this->meshData.amountOfPositions;
				modelHeader->positionDataOffset = curBufferPointer - buffer;
				memcpy(curBufferPointer, this->meshData.positionData, sizeof(SBM::Vector3)* this->meshData.amountOfPositions);
				curBufferPointer += sizeof(SBM::Vector3)* this->meshData.amountOfPositions;

				//Push Normals
				modelHeader->amountOfNormals = this->meshData.amountOfNormals;
				modelHeader->normalDataOffset = curBufferPointer - buffer;
				memcpy(curBufferPointer, this->meshData.normalData, sizeof(SBM::Vector3) * this->meshData.amountOfNormals);
				curBufferPointer += sizeof(SBM::Vector3)* this->meshData.amountOfNormals;

				//Push UVs
				modelHeader->amountOfUVs = this->meshData.amountOfUVs;
				modelHeader->uvDataOffset = curBufferPointer - buffer; 
				memcpy(curBufferPointer, this->meshData.uvData, sizeof(SBM::Vector2) * this->meshData.amountOfUVs);
				curBufferPointer += sizeof(SBM::Vector2)* this->meshData.amountOfUVs;

				int* partOffsets = (int*)(buffer + modelHeader->partsOffsetsOffset);
				for (int i = 0; i < this->amountOfParts; i++)
				{
					partOffsets[i] = curBufferPointer - buffer;
					this->parts[i].Save(curBufferPointer);
					curBufferPointer += this->parts[i].GetSize();
				}
			}

			int Load(char* buffer)
			{				
				ModelHeader* modelHeader = (ModelHeader*)buffer;

				if (modelHeader->magicNumber != SBE_MODEL_MAGIC_BYTES)
					return -1;

				if (modelHeader->modelType != SBR::ModelType::i3fP3fN2fT_ID)
					return -1;

				this->name = buffer + modelHeader->offsetName;
				this->amountOfParts = modelHeader->amountOfParts;

				//this->parts = (SBR::ModelPart**) malloc(sizeof(ModelPart*) * this->amountOfParts);

				this->meshData.amountOfPositions = modelHeader->amountOfPositions;
				this->meshData.amountOfNormals = modelHeader->amountOfNormals;
				this->meshData.amountOfUVs = modelHeader->amountOfUVs;
				this->meshData.positionData = (SBM::Vector3*) (buffer + modelHeader->positionDataOffset);
				this->meshData.normalData = (SBM::Vector3*) (buffer + modelHeader->normalDataOffset);
				this->meshData.uvData = (SBM::Vector2*) (buffer + modelHeader->uvDataOffset);

				int* partOffsets = (int*)(buffer + modelHeader->partsOffsetsOffset);

				for (int i = 0; i < this->amountOfParts; i++)
				{
					char* partBuffer = buffer + partOffsets[i];
					//this->parts[i] = new SBR::i3fP3fN2fT::ModelPart();
					//this->parts[i]->Load(partBuffer);
				}
			}

			int GetSize()
			{
				int size = 0;
				size += sizeof(ModelHeader);
				size += (int)strlen(this->name) + 1; //length of name
				size += 4 * this->amountOfParts;	 //parts offsets

				size += this->meshData.amountOfPositions * sizeof(SBM::Vector3); // space for position data
				size += this->meshData.amountOfNormals * sizeof(SBM::Vector3); // space for normal data
				size += this->meshData.amountOfUVs * sizeof(SBM::Vector2); // space for uv data

				// size of parts
		//		for (int i = 0; i < this->amountOfParts; i++)
//					size += this->parts[i]->GetSize();

				return size;
			}
		};
	}
}