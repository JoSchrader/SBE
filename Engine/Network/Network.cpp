#include "..\SBE_Internal.h"
#include <winsock2.h>
#include "Network.h"

void SBN::Network::Init()
{
	WSADATA wsaData;
	if (WSAStartup(MAKEWORD(1, 1), &wsaData) != 0) {
		//WSAStartup failed
		exit(1);
	}
}

SBE_API void SBN::Network::Cleanup()
{
	WSACleanup();
}
