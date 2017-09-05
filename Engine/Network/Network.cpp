#include "..\pch.h"
#include "Network.h"

void SBN::Network::Init()
{
	WSADATA wsaData;
	if (WSAStartup(MAKEWORD(1, 1), &wsaData) != 0) {
		fprintf(stderr, "WSAStartup failed.\n");
		exit(1);
	}
}

SBE_EXPORT void SBN::Network::Cleanup()
{
	WSACleanup();
}
