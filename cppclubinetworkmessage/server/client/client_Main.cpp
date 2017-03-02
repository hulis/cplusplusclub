#pragma comment(lib, "ws2_32.lib")
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#include <WinSock2.h>
#include <Windows.h>

#include <iostream>
#include <stdint.h>

bool init()
{
	WSADATA wsa;
	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
	{
		return false;
	}

	return true;
}

void deinit()
{
	WSACleanup();
}

int main()
{
	if (!init()){
		std::cout << "Winsoc initialization failed" << std::endl;
		exit(EXIT_FAILURE);
	}

	SOCKET s = NULL;

	unsigned short port = 1337;

	struct sockaddr_in serverAddr;
	serverAddr.sin_family = AF_INET;						//ipv4
	serverAddr.sin_port = htons(port);						//host to network socket
	serverAddr.sin_addr.s_addr = inet_addr("172.31.16.85");	//mihin haluat bindata (verkkokortti) INADDR_ANY mikä tahansa verkkokortti

	struct sockaddr_in clientAddr;
	clientAddr.sin_family = AF_INET;
	clientAddr.sin_addr.s_addr = INADDR_ANY;
	clientAddr.sin_port = 0; // random portti

	s = socket(AF_INET, SOCK_DGRAM, 0);

	if (s == INVALID_SOCKET)
	{
		std::cout << "failed to create socket "
			<< WSAGetLastError() << std::endl;
		exit(EXIT_FAILURE);
	}

	if (bind(s, (struct sockaddr*)&clientAddr,
		sizeof(clientAddr)) == SOCKET_ERROR)
	{
		std::cout << "Failed to bind socket: "
			<< WSAGetLastError() << std::endl;
		exit(EXIT_FAILURE);
	}

	const uint32_t MaxMessageSize = 512;
	char msgBuffer[MaxMessageSize];
	while (true)
	{
		/*/tyhjätään buffer a.k.a nollia täyteen
		memset(msgBuffer, 0, sizeof(msgBuffer));*/

		char msg[] = "Hello world";
		strcpy(msgBuffer, "Hello world");

		int sentBytes = sendto(s,
			msg,
			strlen(msg),
			0,
			(struct sockaddr*)&serverAddr, 
			sizeof(serverAddr));
		
		if (sentBytes == SOCKET_ERROR)
		{
			std::cout << "sendto failed: " << WSAGetLastError() << std::endl;
			exit(EXIT_FAILURE);
		}

	}

	deinit();

	return EXIT_SUCCESS;
}