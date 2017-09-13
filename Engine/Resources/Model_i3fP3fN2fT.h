#pragma once
#include "ModelType.h"
#include "..\Math\Vector3.h"
#include "..\Math\Vector2.h"

namespace SBR
{
	namespace i3fP3fN2fT
	{
		class ModelPart;
	}

	namespace i3fP3fN2fT
	{
		class Model;

		class SBE_API ModelHeader
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

		class SBE_API ModelPartHeader
		{
		public:
			SBR::ModelType modelType;
			int offsetName;
			int offsetTexturePath;
			int offsetMaterialPath;
			int amountOfTriangles;
			int offsetTriangleData;
		};

		class SBE_API MeshData
		{
		public:
			MeshData();

			SBM::Vector3* positionData;
			SBM::Vector3* normalData;
			SBM::Vector2* uvData;

			int amountOfPositions;
			int amountOfNormals;
			int amountOfUVs;
		};

		class SBE_API TriangleIndexData
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

			TriangleIndexData(int position1, int normal1, int texture1, int position2, int normal2, int texture2, int position3, int normal3, int texture3);
			TriangleIndexData();
			TriangleIndexData(int defaultVal);
		};

		class SBE_API ModelPart
		{
		public:
			TriangleIndexData* triangles;
			int amountOfTriangles;
			char* name;
			bool dataIsContinous;
			SBR::i3fP3fN2fT::Model* model;

			ModelPart();
			int GetSize();
			void Save(char* buffer);
			int Load(char* buffer, bool copyDynamicData);
			~ModelPart();
		};

		class SBE_API Model
		{
		public:
			MeshData meshData;
			char* name;
			SBR::i3fP3fN2fT::ModelPart* parts;
			int amountOfParts;
			bool dataIsContinous;
			char* continousDynamicData;

			Model();
			void SaveToFile(char* path);
			void Save(char* buffer);
			static SBR::i3fP3fN2fT::Model* LoadFromPath(char* path, bool copyDynamicData);
			int Load(char* buffer, bool copyDynamicData);
			int GetSize();
			~Model();
		};
	}
}