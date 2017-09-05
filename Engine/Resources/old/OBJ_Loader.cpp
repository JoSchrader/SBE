#include "..\pch.h"
#include "ResourceLoader.h"
#include "..\Math\Vector3.h"
#include "..\Math\Vector2.h"
#include "OBJ_mtl.h"
#include "Mesh.h"

BOOST_FUSION_ADAPT_STRUCT(vec3, (float, x)(float, y)(float, z))
BOOST_FUSION_ADAPT_STRUCT(vec2, (float, x)(float, y))
BOOST_FUSION_ADAPT_STRUCT(TriangleIndex, (int, verticesIndexes[0].posIndex)(int, verticesIndexes[0].uvIndex)(int, verticesIndexes[0].normalIndex)
	(int, verticesIndexes[1].posIndex)(int, verticesIndexes[1].uvIndex)(int, verticesIndexes[1].normalIndex)
	(int, verticesIndexes[2].posIndex)(int, verticesIndexes[2].uvIndex)(int, verticesIndexes[2].normalIndex))

enum VBO_Type
{
	VBO_V3_T2_N3,
	VBO_V3_T2,
	VBO_V3_N3
};


inline SBR::OBJ_Object* CreateObjObject(std::string name, SBR::OBJ_mtl* material, MeshData* meshData, Mesh* mesh)
{
	SBR::OBJ_Object* createdObjObject = new SBR::OBJ_Object(name);
	createdObjObject->material = material;
	createdObjObject->mesh = mesh;
	createdObjObject->mesh->meshData = meshData;



	return createdObjObject;
}

