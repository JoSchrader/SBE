#pragma once
#include "..\SBE_Internal.h"
#include "..\Math\SBM.h"

#include <vector>

namespace SBGM
{
	class SBE_API GameObject
	{
	public:
		std::vector<GameObject*> childs;
		SBM::Vector3 position;
		SBM::Vector3 scale;
		SBM::Quaternion rotation;

		GameObject()
		{
			this->position = SBM::Vector3(0, 0, 0);
			this->scale = SBM::Vector3(1, 1, 1);
			this->rotation = SBM::Quaternion();
		}
		~GameObject()
		{

		}
	};
}
