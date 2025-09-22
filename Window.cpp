#include <sstream>
#include "Window.h"
#include "resource.h"
#include <iostream>
#include "Print.h"
#include "App.h"

#define KEYBOARD_ACTION WM_KEYDOWN: case WM_KEYUP
#define MOUSE_ACTION WM_LBUTTONDOWN: case WM_LBUTTONUP: case WM_RBUTTONDOWN: case WM_RBUTTONUP: case WM_MBUTTONDOWN: case WM_MBUTTONUP: case WM_MOUSEMOVE: case WM_MOUSEWHEEL

void HandleKeyboardMessage(UINT msg, WPARAM wParam, LPARAM lParam) {
	switch (msg)
	{

		//	case WM_CHAR: {}
	case WM_KEYDOWN:
	{
		if (wParam == VK_ESCAPE) {
			PostQuitMessage(69);
			IApp::Stop();
		}
		else {
			bool isHeldDown = lParam & 0x4000FFFF;
			Window::keyboard->OnKeyDown(wParam);
		}
		break;
	}

	case WM_KEYUP:
	{
		Window::keyboard->OnKeyUp(wParam);
		break;
	}
	default:
		break;
	}
}

void HandleMouseMessage(UINT msg, WPARAM wParam, LPARAM lParam) {
	switch (msg) {
	case WM_MOUSEMOVE:
	{
		auto points = MAKEPOINTS(lParam);
		Window::mouse->OnMove(points.x, points.y);
		break;
	}
	case WM_LBUTTONDOWN:
	{
		Window::mouse->OnLClick();
		break;
	}
	case WM_LBUTTONUP:
	{
		Window::mouse->OnLRelease();
		break;
	}
	case WM_RBUTTONDOWN:
	{
		Window::mouse->OnRClick();
		break;
	}
	case WM_RBUTTONUP:
	{
		Window::mouse->OnRRelease();
		break;
	}
	case WM_MBUTTONDOWN:
	{
		Window::mouse->OnMClick();
		break;
	}
	case WM_MBUTTONUP:
	{
		Window::mouse->OnMRelease();
		break;
	}
	case WM_MOUSEWHEEL:
	{
		auto zDelta = GET_WHEEL_DELTA_WPARAM(wParam);
		Window::mouse->OnWheel(zDelta);
		break;
	}
	default:
		break;
	}
}

LRESULT WINAPI WindowProc(
	_In_ HWND hWnd,
	_In_ UINT msg,
	_In_ WPARAM wParam,
	_In_ LPARAM lParam)
{
	switch (msg)
	{
	case WM_CLOSE:
	{
		PostQuitMessage(69);
		IApp::Stop();
		break;
	}
	case KEYBOARD_ACTION:
	{
		HandleKeyboardMessage(msg, wParam, lParam);
		break;
	}
	case MOUSE_ACTION:
	{
		HandleMouseMessage(msg, wParam, lParam);
		break;
	}
	default:
		break;
	}

	return DefWindowProcW(hWnd, msg, wParam, lParam);
}

Window::Window(UINT x, UINT y, std::string name) {
	initWindowClass();

	RECT wr;
	wr.left = 100;
	wr.right = x + wr.left;
	wr.top = 100;
	wr.bottom = y + wr.top;
	AdjustWindowRect(&wr, WS_CAPTION | WS_MINIMIZEBOX | WS_SYSMENU, FALSE);
	// create window & get hWnd
	hWnd = CreateWindowExW(
		0, className, L"WindowName", WS_CAPTION | WS_MINIMIZEBOX | WS_SYSMENU,
		200, 200,
		wr.right - wr.left, wr.bottom - wr.top,
		nullptr, nullptr, GetModuleHandle(NULL), this
	);

	Window::phWnd = &hWnd;
	ShowWindow(hWnd, SW_SHOWDEFAULT);
}

void Window::initWindowClass()
{
	WNDCLASSEXW wc = { 0 };

	wc.cbSize = sizeof(wc);
	wc.style = CS_OWNDC;
	wc.lpfnWndProc = WindowProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = GetModuleHandle(nullptr);
	wc.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_ICON1));
	wc.hCursor = nullptr;
	wc.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	wc.lpszMenuName = nullptr;
	wc.lpszClassName = className;
	wc.hIconSm = nullptr;

	RegisterClassExW(&wc);
}

Window::~Window() {
	UnregisterClass(className, hInstance);
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
