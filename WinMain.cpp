
#include "Window.h"

int APIENTRY wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
	LPWSTR lpCmdLine, int nCmdShow) {

	Window::initWindowClass(hInstance);
	auto window = Window(400, 400, "MyWindow", hInstance);
	try {

		throw std::exception("sdgsdg");

		MSG msg;
		BOOL result;
		while ((result = GetMessage(&msg, nullptr, 0, 0)) > 0) {
			TranslateMessage(&msg);
			DispatchMessage(&msg);
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
		MessageBox(window.hWnd, errorMsg,L"Exception Caught", 0);
		return -1;
	}
	return 0;
}
