#include "wnd/Window.h"
#include "util/Timer.h"

void GetDesktopResolution(int& horizontal, int& vertical);

int CALLBACK WinMain(HINSTANCE hInstance,
	HINSTANCE hPrev,
	LPSTR CmdLine,
	int nCmdShow) {

	int width;
	int height;
	GetDesktopResolution(width,height);

	Timer timer;

	Window wnd(width, height, "MouseRemote Dsktop Client");
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


void GetDesktopResolution(int& horizontal, int& vertical)
{
	RECT desktop;
	const HWND hDesktop = GetDesktopWindow();
	GetWindowRect(hDesktop, &desktop);
	horizontal = desktop.right;
	vertical = desktop.bottom;
}