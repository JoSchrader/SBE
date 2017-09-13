#pragma once
#include "..\SBE_Internal.h"

#define SBE_TCP_STREAM SOCK_STREAM
#define SBE_UDP_STREAM SOCK_DGRAM

namespace SBN
{


	class Network
	{
	public:
		static SBE_API void Init();
		static SBE_API void Cleanup();
	};
}