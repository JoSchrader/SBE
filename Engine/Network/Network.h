#pragma once
#include "..\pch.h"

#define SBE_TCP_STREAM SOCK_STREAM
#define SBE_UDP_STREAM SOCK_DGRAM

namespace SBN
{


	class Network
	{
	public:
		static SBE_EXPORT void Init();
		static SBE_EXPORT void Cleanup();
	};
}