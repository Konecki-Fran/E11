#pragma once

#include <string>
#include"WindowsFiltered.h"

class Window {
public:
	Window(UINT x, UINT y, std::string name, HINSTANCE hInstance);
	static void initWindowClass(HINSTANCE hInstance);
	std::string TranslateErrorCode(HRESULT hr); 

public:
	HWND hWnd;
};
