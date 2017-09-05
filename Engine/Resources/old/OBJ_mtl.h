#pragma once
#include "..\pch.h"
#include "Resource.h"
#include "..\Math\Vector3.h"

namespace SBR
{
	class OBJ_mtl : public Resource
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
		OBJ_mtl();
		~OBJ_mtl();
	};	
}