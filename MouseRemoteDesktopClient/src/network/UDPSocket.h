#pragma once

#include <iostream>
#include <string>
#include <exception>
#include "NetworkException.h"


struct IPv4
{
	unsigned char s_b1, s_b2, s_b3, s_b4;
};




bool GetMyIP(struct IPv4& myIP);

class UDPSocket
{
private:
	SOCKET sock;
	WSAData wsaData;
	sockaddr_in toRecv;
	sockaddr_in toSend;
	int sizeOfRecvAddr;
	unsigned short port;
	unsigned short sport;


public:
	UDPSocket();
	UDPSocket(unsigned short port);
	UDPSocket(IPv4& ip);
	UDPSocket(IPv4& ip, unsigned short port);
	~UDPSocket()noexcept;

public:
	int Bind(unsigned short port);
	int Bind(IPv4& ip, unsigned short port);

	int Send(IPv4& ip, const char* data, int size, int flags = 0);
	int Send(const char* data, int size, int flags = 0);
	int Recv(char data[], int size, int flags = 0);
	int SetSourcePort(unsigned short port);


};

