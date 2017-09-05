#include "..\pch.h"
#include "OBJ_mtl.h"

SBR::OBJ_mtl::OBJ_mtl()
{
	name = "";								//newmtl
	float transparency = 0.0f;				//d		tr
	ambientColor = SBM::Vector3(1, 1, 1);	//Ka
	diffuseColor = SBM::Vector3(1, 1, 1);	//Kd
	specularColor = SBM::Vector3(1, 1, 1);  //Ks
	shininess = 0;							//Ns
	illuminationModel = 0;					//illum
	ambientTexture = -1;					//map_ka
	diffuseTexture = -1;					//map_kd
	specularTexture = -1;					//map_ks
	alphaTexture = -1;						//map_d
	bumpTexture = -1;						//map_bump		bump
}

SBR::OBJ_mtl::~OBJ_mtl()
{
}