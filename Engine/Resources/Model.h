#pragma once
#include "..\pch.h"
#include "Texture.h"
#include "Material.h"
#include "..\Math\SBM.h"

namespace SBR
{
	class ModelPart;

	enum SBE_EXPORT ModelType
	{
		i3fP3fN2fT_ID = 1,
		f3fPc3fN2sT_ID = 2
	};

	class SBE_EXPORT Model
	{
	public:
		char* name;
		ModelPart** parts;
		int amountOfParts;

		virtual void Save(char* buffer) = 0;
		virtual void Load(char* buffer) = 0;
		virtual int GetSize() = 0;
	};

	class SBE_EXPORT ModelPart
	{
	public:
		char* name;
		char* texturePath;
		char* materialPath;
		Texture* texure;
		Material* material;
		Model* model;

		virtual void Save(char* buffer) = 0;
		virtual void Load(char* buffer) = 0;
		virtual int GetSize() = 0;
	};	
}