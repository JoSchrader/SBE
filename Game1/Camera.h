#pragma once
#include "Client\ClientPCH.h"

class Camera
{
public:
	SBM::Vector3 position;
	SBM::Quaternion rotation;

	Camera()
	{
		position = SBM::Vector3(0, 0, -10);
	}

	void Update(SBI::Keyboard* keyboard, SBI::Cursor* cursor, SBI::Time* time, SBGM::Pipeline* pipe)
	{
		SBM::Vector3 up = SBM::Vector3(0, 1, 0);
		SBM::Vector3 forward = rotation * SBM::Vector3(0, 0, 1);

		SBM::Vector3 move = SBM::Vector3(0, 0, 0);

		if (keyboard->GetKeyPressed(SBI::Keys::W)) move += forward;
		if (keyboard->GetKeyPressed(SBI::Keys::S)) move -= forward;
		if (keyboard->GetKeyPressed(SBI::Keys::D)) move += forward.Cross(up);
		if (keyboard->GetKeyPressed(SBI::Keys::A)) move -= forward.Cross(up);
		if (keyboard->GetKeyPressed(SBI::Keys::E)) move += forward.Cross(up).Cross(forward);
		if (keyboard->GetKeyPressed(SBI::Keys::Q)) move -= forward.Cross(up).Cross(forward);

		move *= time->deltaTime*100.0f;

		this->position += move;

		this->rotation = SBM::Quaternion::Euler((float)-cursor->moveY *0.001f, 0, 0) * this->rotation;
		this->rotation = this->rotation *  SBM::Quaternion::Euler(0, (float) cursor->moveX*0.001f, 0);

		pipe->viewMatrix = SBM::Matrix4::LookAt(position, position + forward, up);
	}
};