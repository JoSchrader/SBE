#pragma once
#include "..\pch.h"
#include "ServerClient.h"

namespace SBN
{
	class SBE_EXPORT Server
	{
	public:
		SOCKET* _socket;
		sockaddr_in* socketAddr;
		u_short port;
		std::vector<ServerClient*> clients;
		std::mutex clientsMutex;

		std::thread listenThread;
		std::atomic<bool> listenThreadRunning;

		Server(u_short port);
		~Server();

		void Bind();
		void StartListen();
		void StopListen();

		void LockClients() { std::lock_guard<std::mutex> lock(clientsMutex); }
		void UnlockClients() { std::lock_guard<std::mutex> unlock(clientsMutex); }

		void SendToAll(char* buffer, int len)
		{
			LockClients();
			for (auto it = clients.begin(); it != clients.end(); it++)
			{
				(*it)->Send(buffer, len);
			}

			UnlockClients();
		}

		void RemoveClient(ServerClient* client)
		{
			LockClients();			
			auto element = std::find(clients.begin(), clients.end(), client);
			if (element != clients.end())
				clients.erase(element);
			delete client;
			UnlockClients();
		}

	private:
		void Listen();
	};
}