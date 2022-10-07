#pragma once
#include <memory>
#include <string>
#include <Windows.h>
#include "..\network\NetworkException.h"
#include "..\network\UDPSocket.h"

#define SERVER_PORT 5559
#define ECHO_PORT 5560

class App
{
public:
	App();
	App(int, int);

	~App();
	
	App(App& app) = delete;
	void Go();
	void OnEvent(UINT msg, LPARAM lParam, WPARAM wPararm);


	void operator =(App& app) = delete;



private:

	INPUT input;
	struct IPv4 local;
	UDPSender sender;
	struct IPv4 remote;
	bool AllGood = false;
	int width;
	int height;
	char msg[512];
	void MakeJSON();
};