#include "..\pch.h"
#include "ServerClient.h"
#include "Server.h"

SBN::ServerClient::ServerClient(SOCKET* socket, sockaddr_in* socketAddr, Server* server)
{
	this->_socket = socket;
	this->recvThread = std::thread();
	this->buffer = (char*)malloc(sizeof(char*)*SBE_PACKAGE_MAXSIZE);
	this->recvThreadRunning = false;
	this->socketAddr = socketAddr;
	this->server = server;
}

SBN::ServerClient::~ServerClient()
{
	this->StopRecieving();
	delete this->buffer;
	closesocket(*this->_socket);
	free(this->_socket);
	free(this->socketAddr);
}

void SBN::ServerClient::StartRecieving()
{
	if (recvThreadRunning == true)
		return;

	recvThreadRunning = true;
	this->recvThread = std::thread(&ServerClient::Recieve, this);
}

void SBN::ServerClient::StopRecieving()
{
	if (this->recvThreadRunning)
	{
		this->recvThread.detach();
		this->recvThreadRunning = false;
	}
}

int SBN::ServerClient::Send(char * data, int len)
{
	return send(*this->_socket, data, len, 0);
}

void SBN::ServerClient::Recieve()
{
	while (true)
	{
		int size = recv(*this->_socket, this->buffer, SBE_PACKAGE_MAXSIZE, 0);
		if(size == SOCKET_ERROR)
		{
			int errorCode = WSAGetLastError();
			printf("recv failed: %d\r\n", errorCode);
			if (errorCode == 10054)
			{
				printf("Connection reset by peer. Closing Socket.\r\n");
				server->RemoveClient(this);
				break;
			}
		}
		else
		{
			buffer[size] = 0;
			printf(buffer);
		}
	}
}