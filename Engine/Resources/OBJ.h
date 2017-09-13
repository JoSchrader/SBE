#pragma once
#include "..\SBE_Internal.h"
#include "..\Math\SBM.h"

namespace SBR
{
	class Mesh;

	class OBJ_mtl
	{
	public:
		std::string name;				//newmtl
		SBM::Vector3 ambientColor;		//Ka
		SBM::Vector3 diffuseColor;		//Kd
		SBM::Vector3 specularColor;		//Ks
		float transparency;				//d		tr
		int shininess;					//Ns
		int illuminationModel;			//illum
		int ambientTexture;				//map_ka
		int diffuseTexture;				//map_kd
		int specularTexture;			//map_ks
		int alphaTexture;				//map_d
		int bumpTexture;				//map_bump		bump
	};

	class OBJ_mtllib
	{
	public:
		std::vector<OBJ_mtl*> materials;
	};


	class OBJ_Object
	{
	public:
		Mesh* mesh;
		OBJ_mtl* material;
		char* name;
	};

	class OBJ
	{
	public:
		std::vector<OBJ_Object*> objObjects;
		OBJ_mtllib* mtllib;
	};

}