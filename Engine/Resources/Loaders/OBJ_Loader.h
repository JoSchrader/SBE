#pragma once

#include "..\..\pch.h"
#include "FileOperations.h"

#include "..\OBJ.h"

namespace SBR
{
	enum SBE_EXPORT OBJ_FaceTypes
	{
		UNDEFINED = 0,

		TRI_FLAG = 1,
		QUAD_FLAG = 2,
		POS_FLAG = 4,
		TEXTURE_FLAG = 8,
		NORMAL_FLAG = 16,

		TRI_P = TRI_FLAG | POS_FLAG,									// f 1 2 3
		QUAD_P = QUAD_FLAG | POS_FLAG,									// f 1 2 3 4
		TRI_PT = TRI_FLAG | POS_FLAG | TEXTURE_FLAG,					// f 1/2 2/3 3/4					3
		QUAD_PT = QUAD_FLAG | POS_FLAG | TEXTURE_FLAG,					// f 1/2 2/3 3/4 4/5				4
		TRI_PN = TRI_FLAG | POS_FLAG | NORMAL_FLAG,						// f 1//2 2//3 3//4					6
		QUAD_PN = QUAD_FLAG | POS_FLAG | NORMAL_FLAG,					// f 1//2 2//3 3//4 4//5			8
		TRI_PTN = TRI_FLAG | POS_FLAG | TEXTURE_FLAG | NORMAL_FLAG,		// f 1/2/3 4/5/6 7/8/9				6
		QUAD_PTN = QUAD_FLAG | POS_FLAG | TEXTURE_FLAG | NORMAL_FLAG	// f 1/2/3 4/5/6 7/8/9 10/11/12		8
	};

	class SBE_EXPORT OBJ_Loader
	{
	private:
		static SBR::i3fP3fN2fT::ModelPart* ConstructModelPart(std::vector<SBR::i3fP3fN2fT::TriangleIndexData>* triangleData, char* name)
		{
			SBR::i3fP3fN2fT::ModelPart* part = new SBR::i3fP3fN2fT::ModelPart();
			part->amountOfTriangles = triangleData->size();
			part->dataIsContinous = false;

			if (strlen(name) > 0)
			{
				part->name = (char*)malloc(sizeof(char) * strlen(name) + 1);
				memcpy(part->name, name, strlen(name) + 1);
			}
			else
			{
				part->name = (char*)malloc(sizeof(char) * 7);
				part->name[0] = 'N'; part->name[1] = 'O'; part->name[2] = 'N'; part->name[3] = 'A'; part->name[4] = 'M'; part->name[5] = 'E'; part->name[6] = 0;
			}

			part->triangles = (SBR::i3fP3fN2fT::TriangleIndexData*) malloc(sizeof(SBR::i3fP3fN2fT::TriangleIndexData) *  triangleData->size());
			memcpy(part->triangles, &((*triangleData)[0]), sizeof(SBR::i3fP3fN2fT::TriangleIndexData) *  triangleData->size());

			return part;
		}

		static OBJ_FaceTypes GetFaceType(char* facestr)
		{
			int type = OBJ_FaceTypes::UNDEFINED;

			bool twoSlashes = false;
			int slashCount = 0, spacecount = 0;
			char* tmp = facestr;
			while (*tmp != '\r' && *tmp != '\n' && *tmp != 0)
			{
				if (*tmp == ' ' && *(tmp+1) != 0)  //hack to ignore a space if its at the end of line
					spacecount++;
				if (*tmp == '/')
					slashCount++;
				if (*tmp == '/' && *(tmp + 1) == '/')
					twoSlashes = true;
				tmp++;
			}

			type = OBJ_FaceTypes::POS_FLAG;

			if (spacecount == 2)
				type = type | OBJ_FaceTypes::TRI_FLAG;
			else if (spacecount == 3)
				type = type | OBJ_FaceTypes::QUAD_FLAG;
			else
				return OBJ_FaceTypes::UNDEFINED;

			if (slashCount == 0)
				;
			else if (slashCount == 3)
				type = type | OBJ_FaceTypes::TEXTURE_FLAG;
			else if (slashCount == 4)
				type = type | OBJ_FaceTypes::TEXTURE_FLAG;
			else if (slashCount == 6 && twoSlashes)
				type = type | OBJ_FaceTypes::NORMAL_FLAG;
			else if (slashCount == 6 && !twoSlashes)
				type = type | OBJ_FaceTypes::TEXTURE_FLAG | OBJ_FaceTypes::NORMAL_FLAG;
			else if (slashCount == 8 && twoSlashes)
				type = type | OBJ_FaceTypes::NORMAL_FLAG;
			else if (slashCount == 8 && !twoSlashes)
				type = type | OBJ_FaceTypes::TEXTURE_FLAG | OBJ_FaceTypes::NORMAL_FLAG;
			else
				return OBJ_FaceTypes::UNDEFINED;

			return (OBJ_FaceTypes)type;
		}

