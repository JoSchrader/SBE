#pragma once

#include "..\..\pch.h"
#include "FileOperations.h"

#include "..\OBJ.h"
#include "..\Mesh.h"

namespace SBR
{
	class SBE_EXPORT OBJ_Loader
	{
	public:
		static SBR::OBJ* Load(char* path)
		{
			SBR::i3fP3fN2fT::Model* model = new SBR::i3fP3fN2fT::Model();

			std::vector<SBR::i3fP3fN2fT::ModelPart*> parts;
			parts.push_back(new SBR::i3fP3fN2fT::ModelPart());

			std::vector<SBM::Vector3> positions;
			std::vector<SBM::Vector3> normals;
			std::vector<SBM::Vector2> uvs;

			SBR::OBJ* ret = new SBR::OBJ();


			if (!SBR::File::Exist(path))
				return ret;

			int size;
			char* file = SBR::File::Read(path, &size);
			char* eof = file + size;

			char* cur = file;

			float x, y, z;
			int v1Pos, v1UV, v1Normal;
			int v2Pos, v2UV, v2Normal;
			int v3Pos, v3UV, v3Normal;

			while (cur < eof)
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
					sscanf(cur, "%i/%i/%i %i/%i/%i %i/%i/%i", &v1Pos, &v1UV, &v1Normal, &v2Pos, &v2UV, &v2Normal, &v3Pos, &v3UV, &v3Normal);

					v1Pos--; v1UV--; v1Normal--;
					v2Pos--; v2UV--; v2Normal--;
					v3Pos--; v3UV--; v3Normal--;

//					curMesh->triangleIndexes.push_back(SBR::TriangleIndex(SBR::VertexIndex(v1Pos, v1UV, v1Normal), SBR::VertexIndex(v2Pos, v2UV, v2Normal), SBR::VertexIndex(v3Pos, v3UV, v3Normal)));
				}
				else if (cur[0] == 'o' && cur[1] == ' ' || cur[0] == 'g' && cur[1] == ' ')
				{
					cur += 2;
				}
				else if (cur[0] == 'm' && cur[1] == 't' && cur[2] == 'l' && cur[3] == 'l' && cur[4] == 'i' && cur[5] == 'b')
				{
					cur += 7;
				}
				else if (cur[0] == 'u' && cur[1] == 's' && cur[2] == 'e' && cur[3] == 'm' && cur[4] == 't' && cur[5] == 'l')
				{
					cur += 7;
				}

				cur = strchr(cur, '\n') + 1;
			}

			SBR::OBJ_Object* objObject = new SBR::OBJ_Object();
//			objObject->mesh = curMesh;

			ret->objObjects.push_back(objObject);

			free(file);

			return ret;
		}
	};

}

