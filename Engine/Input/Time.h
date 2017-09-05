#pragma once
#include "..\pch.h"

namespace SBI
{
	class SBE_EXPORT Time
	{
	public:
		GLfloat ellapsedTime;
		GLfloat deltaTime;
		GLfloat fps;
		GLfloat timeScale;
		GLfloat fixedTime;

		Time(void);
		~Time(void);

		void Update();

		static GLfloat EllapsedTime();
		static GLfloat DeltaTime();
		static GLfloat Fps();
	};
}