#include "App.h"
#include "Window.h"
#include "D3DX11.h"
#include "Graphics.h"
#include "Timer.h"
#include "Keyboard.h"

#define MSG_AVAILABLE PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE)

int IApp::Start() {
	Window window{ 800, 600, "WindowName" };
	Graphics gfx{};
	Timer timer{};

	try {
		MSG msg;
		while (IApp::IsRunning()) {
			if (MSG_AVAILABLE) {
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}

			gfx.DrawTestTriangle();

			auto colorVal = (sin(timer.Peek()) + 1) / 2.f;
			gfx.ClearRTV({ colorVal, colorVal, colorVal });
			gfx.EndFrame(window.hWnd);
		}
		return IApp::instance->result;
	}
	catch (std::exception e) {
		auto errorMsg = (LPWSTR)e.what();
		MessageBox(window.hWnd, errorMsg, L"Exception Caught", 0);
		return -1;
	}
	return 0;
}

void IApp::Alert(const char* title, const char* msg) {
	MessageBoxA(nullptr, msg, title, MB_OK | MB_ICONEXCLAMATION);
}


