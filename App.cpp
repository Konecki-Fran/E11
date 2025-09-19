#include "App.h"


#include "Window.h"
#include "D3DX11.h"
#include "Graphics.h"
#include "Timer.h"
#include "Keyboard.h"

void App::Start() {

	auto hInstance = GetModuleHandle(nullptr);

	auto window = Window(400, 400, "MyWindow", hInstance);
	auto gfx = Graphics(window.hWnd);

	Timer timer{};
	Keyboard keyboard{};

	try {
		MSG msg;
		BOOL result;
		while ((result = PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE)) >= 0) {
			TranslateMessage(&msg);
			DispatchMessage(&msg);

			auto colorVal = (sin(timer.Peek()) + 1) / 2.f;
			gfx.ClearRTV({ colorVal, colorVal, colorVal });
			gfx.EndFrame(window.hWnd);
		}

		if (result == -1) {
			//return -1;
		}
		else {
			//return msg.wParam;
		}

	}
	catch (std::exception e) {
		auto errorMsg = (LPWSTR)e.what();
		MessageBox(window.hWnd, errorMsg, L"Exception Caught", 0);
		//return -1;
	}
	//return 0;
}

void App::Alert(const char* title, const char* msg) {
	MessageBoxA(nullptr, msg, title, MB_OK | MB_ICONEXCLAMATION);
}
