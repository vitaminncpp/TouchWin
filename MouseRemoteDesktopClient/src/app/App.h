#pragma once
#include "..\wnd\Window.h"
#include "..\util\Timer.h"

class App
{
public:
	App();
	
	int Go();
	~App();
private:
	void DoFrame();
private:
	Window wnd;
	Timer timer;
};