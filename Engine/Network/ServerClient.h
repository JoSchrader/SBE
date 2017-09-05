#pragma once
#include "..\pch.h"

namespace SBN
{
	class Server;

	class SBE_EXPORT ServerClient
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