SBR::OBJ* SBR::ResourceLoader::LoadObj(std::string path)
{
	using namespace boost::spirit::qi;
	OBJ* createdObj = new OBJ();

	boost::iostreams::mapped_file mmap(path, boost::iostreams::mapped_file::readonly);
	auto f = mmap.const_data();
	auto l = f + mmap.size();
	uintmax_t m_numLines = 0;

	MeshData* meshData = new MeshData();
	Mesh* curMesh = new Mesh();

	std::string name;
	VBO_Type vboType;
	OBJ_mtl* currentMtl = nullptr;

	while (f && f != l)
	{
		if (f[0] == 'v' && f[1] == ' ')
		{
			f += 2;
			bool ok = phrase_parse(f, l, (float_ > float_ > float_) % eol, blank, meshData->positions);
			int a = 12;
		}

		else if (f[0] == 'v' && f[1] == 't')
		{
			f += 3;
			bool ok = phrase_parse(f, l, (float_ > float_) % eol, blank, meshData->uvs);
			int a = 12;
		}

		else if (f[0] == 'v' && f[1] == 'n')
		{
			f += 3;
			bool ok = phrase_parse(f, l, (float_ > float_ > float_) % eol, blank | '/', meshData->normals);
			int a = 12;
		}

		else if (f[0] == 'f' && f[1] == ' ')
		{
			f += 2;
			if (curMesh->triangleIndexes.size() == 0)
			{
				const char* lineEnd = static_cast<const char*>(memchr(f, '\n', l - f));
				int size = (int)(lineEnd - f) - 1;
				char* line = (char*)malloc((size + 1)*sizeof(char));
				memcpy(line, f, size);
				line[size] = '\0';
				std::string lineStr = std::string(line);

				boost::regex V3_T2_N3_Regex("[0-9]+/[0-9]+/[0-9]+ [0-9]+/[0-9]+/[0-9]+ [0-9]+/[0-9]+/[0-9]+");
				boost::regex V3_T2_Regex("[0-9]+/[0-9]+ [0-9]+/[0-9]+ [0-9]+/[0-9]+");
				boost::regex V3_N3_Regex("[0-9]+//[0-9]+ [0-9]+//[0-9]+ [0-9]+//[0-9]+");

				if (boost::regex_match(lineStr, V3_T2_N3_Regex))
					vboType = VBO_V3_T2_N3;
				else if (boost::regex_match(lineStr, V3_T2_Regex))
					vboType = VBO_V3_T2;
				else if (boost::regex_match(lineStr, V3_N3_Regex))
					vboType = VBO_V3_N3;
			}
			if (vboType == VBO_V3_T2_N3)
			{
				bool ok = phrase_parse(f, l, (int_ > int_ > int_ > int_ > int_ > int_ > int_ > int_ > int_) % eol, blank | '/', curMesh->triangleIndexes);
			}
			else if (vboType == VBO_V3_T2)
			{
				/*bool ok = phrase_parse(f, l, (int_ > int_ > int_ > int_ > int_ > int_) % eol, blank | '/', i6TmpFaces);
				Face_i6 f2 = i6TmpFaces[0];
				Face_i9 f;
				f.v1 = f2.i1;
				f.t1 = f2.i2;
				f.n1 = 0;
				f.v2 = f2.i3;
				f.t2 = f2.i4;
				f.n2 = 0;
				f.v3 = f2.i5;
				f.t3 = f2.i6;
				f.n3 = 0;
				faces.push_back(f);
				i6TmpFaces.pop_back();*/
			}
			else if (vboType == VBO_V3_N3)
			{
				/*bool ok = phrase_parse(f, l, (int_ > int_ > int_ > int_ > int_ > int_) % eol, blank | '/', i6TmpFaces);
				Face_i6 f2 = i6TmpFaces[0];
				Face_i9 f;
				f.v1 = f2.i1;
				f.t1 = 0;
				f.n1 = f2.i2;
				f.v2 = f2.i3;
				f.t2 = 0;
				f.n2 = f2.i4;
				f.v3 = f2.i5;
				f.t3 = 0;
				f.n3 = f2.i6;
				faces.push_back(f);
				i6TmpFaces.pop_back();*/
			}
		}

		else if (f[0] == 'o' && f[1] == ' ' || f[0] == 'g' && f[1] == ' ')
		{
			if (curMesh->triangleIndexes.size() != 0)
			{
				createdObj->objObjects.push_back(CreateObjObject(name, currentMtl, meshData, curMesh));
			}
			name = std::string();
			bool ok = parse(f, l, "o " >> +(char_ - eol) | "g " >> +(char_ - eol), name);
		}

		else if (f[0] == 'm' && f[1] == 't' && f[2] == 'l' && f[3] == 'l' && f[4] == 'i' && f[5] == 'b')
		{
			std::string mtllibName;
			std::string mtllibPath;

			boost::filesystem::path objPath(path);

			bool ok = parse(f, l, "mtllib " >> +(char_ - eol), mtllibName);
			if (ok)
			{
				mtllibPath = objPath.parent_path().string() + "\\" + mtllibName;
				createdObj->mtllib = SBR::ResourceLoader::LoadObjMtlLib(mtllibPath);
			}
		}
		else if (f[0] == 'u' && f[1] == 's' && f[2] == 'e' && f[3] == 'm' && f[4] == 't' && f[5] == 'l')
		{
			f += 7;
			std::string mtlName;
			bool ok = parse(f, l, "" >> +(char_ - eol), mtlName);
			if (createdObj->mtllib != nullptr)
				currentMtl = createdObj->mtllib->GetMaterial(mtlName);
			else
				currentMtl = nullptr;

		}

		if ((f = static_cast<const char*>(memchr(f, '\n', l - f))))
			m_numLines++, f++;
	}


	if (curMesh->triangleIndexes.size() != 0)
	{
		createdObj->objObjects.push_back(CreateObjObject(name, currentMtl, meshData, curMesh));
	}

	return createdObj;
}