		static void ReadFace(std::vector<SBR::i3fP3fN2fT::TriangleIndexData>* triangleData, OBJ_FaceTypes faceType, char* text, int amountOfPositions, int amountOfNormals, int amountOfUVs)
		{
			SBR::i3fP3fN2fT::TriangleIndexData triData(0);

			if (faceType & OBJ_FaceTypes::TRI_FLAG)
			{
				if (faceType == OBJ_FaceTypes::TRI_P)
					sscanf(text, "%i %i %i", &triData.position1, &triData.position2, &triData.position3);
				else if (faceType == OBJ_FaceTypes::TRI_PT)
					sscanf(text, "%i/%i %i/%i %i/%i", &triData.position1, &triData.texture1, &triData.position2, &triData.texture2, &triData.position3, &triData.texture3);
				else if (faceType == OBJ_FaceTypes::TRI_PN)
					sscanf(text, "%i//%i %i//%i %i//%i", &triData.position1, &triData.normal1, &triData.position2, &triData.normal2, &triData.position3, &triData.normal3);
				else if (faceType == OBJ_FaceTypes::TRI_PTN)
					sscanf(text, "%i/%i/%i %i/%i/%i %i/%i/%i", &triData.position1, &triData.texture1, &triData.normal1, &triData.position2, &triData.texture2, &triData.normal2, &triData.position3, &triData.texture3, &triData.normal3);

				if (triData.position1 < 0) triData.position1 = amountOfPositions + triData.position1;
				if (triData.position2 < 0) triData.position2 = amountOfPositions + triData.position2;
				if (triData.position3 < 0) triData.position3 = amountOfPositions + triData.position3;
				if (triData.normal1 < 0) triData.normal1 = amountOfNormals + triData.normal1;
				if (triData.normal2 < 0) triData.normal2 = amountOfNormals + triData.normal2;
				if (triData.normal3 < 0) triData.normal3 = amountOfNormals + triData.normal3;
				if (triData.texture1 < 0) triData.texture1 = amountOfUVs + triData.texture1;
				if (triData.texture2 < 0) triData.texture2 = amountOfUVs + triData.texture2;
				if (triData.texture3 < 0) triData.texture3 = amountOfUVs + triData.texture3;

				if (triData.texture3 == 292850)
				{
					int i = 12;
				}

				triangleData->push_back(triData);
			}

			else if (faceType & OBJ_FaceTypes::QUAD_FLAG)
			{
				int pos4=0, texture4=0, normal4=0;
				if (faceType == OBJ_FaceTypes::QUAD_P)
					sscanf(text, "%i %i %i %i", &triData.position1, &triData.position2, &triData.position3, &pos4);
				else if (faceType == OBJ_FaceTypes::QUAD_PT)
					sscanf(text, "%i/%i %i/%i %i/%i %i/%i", &triData.position1, &triData.texture1, &triData.position2, &triData.texture2, &triData.position3, &triData.texture3, &pos4, &texture4);
				else if (faceType == OBJ_FaceTypes::QUAD_PN)
					sscanf(text, "%i//%i %i//%i %i//%i %i//%i", &triData.position1, &triData.normal1, &triData.position2, &triData.normal2, &triData.position3, &triData.normal3, &pos4, &normal4);
				else if (faceType == OBJ_FaceTypes::QUAD_PTN)
					sscanf(text, "%i/%i/%i %i/%i/%i %i/%i/%i %i/%i/%i", &triData.position1, &triData.texture1, &triData.normal1, &triData.position2, &triData.texture2, &triData.normal2, &triData.position3, &triData.texture3, &triData.normal3, &pos4, &texture4, &normal4);

				if (triData.position1 < 0) triData.position1 = amountOfPositions + triData.position1;
				if (triData.position2 < 0) triData.position2 = amountOfPositions + triData.position2;
				if (triData.position3 < 0) triData.position3 = amountOfPositions + triData.position3;
				if (triData.normal1 < 0) triData.normal1 = amountOfNormals + triData.normal1;
				if (triData.normal2 < 0) triData.normal2 = amountOfNormals + triData.normal2;
				if (triData.normal3 < 0) triData.normal3 = amountOfNormals + triData.normal3;
				if (triData.texture1 < 0) triData.texture1 = amountOfUVs + triData.texture1;
				if (triData.texture2 < 0) triData.texture2 = amountOfUVs + triData.texture2;
				if (triData.texture3 < 0) triData.texture3 = amountOfUVs + triData.texture3;
				if (pos4 < 0) pos4 = amountOfPositions + pos4;
				if (normal4 < 0) normal4 = amountOfNormals + normal4;
				if (texture4 < 0) texture4 = amountOfUVs + texture4;

				if (texture4 == 292850)
				{
					int i = 12;
				}

				triangleData->push_back(triData);
				SBR::i3fP3fN2fT::TriangleIndexData triData2(triData.position3, triData.normal3, triData.texture3,  pos4, normal4, texture4,  triData.position1, triData.normal1, triData.texture1);
				triangleData->push_back(triData2);
			}
			else
			{
				//WTF - how did we get here?
			}
		}

