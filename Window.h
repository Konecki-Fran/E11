#pragma once

#include <string>
#include"WindowsFiltered.h"
#include "E11Exception.h"

class Window {
	class Exception : public E11Exception {};

public:
	Window(UINT x, UINT y, std::string name, HINSTANCE hInstance);
	~Window();
	std::string TranslateErrorCode(HRESULT hr);

private:
	void initWindowClass();

public:
	HWND hWnd;
	HINSTANCE hInstance;
	const LPCWSTR className = L"E11 Window Class";

};
