#pragma once
#include "..\pch.h"
#include "Texture.h"
#include "Material.h"
#include "..\Math\SBM.h"

#define SBE_MODEL_MAGIC_BYTES 0x4D454253 

namespace SBR
{
	enum SBE_EXPORT ModelType
	{
		i3fP3fN2fT_ID = 1,
		f3fPc3fN2sT_ID = 2
	};	
}