	public:
		static SBR::i3fP3fN2fT::Model *Load(char* path)
		{
			if (!SBR::File::Exist(path))
				return nullptr;

			SBR::i3fP3fN2fT::Model* model = new SBR::i3fP3fN2fT::Model();

			OBJ_FaceTypes vertexIndexType = OBJ_FaceTypes::UNDEFINED;

			std::vector<SBM::Vector3> positions;
			std::vector<SBM::Vector3> normals;
			std::vector<SBM::Vector2> uvs;

			positions.push_back(SBM::Vector3(0, 0, 0));
			normals.push_back(SBM::Vector3(0, 0, 0));
			uvs.push_back(SBM::Vector2(0, 0));

			std::vector<SBR::i3fP3fN2fT::ModelPart*> parts;
			std::vector<SBR::i3fP3fN2fT::TriangleIndexData> curTriangleData;
			char curName[256];

			int size;
			char* file = SBR::File::Read(path, &size);
			char* eof = file + size;

			char* cur = file;

			int line = 1;
			float x, y, z;

			cur = strtok(cur, "\r\n");

			while (cur < eof && cur != nullptr)
			{
				if (cur[0] == 'v' && cur[1] == ' ')
				{
					cur += 2;
					sscanf(cur, "%f %f %f", &x, &y, &z);
					positions.push_back(SBM::Vector3(x, y, z));
				}
				else if (cur[0] == 'v' && cur[1] == 't')
				{
					cur += 3;
					sscanf(cur, "%f %f", &x, &y);
					uvs.push_back(SBM::Vector2(x, y));
				}
				else if (cur[0] == 'v' && cur[1] == 'n')
				{
					cur += 3;
					sscanf(cur, "%f %f %f", &x, &y, &z);
					normals.push_back(SBM::Vector3(x, y, z));
				}
				else if (cur[0] == 'f' && cur[1] == ' ')
				{
					cur += 2;

					//only scan first face
					//if (vertexIndexType == OBJ_FaceTypes::UNDEFINED)
					vertexIndexType = GetFaceType(cur);

					if(vertexIndexType != OBJ_FaceTypes::UNDEFINED)
						ReadFace(&curTriangleData, vertexIndexType, cur, positions.size(), normals.size(), uvs.size());
				}
				else if (cur[0] == 'o' && cur[1] == ' ' || cur[0] == 'g' && cur[1] == ' ')
				{
					cur += 2;

					if (curTriangleData.size() > 0)
					{
						SBR::i3fP3fN2fT::ModelPart* part = ConstructModelPart(&curTriangleData, curName);
						part->model = model;
						parts.push_back(part);
						curTriangleData.clear();
					}

					char* nextCRLF = cur;
					while (*nextCRLF != '\n' && *nextCRLF != '\r')
						nextCRLF++;

					int nameLength = nextCRLF - cur;
					memcpy(curName, cur, nameLength * sizeof(char));
					curName[nameLength] = 0;
				}
				else if (cur[0] == 'm' && cur[1] == 't' && cur[2] == 'l' && cur[3] == 'l' && cur[4] == 'i' && cur[5] == 'b')
				{
					cur += 7;
				}
				else if (cur[0] == 'u' && cur[1] == 's' && cur[2] == 'e' && cur[3] == 'm' && cur[4] == 't' && cur[5] == 'l')
				{
					cur += 7;
				}

				cur = strtok(nullptr, "\r\n");
				line++;
			}

			if (curTriangleData.size() > 0)
			{
				SBR::i3fP3fN2fT::ModelPart* part = ConstructModelPart(&curTriangleData, curName);
				part->model = model;
				parts.push_back(part);
				curTriangleData.clear();
			}

			model->amountOfParts = parts.size();
			model->continousDynamicData = nullptr;
			model->dataIsContinous = false;

			model->meshData.amountOfPositions = positions.size();
			model->meshData.positionData = (SBM::Vector3*) malloc(sizeof(SBM::Vector3)* positions.size());
			memcpy(model->meshData.positionData, &positions[0], sizeof(SBM::Vector3)* positions.size());

			model->meshData.amountOfNormals = normals.size();
			model->meshData.normalData = (SBM::Vector3*) malloc(sizeof(SBM::Vector3)* normals.size());
			memcpy(model->meshData.normalData, &normals[0], sizeof(SBM::Vector3)* normals.size());

			model->meshData.amountOfUVs = uvs.size();
			model->meshData.uvData = (SBM::Vector2*) malloc(sizeof(SBM::Vector2)* uvs.size());
			memcpy(model->meshData.uvData, &uvs[0], sizeof(SBM::Vector2)* uvs.size());

			model->name = (char*)malloc(sizeof(char) * strlen(path) + 1);
			strcpy(model->name, path);

			model->parts = (SBR::i3fP3fN2fT::ModelPart*) malloc(sizeof(SBR::i3fP3fN2fT::ModelPart) * parts.size());
			for (int i = 0; i < parts.size(); i++)
				model->parts[i] = *parts[i];

			free(file);

			return model;
		}
	};
}

