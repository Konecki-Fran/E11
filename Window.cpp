#include <sstream>
#include "Window.h"
#include "resource.h"

LRESULT WINAPI WindowProc(
	_In_ HWND hWnd,
	_In_ UINT msg,
	_In_ WPARAM wParam,
	_In_ LPARAM lParam)
{
	switch (msg)
	{
	case WM_CLOSE:
		PostQuitMessage(69);
		break;
	case WM_CHAR: {
		static std::wstring title;
		title.push_back((char)wParam);
		SetWindowTextW(hWnd, title.c_str());
		break;
	}
	case WM_LBUTTONDOWN:
	{
		auto pos = MAKEPOINTS(lParam);
		std::wstringstream oss{};
		oss << "(" << pos.x << ", " << pos.y << ")";
		SetWindowTextW(hWnd, oss.str().c_str());
		break;
	}
	case WM_KEYDOWN:
		if (wParam == VK_ESCAPE) {
			PostQuitMessage(69);
		}
		break;
	default:
		break;
	}

	return DefWindowProcW(hWnd, msg, wParam, lParam);
}

Window::Window(UINT x, UINT y, std::string name, HINSTANCE hInstance) {
	LPCWSTR classNameL = L"E11 Window Class";

	RECT wr;
	wr.left = 100;
	wr.right = x + wr.left;
	wr.top = 100;
	wr.bottom = y + wr.top;
	AdjustWindowRect(&wr, WS_CAPTION | WS_MINIMIZEBOX | WS_SYSMENU, FALSE);
	// create window & get hWnd
	hWnd = CreateWindowExW(
		0, classNameL, L"WindowName", WS_CAPTION | WS_MINIMIZEBOX | WS_SYSMENU,
		200, 200,
		wr.right - wr.left, wr.bottom - wr.top,
		nullptr, nullptr, GetModuleHandle(NULL), this
	);

	// show window
	ShowWindow(hWnd, SW_SHOWDEFAULT);
}

void Window::initWindowClass(HINSTANCE hInstance)
{
	WNDCLASSEXW wc = { 0 };
	LPCWSTR classNameL = L"E11 Window Class";

	wc.cbSize = sizeof(wc);
	wc.style = CS_OWNDC;
	wc.lpfnWndProc = WindowProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = hInstance;
	wc.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_ICON1));
	wc.hCursor = nullptr;
	wc.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	wc.lpszMenuName = nullptr;
	wc.lpszClassName = classNameL;
	wc.hIconSm = nullptr;

	RegisterClassExW(&wc);
}

std::string Window::TranslateErrorCode(HRESULT hr) 
{
	char* pMsgBuf = nullptr;
	// windows will allocate memory for err string and make our pointer point to it
	DWORD nMsgLen = FormatMessage(
		FORMAT_MESSAGE_ALLOCATE_BUFFER |
		FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
		nullptr, hr, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
		reinterpret_cast<LPWSTR>(&pMsgBuf), 0, nullptr
	);
	// 0 string length returned indicates a failure
	if (nMsgLen == 0)
	{
		return "Unidentified error code";
	}
	// copy error string from windows-allocated buffer to std::string
	std::string errorString = pMsgBuf;
	// free windows buffer
	LocalFree(pMsgBuf);
	return errorString;
}