SBR::OBJ_mtllib* SBR::ResourceLoader::LoadObjMtlLib(std::string path)
{
	using namespace boost::spirit::qi;
	OBJ_mtllib* createdMtlLib = new OBJ_mtllib();
	OBJ_mtl* curMtl = nullptr;

	boost::filesystem::path fileDir = boost::filesystem::path(path);
	fileDir.remove_filename();

	boost::iostreams::mapped_file mmap(path, boost::iostreams::mapped_file::readonly);
	auto f = mmap.const_data();
	auto l = f + mmap.size();
	uintmax_t m_numLines = 0;

	while (f && f != l)
	{
		if (f[0] == 'n' && f[1] == 'e' && f[2] == 'w' && f[3] == 'm' && f[4] == 't' && f[5] == 'l')
		{
			curMtl = new OBJ_mtl();
			createdMtlLib->materials.push_back(curMtl);
			std::string mtlName;
			bool ok = parse(f, l, "newmtl " >> +(char_ - eol), mtlName);
			curMtl->name = mtlName;
		}

		else if (f[0] == 'K' && f[1] == 'a')
		{
			f += 3;
			bool ok = parse(f, l, float_ > ' ' > float_ > ' ' > float_, curMtl->ambientColor);
		}
		else if (f[0] == 'K' && f[1] == 'd')
		{
			f += 3;
			bool ok = parse(f, l, float_ > ' ' > float_ > ' ' > float_, curMtl->diffuseColor);
		}
		else if (f[0] == 'K' && f[1] == 's')
		{
			f += 3;
			bool ok = parse(f, l, float_ > ' ' > float_ > ' ' > float_, curMtl->specularColor);
		}
		else if (f[0] == 'N' && f[1] == 's')
		{
			f += 3;
			bool ok = parse(f, l, float_, curMtl->shininess);
		}
		else if (f[0] == 'd' && f[1] == ' ')
		{
			f += 2;
			bool ok = parse(f, l, float_, curMtl->transparency);
		}
		else if (f[0] == 'T' && f[1] == 'r'&&f[2] == ' ')
		{
			f += 3;
			bool ok = parse(f, l, float_, curMtl->transparency);
		}
		else if (f[0] == 'i' && f[1] == 'l'&&f[2] == 'l'&&f[3] == 'u'&&f[4] == 'm'&&f[5] == 'n')
		{
			f += 7;
			bool ok = parse(f, l, int_, curMtl->illuminationModel);
		}
		else if (f[0] == 'm' && f[1] == 'a'&&f[2] == 'p'&&f[3] == '_'&&f[4] == 'K'&&f[5] == 'a')
		{
			f += 7;
			std::string textureRelPath;
			bool ok = parse(f, l, "" >> +(char_ - eol), textureRelPath);
			boost::filesystem::path texturePath = fileDir / "\\" / textureRelPath;
			curMtl->ambientTexture = SBR::ResourceLoader::LoadTexture(texturePath.string());
		}
		else if (f[0] == 'm' && f[1] == 'a'&&f[2] == 'p'&&f[3] == '_'&&f[4] == 'K'&&f[5] == 'd')
		{
			f += 7;
			std::string textureRelPath;
			bool ok = parse(f, l, "" >> +(char_ - eol), textureRelPath);
			boost::filesystem::path texturePath = fileDir / "\\" / textureRelPath;
			curMtl->diffuseTexture = SBR::ResourceLoader::LoadTexture(texturePath.string());
		}
		else if (f[0] == 'm' && f[1] == 'a'&&f[2] == 'p'&&f[3] == '_'&&f[4] == 'K'&&f[5] == 's')
		{
			f += 7;
			std::string textureRelPath;
			bool ok = parse(f, l, "" >> +(char_ - eol), textureRelPath);
			boost::filesystem::path texturePath = fileDir / "\\" / textureRelPath;
			curMtl->specularTexture = SBR::ResourceLoader::LoadTexture(texturePath.string());
		}
		else if (f[0] == 'm' && f[1] == 'a' && f[2] == 'p' && f[3] == '_' && f[4] == 'b' && f[5] == 'u' &&  f[6] == 'm' && f[7] == 'p' && f[8] == ' ')
		{
			f += 8;
			std::string textureRelPath;
			bool ok = parse(f, l, "" >> +(char_ - eol), textureRelPath);
			boost::filesystem::path texturePath = fileDir / "\\" / textureRelPath;
			curMtl->bumpTexture = SBR::ResourceLoader::LoadTexture(texturePath.string());
		}
		else if (f[0] == 'b' && f[1] == 'u' && f[2] == 'm' && f[3] == 'p' && f[4] == ' ')
		{
			f += 5;
			std::string textureRelPath;
			bool ok = parse(f, l, "" >> +(char_ - eol), textureRelPath);
			boost::filesystem::path texturePath = fileDir / "\\" / textureRelPath;
			curMtl->bumpTexture = SBR::ResourceLoader::LoadTexture(texturePath.string());
		}

		if ((f = static_cast<const char*>(memchr(f, '\n', l - f))))
			m_numLines++, f++;
	}

	return createdMtlLib;
}