#pragma comment(lib, "ws2_32.lib")
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

	struct sockaddr_in server;
	server.sin_family = AF_INET;			//ipv4
	server.sin_port = htons(port);			//host to network socket
	server.sin_addr.s_addr = INADDR_ANY;	//mihin haluat bindata (verkkokortti) INADDR_ANY mikä tahansa verkkokortti

	s = socket(AF_INET, SOCK_DGRAM, 0);

	if (s == INVALID_SOCKET)
	{
		std::cout << "failed to create socket "
			<< WSAGetLastError() << std::endl;
		exit(EXIT_FAILURE);
	}

	if (bind(s,(struct sockaddr*)&server,
		sizeof(server)) == SOCKET_ERROR)	
	{
		std::cout << "Failed to bind socket: "
			<< WSAGetLastError() << std::endl;
		exit(EXIT_FAILURE);
	}

	const uint32_t MaxMessageSize = 512;
	char msgBuffer[MaxMessageSize];
	struct sockaddr_in from;
	int fromLen = sizeof(from);
	while (true)
	{
		//tyhjätään buffer a.k.a nollia täyteen
		memset(msgBuffer, 0, sizeof(msgBuffer));


		
		int bytes = recvfrom(
			s,								//mitä sockettia
			msgBuffer,						//mihin luetaan
			MaxMessageSize,					//paljon bufferissa tilaa
			0,								//flags
			(struct sockaddr*)&from,		//ip jne lähettäjältä
			&fromLen);						//kuinka iso lähettäjä on

		if (bytes == SOCKET_ERROR)
		{
			std::cout << "recvfrom failed: "
				<< WSAGetLastError() << std::endl;
			exit(EXIT_FAILURE);
		}
		// jos saatiin tavuja
		if (bytes > 0)
		{
			std::cout << ">> " << msgBuffer << std::endl;
		}
	}

	deinit();

	return EXIT_SUCCESS;
}