#include "..\pch.h"
#include "Server.h"
#include "ServerClient.h"

SBN::Server::Server(u_short port)
{
	this->port = port;
	this->_socket = (SOCKET*)malloc(sizeof(SOCKET));
	this->socketAddr = (sockaddr_in*) malloc(sizeof(sockaddr_in));
}

SBN::Server::~Server()
{
	this->StopListen();

	for (auto it = this->clients.begin(); it != this->clients.end(); ++it)
	{
		delete *it;
	}

	closesocket(*this->_socket);
	free(socket);
	free(socketAddr);
}

void SBN::Server::Bind()
{
	*this->_socket = socket(AF_INET, SOCK_STREAM, 0);
	if (*this->_socket == INVALID_SOCKET)
	{
		printf("Could not create socket : %d", WSAGetLastError());
	}

	printf("Socket created.\n");

	//Prepare the sockaddr_in structure

	socketAddr->sin_family = AF_INET;
	socketAddr->sin_addr.s_addr = INADDR_ANY;
	socketAddr->sin_port = htons(this->port);

	//Bind
	int error = bind(*this->_socket, (struct sockaddr*) socketAddr, sizeof(sockaddr_in));
	if (error == SOCKET_ERROR)
	{
		printf("Bind failed with error code : %d", WSAGetLastError());
	}
}

void SBN::Server::Listen()
{
	listen(*this->_socket, 3);

	while (true)
	{
		sockaddr_in* clientAddr = (sockaddr_in*) malloc(sizeof(sockaddr_in));
		int c = sizeof(struct sockaddr_in);
		SOCKET* clientSocket = (SOCKET*)malloc(sizeof(SOCKET));
		*clientSocket = accept(*this->_socket, (struct sockaddr *)clientAddr, &c);
		if (*clientSocket == INVALID_SOCKET)
		{
			printf("Accept failed with error code : %d\r\n", WSAGetLastError());
		}
		else
		{
			this->LockClients();
			ServerClient* client = new ServerClient(clientSocket, clientAddr, this);
			this->clients.push_back(client);
			client->StartRecieving();
			printf("New Client connected");
			this->UnlockClients();
		}
	}
}

void SBN::Server::StartListen()
{
	if (this->listenThreadRunning == true)
		return;
	this->listenThreadRunning = true;
	this->listenThread = std::thread(&SBN::Server::Listen, this);
}

void SBN::Server::StopListen()
{
	if (this->listenThreadRunning)
	{
		this->listenThread.detach();
		this->listenThreadRunning = false;
	}
}