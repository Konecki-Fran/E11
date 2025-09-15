#pragma once

#include <string>
#include"WindowsFiltered.h"

class Window {
public:
	Window(UINT x, UINT y, std::string name, HINSTANCE hInstance);
	static void initWindowClass(HINSTANCE hInstance);

public:
	HWND hWnd;
};
