#pragma once
#include "Model.h"
#include "Loaders\FileOperations.h"
#include "Model_f3fPc3fN2sT.h"

namespace SBR
{
	namespace i3fP3fN2fT
	{
		class Model;

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

			TriangleIndexData(int position1, int normal1, int texture1, int position2, int normal2, int texture2, int position3, int normal3, int texture3)
			{
				this->position1 = position1;
				this->normal1 = normal1;
				this->texture1 = texture1;
				this->position2 = position2;
				this->normal2 = normal2;
				this->texture2 = texture2;
				this->position3 = position3;
				this->normal3 = normal3;
				this->texture3 = texture3;
			}

			TriangleIndexData()
			{
				this->position1 = -1;
				this->normal1 = -1;
				this->texture1 = -1;
				this->position2 = -1;
				this->normal2 = -1;
				this->texture2 = -1;
				this->position3 = -1;
				this->normal3 = -1;
				this->texture3 = -1;
			}

			TriangleIndexData(int defaultVal)
			{
				this->position1 = defaultVal;
				this->normal1 = defaultVal;
				this->texture1 = defaultVal;
				this->position2 = defaultVal;
				this->normal2 = defaultVal;
				this->texture2 = defaultVal;
				this->position3 = defaultVal;
				this->normal3 = defaultVal;
				this->texture3 = defaultVal;
			}
		};

		class SBE_EXPORT ModelPart
		{
		public:
			TriangleIndexData* triangles;
			int amountOfTriangles;
			char* name;
			bool dataIsContinous;
			SBR::i3fP3fN2fT::Model* model;

			ModelPart()
			{
				this->triangles = nullptr;
				this->amountOfTriangles = -1;
				this->dataIsContinous = false;
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
			int Load(char* buffer, bool copyDynamicData)
			{
				ModelPartHeader* modelPartHeader = (ModelPartHeader*)buffer;

				if (modelPartHeader->modelType != SBR::ModelType::i3fP3fN2fT_ID)
					return -1;

				this->name = buffer + modelPartHeader->offsetName;
				this->amountOfTriangles = modelPartHeader->amountOfTriangles;
				this->triangles = (TriangleIndexData*)(buffer + modelPartHeader->offsetTriangleData);

				if (copyDynamicData)
				{
					this->dataIsContinous = false;

					SBR::i3fP3fN2fT::TriangleIndexData* _triangles = (SBR::i3fP3fN2fT::TriangleIndexData*) malloc(sizeof(SBR::i3fP3fN2fT::TriangleIndexData) * this->amountOfTriangles);
					memcpy(_triangles, this->triangles, sizeof(SBR::i3fP3fN2fT::TriangleIndexData) * this->amountOfTriangles);
					this->triangles = _triangles;


					char* _name = (char*)malloc(sizeof(char) * strlen(this->name) + 1);
					strcpy(_name, this->name);
					this->name = _name;
				}
				else
				{
					this->dataIsContinous = true;
				}
			}

			~ModelPart()
			{
				if (!this->dataIsContinous)
				{
					if (triangles != nullptr)
						free(this->triangles);
					if (this->name != nullptr)
						free(this->name);
				}
			}
		};

		class SBE_EXPORT Model
		{
		public:
			MeshData meshData;
			char* name;
			SBR::i3fP3fN2fT::ModelPart* parts;
			int amountOfParts;
			bool dataIsContinous;
			char* continousDynamicData;

			Model()
			{
				this->amountOfParts = 0;
				this->name = nullptr;
				this->parts = nullptr;
				this->continousDynamicData = nullptr;
				this->dataIsContinous = false;
			}

