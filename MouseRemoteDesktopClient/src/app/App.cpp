#include "App.h"

App::App()
{
	
	

}

App::~App()
{}

void App::Go() {
	
	GetMyIP(local);
	UDPSocket recv(ECHO_PORT);
	recv.Recv(reinterpret_cast<char*>(&remote), 4);
	
	sender.Bind(remote, SERVER_PORT);
	sender.SetSourcePort(SERVER_PORT);
	AllGood = true;
	
	input.msg = 45;
	input.lParam = 555;
	input.wParam = 856;

	sender.Send(reinterpret_cast<const char*>(&input), sizeof(input));
}

void App::onEvent(UINT msg, LPARAM lParam, WPARAM wPararm)
{
	input.msg = msg;
	input.lParam = lParam;
	input.wParam = wPararm;
	if (AllGood) {
		sender.Send(reinterpret_cast<const char*>(&input), sizeof(input));
	}
	

#ifndef NDEBUG
	OutputDebugString((LPCWSTR)(std::string("msg:").append(std::to_string(msg)).append("\n")).c_str());
#endif // !NDEBUG


}
