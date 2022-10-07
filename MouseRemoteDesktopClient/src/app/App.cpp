#include "App.h"

App::App() {

}

App::App(int width, int height) :
	width(width),
	height(height),
	remote({192,168,18,255})
{
	
	ZeroMemory(msg, 512);
	GetMyIP(local);
	UDPReceiver recv(ECHO_PORT);
	//recv.Recv(reinterpret_cast<char*>(&remote), 4);

	sender.Bind(remote, SERVER_PORT);
	AllGood = true;
}

App::~App()
{}

void App::Go() {

	

}

void App::OnEvent(UINT msg, LPARAM lParam, WPARAM wParam)
{
	

	POINTS pt;
	int delta = 0;
	switch (msg)
	{

	case WM_KEYDOWN:
		
	case WM_SYSKEYDOWN:
		input.type = INPUT_KEYBOARD;
		input.ki.wVk = static_cast<unsigned char>(wParam);
		input.ki.wScan = 0;
		input.ki.dwFlags = 0;
		input.ki.dwExtraInfo = 0;
		input.ki.time = 0;
		break;

	case WM_KEYUP:
	case WM_SYSKEYUP:input.type = INPUT_KEYBOARD;
		input.ki.wVk = static_cast<unsigned char>(wParam);
		input.ki.wScan = 0;
		input.ki.dwFlags = 0;
		input.ki.dwExtraInfo = KEYEVENTF_KEYUP;
		input.ki.time = 0;
		break;

	case WM_CHAR:
		break;

	case WM_MOUSEMOVE:
		pt = MAKEPOINTS(lParam);
		input.type = INPUT_MOUSE;
		input.mi.dx = pt.x;
		input.mi.dy = pt.y;
		input.mi.dwFlags = MOUSEEVENTF_MOVE;
		input.mi.dwExtraInfo = 0;
		input.mi.time = 0;
		input.mi.mouseData = 0;
		break;
	case WM_LBUTTONDOWN:
		pt = MAKEPOINTS(lParam);
		input.type = INPUT_MOUSE;
		input.mi.dx = pt.x;
		input.mi.dy = pt.y;
		input.mi.dwFlags = MOUSEEVENTF_LEFTDOWN;
		input.mi.dwExtraInfo = 0;
		input.mi.time = 0;
		input.mi.mouseData = 0;
		break;

	case WM_RBUTTONDOWN:
		pt = MAKEPOINTS(lParam);
		input.type = INPUT_MOUSE;
		input.mi.dx = pt.x;
		input.mi.dy = pt.y;
		input.mi.dwFlags = MOUSEEVENTF_RIGHTDOWN;
		input.mi.dwExtraInfo = 0;
		input.mi.time = 0;
		input.mi.mouseData = 0;
		break;

	case WM_LBUTTONUP:
		pt = MAKEPOINTS(lParam);
		input.type = INPUT_MOUSE;
		input.mi.dx = pt.x;
		input.mi.dy = pt.y;
		input.mi.dwFlags = MOUSEEVENTF_LEFTUP;
		input.mi.dwExtraInfo = 0;
		input.mi.time = 0;
		input.mi.mouseData = 0;
		break;

	case WM_RBUTTONUP:
		pt = MAKEPOINTS(lParam);
		input.type = INPUT_MOUSE;
		input.mi.dx = pt.x;
		input.mi.dy = pt.y;
		input.mi.dwFlags = MOUSEEVENTF_RIGHTUP;
		input.mi.dwExtraInfo = 0;
		input.mi.time = 0;
		input.mi.mouseData = 0;
		break;

	case WM_MOUSEWHEEL:

		pt = MAKEPOINTS(lParam);
		delta = GET_WHEEL_DELTA_WPARAM(wParam);
		input.type = INPUT_MOUSE;
		input.mi.dx = pt.x;
		input.mi.dy = pt.y;
		input.mi.dwFlags = MOUSEEVENTF_WHEEL;
		input.mi.time = 0;
		input.mi.mouseData = delta;
		break;


	default:
		break;
	}

	MakeJSON();

	if (AllGood) {
		sender.Send(reinterpret_cast<const char*>(this->msg), sizeof(512));
	}


#ifndef NDEBUG
	OutputDebugString((LPCSTR)this->msg);
#endif // !NDEBUG


}



void App::MakeJSON() {
	
	ZeroMemory(msg, 512);
	std::string json = std::string("{").append(std::string("\"type\":")).append(std::to_string(input.type)).append(",");
	if (input.type == INPUT_MOUSE) {

		double dx = (double)input.mi.dx;
		double dy = (double)input.mi.dy;

		double normX = dx / (double)this->width;
		double normY = dy / (double)this->height;

		json.append(std::string("\"dx\":").append(std::to_string(normX)).append(","));
		json.append(std::string("\"dy\":").append(std::to_string(normY)).append(","));
		json.append(std::string("\"mouseData\":")).append(std::to_string(input.mi.mouseData).append(","));

		json.append(std::string("\"dwFlags\":").append(std::to_string(input.mi.dwFlags)).append(","));
		json.append(std::string("\"time\":")).append(std::to_string(input.mi.time).append(","));
		json.append(std::string("\"dwExtraInfo\":")).append(std::to_string(input.mi.dwExtraInfo));
	}
	else if (input.type == INPUT_KEYBOARD) {
		json.append(std::string("\"wVk\":").append(std::to_string(input.ki.wVk).append(",")));
		json.append(std::string("\"wScan\":")).append(std::to_string(input.ki.wScan).append(","));

		json.append(std::string("\"dwFlags\":").append(std::to_string(input.ki.dwFlags)).append(","));
		json.append(std::string("\"time\":")).append(std::to_string(input.ki.time).append(","));
		json.append(std::string("\"dwExtraInfo\":")).append(std::to_string(input.ki.dwExtraInfo));
	}
	json.append("}\n");

	strcpy_s(msg, json.c_str());
}