#pragma once

#include <string>
#include"WindowsFiltered.h"
#include "E11Exception.h"

class Window {
		class Exception : public E11Exception {};

public:
	Window(UINT x, UINT y, std::string name, HINSTANCE hInstance);
	static void initWindowClass(HINSTANCE hInstance);
	std::string TranslateErrorCode(HRESULT hr); 

public:
	HWND hWnd;
};
