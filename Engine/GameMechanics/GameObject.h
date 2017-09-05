#pragma once
#include "..\pch.h"
#include "..\Math\SBM.h"

namespace SBGM
{
	class SBE_EXPORT GameObject
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
