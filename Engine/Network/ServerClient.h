#pragma once
#include <winsock2.h>
#include <atomic>
#include <mutex>
#include "..\SBE_Internal.h"

namespace SBN
{
	class Server;

	class SBE_API ServerClient
	{	
	public:
		SOCKET* _socket;
		sockaddr_in* socketAddr;
		std::thread recvThread;
		std::atomic<bool> recvThreadRunning;
		char* buffer;
		Server* server;

		ServerClient(SOCKET* socket, sockaddr_in* socketAddr, Server* server);
		~ServerClient();

		void StartRecieving();
		void StopRecieving();

		int Send(char* data, int len);

	private:
		void Recieve();
	};
}