#pragma once
#include "..\SBE_Internal.h"
#include "..\Math\SBM.h"
#include <vector>


namespace SBGM
{
	class SBE_API Pipeline
	{
	public:
		std::vector<SBM::Matrix4> modelMatrix;
		SBM::Matrix4 viewMatrix;
		SBM::Matrix4 projectionMatrix;

		Pipeline(void);
		~Pipeline(void);

		void Push();
		void Pop();

		void UpdateMatrices(unsigned int programId);

		void operator*=(SBM::Matrix4);
		void operator=(SBM::Matrix4 other);
	};
}
