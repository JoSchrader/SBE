#include "..\SBE_Internal.h"
#include "Client.h"
#include <windows.h>

SBN::Client::Client(const char* server, u_short port)
{
	int len = (int) strlen(server);
	this->server = (char*)malloc(sizeof(char) * (len + 1));
	strcpy(this->server, server);
	this->server[strlen(server)] = 0;
	this->port = port;
	this->_socket = (SOCKET*)malloc(sizeof(SOCKET));
	this->socketAddr = (sockaddr_in*)malloc(sizeof(sockaddr_in));
	this->buffer = (char*)malloc(sizeof(char)*SBE_PACKAGE_MAXSIZE);
}

SBN::Client::~Client()
{
	free(server);
	free(buffer);
	this->StopRecieving();
	closesocket(*this->_socket);
	free(socket);
	free(socketAddr);
}

bool SBN::Client::Connect()
{
	*this->_socket = socket(AF_INET, SOCK_STREAM, 0);
	if (*this->_socket == INVALID_SOCKET)
	{
		printf("Could not create socket : %d\r\n", WSAGetLastError());
		return false;
	}

	socketAddr->sin_addr.s_addr = inet_addr(this->server);
	socketAddr->sin_family = AF_INET;
	socketAddr->sin_port = htons(this->port);

	int status;
	for (int i = 0; i < 10; i++ )
	{
		status = connect(*_socket, (struct sockaddr *)socketAddr, sizeof(sockaddr));
		if (status < 0)
		{
			printf("Connect attempt failed\r\n");
			Sleep(500);
		}
		else
		{
			break;
		}
	}

	if (status < 0)
	{
		printf("Stopped Connecting after 10 retries");
		return false;
	}

	printf("Connected - Lewl");
	return true;
}

bool SBN::Client::Send(const char * const data, int len)
{
	
	if (send(*this->_socket, data, len, 0) < 0)
	{
		printf("Send failed");
		return false;
	}

	return true;
}

void SBN::Client::Reciev()
{
	while (true)
	{
		int recv_size = recv(*this->_socket, buffer, SBE_PACKAGE_MAXSIZE, 0);
		if (recv_size == SOCKET_ERROR)
		{
			int errorCode = WSAGetLastError();
			printf("recv failed: %d\r\n", errorCode);
			if (errorCode == 10054)
			{
				printf("Connection reset by peer. Closing Socket.\r\n");
				this->recvThreadRunning = false;
				break;
			}
		}
		else
		{
			printf(buffer); printf("\r\n");
		}
	}
}

void SBN::Client::StartRecieving()
{
	if (this->recvThreadRunning)
		return;

	this->recvThreadRunning = true;
	this->recvThread = std::thread(&SBN::Client::Reciev, this);
}

void SBN::Client::StopRecieving()
{
	if (this->recvThreadRunning)
	{
		this->recvThread.detach();
		this->recvThreadRunning = false;
	}
}

