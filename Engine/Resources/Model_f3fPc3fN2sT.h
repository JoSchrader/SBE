#pragma once
#include "..\Math\Vector3.h"
#include "..\Math\Vector2.h"
#include "ModelType.h"

namespace SBR
{
	namespace i3fP3fN2fT
	{
		class Model;
	}

	namespace f3fPc3fN2sT
	{
		class SBE_API ModelHeader
		{
		public:
			int magicNumber;
			SBR::ModelType modelType;
			int amountOfParts;
			int nameOffset;
			int partOffsetsOffset;
		};

		class SBE_API ModelPartHeader
		{
		public:
			SBR::ModelType modelType;
			int nameOffset;
			int amountOfVertexes;
			int vertexDataOffset;
		};

		class SBE_API CompressedVertex
		{
		public:
			float posX; // 4byte
			float posY; // 4byte
			float posZ; // 4byte
			unsigned int packedNormals; //4 byte
			short uvX; // 2byte
			short uvY; // 2byte

			CompressedVertex(SBM::Vector3 pos, SBM::Vector3 normal, SBM::Vector2 uv)
			{
				this->posX = pos.x;
				this->posY = pos.y;
				this->posZ = pos.z;

				this->packedNormals = 0;
				this->packedNormals = this->packedNormals | (0 << 30); // upper 2 bit not used
				this->packedNormals = this->packedNormals | ((int)(normal.x * 1023) << 20); // map normalised normal to [0,1023] integer
				this->packedNormals = this->packedNormals | ((int)(normal.y * 1023) << 10); // map normalised normal to [0,1023] integer
				this->packedNormals = this->packedNormals | ((int)(normal.z * 1023) << 0); // map normalised normal to [0,1023] integer

				this->uvX = (short)(uv.x * 65535); // map normalised uv to [0,65535]
				this->uvY = (short)(uv.y * 65535); // map normalised uv to [0,65535]
			}
		};

		class SBE_API ModelPart
		{
		public:
			CompressedVertex* vertexes;
			int amountOfVertexes;
			char* name;
			bool dataIsContinous;

			ModelPart();
			~ModelPart();

			void Load(char* buffer, bool copyDynamicData);

			int GetSize();
			void Save(char* buffer);
		};

		class SBE_API Model
		{
		public:
			char* name;
			int amountOfParts;
			SBR::f3fPc3fN2sT::ModelPart* parts;

			bool dataIsContinous;
			char* continousDynamicData;

			Model();
			Model(SBR::i3fP3fN2fT::Model* model);
			SBR::f3fPc3fN2sT::ModelPart* MergeParts();
			~Model();
			int GetSize();

			static SBR::f3fPc3fN2sT::Model* LoadFromFile(char* path, bool copyDynamicData);
			void LoadFromBuffer(char* buffer, bool copyDynamicData);
			void SaveToFile(char* path);
			void SaveToBuffer(char* buffer);
		};
	}
}