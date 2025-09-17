
#include "Window.h"
#include "D3DX11.h"
#include "Graphics.h"
#include "Timer.h"

void DoFrame() {
}

void ProcessMessages() {

}

int APIENTRY wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
	LPWSTR lpCmdLine, int nCmdShow) {

	Window::initWindowClass(hInstance);
	auto window = Window(400, 400, "MyWindow", hInstance);
	auto gfx = Graphics(window.hWnd);
	Timer timer{};

	try {
		MSG msg;
		BOOL result;
		while ((result = GetMessage(&msg, nullptr, 0, 0)) > 0) {
			TranslateMessage(&msg);
			DispatchMessage(&msg);

			auto colorVal = (sin(timer.Peek()) + 1) / 2.f;
			gfx.ClearRTV({ colorVal, colorVal, colorVal });
			gfx.EndFrame(window.hWnd);
		}

		if (result == -1) {
			return -1;
		}
		else {
			return msg.wParam;
		}

	}
	catch (std::exception e) {
		auto errorMsg = (LPWSTR)e.what();
		MessageBox(window.hWnd, errorMsg, L"Exception Caught", 0);
		return -1;
	}
	return 0;
}