			void SaveToFile(char* path)
			{
				int size = this->GetSize();
				char* buffer = (char*)malloc(sizeof(char)* size);
				this->Save(buffer);
				SBR::File::Write(path, buffer, size);
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

			static SBR::i3fP3fN2fT::Model* LoadFromPath(char* path, bool copyDynamicData)
			{
				if (!SBR::File::Exist(path))
					return nullptr;

				SBR::i3fP3fN2fT::Model* model = new SBR::i3fP3fN2fT::Model();

				int size = 0;
				char* buffer = SBR::File::Read(path, &size);

				int result = model->Load(buffer, copyDynamicData);

				if (copyDynamicData)
					free(buffer);
				else
					model->continousDynamicData = buffer;

				if (strlen(model->name) == 0)
				{
					model->name = (char*)malloc(sizeof(char) * strlen(path) + 1);
					strcpy(model->name, path);
				}

				return model;
			}

			int Load(char* buffer, bool copyDynamicData)
			{
				ModelHeader* modelHeader = (ModelHeader*)buffer;

				if (modelHeader->magicNumber != SBE_MODEL_MAGIC_BYTES)
					return -1;

				if (modelHeader->modelType != SBR::ModelType::i3fP3fN2fT_ID)
					return -1;

				this->name = buffer + modelHeader->offsetName;
				this->amountOfParts = modelHeader->amountOfParts;
				this->meshData.amountOfPositions = modelHeader->amountOfPositions;
				this->meshData.amountOfNormals = modelHeader->amountOfNormals;
				this->meshData.amountOfUVs = modelHeader->amountOfUVs;
				this->meshData.positionData = (SBM::Vector3*) (buffer + modelHeader->positionDataOffset);
				this->meshData.normalData = (SBM::Vector3*) (buffer + modelHeader->normalDataOffset);
				this->meshData.uvData = (SBM::Vector2*) (buffer + modelHeader->uvDataOffset);

				if (copyDynamicData)
				{
					this->dataIsContinous = false;

					char* _name = (char*)malloc(sizeof(char) * strlen(this->name) + 1);
					strcpy(_name, this->name);
					this->name = _name;

					SBM::Vector3* _positionData = (SBM::Vector3*) malloc(sizeof(SBM::Vector3)*this->meshData.amountOfPositions);
					memcpy(_positionData, this->meshData.positionData, sizeof(SBM::Vector3)*this->meshData.amountOfPositions);
					this->meshData.positionData = _positionData;

					SBM::Vector3* _normalData = (SBM::Vector3*) malloc(sizeof(SBM::Vector3)*this->meshData.amountOfNormals);
					memcpy(_normalData, this->meshData.normalData, sizeof(SBM::Vector3)*this->meshData.amountOfNormals);
					this->meshData.normalData = _normalData;

					SBM::Vector2* _uvData = (SBM::Vector2*) malloc(sizeof(SBM::Vector2)*this->meshData.amountOfUVs);
					memcpy(_uvData, this->meshData.uvData, sizeof(SBM::Vector2)*this->meshData.amountOfUVs);
					this->meshData.uvData = _uvData;
				}
				else
				{
					this->dataIsContinous = true;
					this->continousDynamicData = buffer;
				}

				int* partOffsets = (int*)(buffer + modelHeader->partsOffsetsOffset);
				this->parts = (SBR::i3fP3fN2fT::ModelPart*) malloc(sizeof(SBR::i3fP3fN2fT::ModelPart) * this->amountOfParts);

				for (int i = 0; i < this->amountOfParts; i++)
				{
					char* partBuffer = buffer + partOffsets[i];
					new (this->parts + i) SBR::i3fP3fN2fT::ModelPart();
					this->parts[i].Load(partBuffer, copyDynamicData);
					this->parts[i].model = this;
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

				//size of parts
				for (int i = 0; i < this->amountOfParts; i++)
					size += this->parts[i].GetSize();

				return size;
			}

			~Model()
			{
				for (int i = 0; i < this->amountOfParts; i++)
				{
					delete (this->parts + i);
				}

				if (this->dataIsContinous)
				{
					free(this->continousDynamicData);
				}
				else
				{
					free(this->meshData.normalData);
					free(this->meshData.positionData);
					free(this->meshData.uvData);
				}
			}
		};
	}
}