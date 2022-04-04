#pragma once
#include <memory>
#include <string>
#include <Windows.h>
#include "..\network\NetworkException.h"
#include "..\network\UDPSocket.h"

#define SERVER_PORT 5559
#define ECHO_PORT 5560

struct SendInput {
	UINT msg;
	LPARAM lParam;
	WPARAM wParam;
};


class App
{
public:
	App();
	

	~App();
	App(App& app) = delete;
	void Go();
	void onEvent(UINT msg, LPARAM lParam, WPARAM wPararm);


	void operator =(App& app) = delete;


private:
	
	struct IPv4 local;
	struct SendInput input;
	UDPSocket sender;
	struct IPv4 remote;
	bool AllGood = false;

};