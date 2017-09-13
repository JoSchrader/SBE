#pragma once
#include "..\SBE_Internal.h"
#include <winsock2.h>
#include <atomic>
#include <mutex>

namespace SBN
{
	class SBE_API Client
	{
	public:
		SOCKET* _socket;
		sockaddr_in* socketAddr;
		char* server;
		u_short port;
		char* buffer;

		std::thread recvThread;
		std::atomic<bool> recvThreadRunning;

		Client(const char* server, u_short port);
		~Client();

		bool Connect();
		bool Send(const char* const data, int len);

		void StartRecieving();
		void StopRecieving();

	private:
		void Reciev();
	};
}