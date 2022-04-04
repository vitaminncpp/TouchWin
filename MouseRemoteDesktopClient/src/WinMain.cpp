#include "wnd/Window.h"
#include "util/Timer.h"


int CALLBACK WinMain(HINSTANCE hInstance,
	HINSTANCE hPrev,
	LPSTR CmdLine,
	int nCmdShow) {
	Timer timer;
	Window wnd(1920, 1080, "MOuseRemote Dsktop Client");
	wnd.Gfx().SetProjection(DirectX::XMMatrixPerspectiveLH(1.0f, 3.0f / 4.0f, 0.5f, 40.0f));
	
	wnd.GetApp().Go();

	while (true)
	{


		// process all messages pending, but to not block for new messages
		if (const auto ecode = Window::ProcessMessages())
		{
			// if return optional has value, means we're quitting so return exit code
			return *ecode;
		}


		auto dt = timer.Mark();
		wnd.Gfx().ClearBuffer(0.07f, 0.0f, 0.12f);

		wnd.Gfx().EndFrame();

	}

	return 0;
}