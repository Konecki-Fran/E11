#pragma once

#include <string>
#include"WindowsFiltered.h"
#include "E11Exception.h"
#include "Keyboard.h"
#include "Mouse.h"
#include <memory>

class Window {
	class Exception : public E11Exception {};

public:
	Window(UINT x, UINT y, std::string name);
	~Window();
	std::string TranslateErrorCode(HRESULT hr);

	static HWND GetHWnd() {
		if (Window::phWnd) {
			return *phWnd;
		}

		throw E11Exception("Fetching uninitialized window handle");
	}

private:
	void initWindowClass();

public:
	HWND hWnd;
	HINSTANCE hInstance;
	const LPCWSTR className = L"E11 Window Class";

	inline static std::unique_ptr<Keyboard> keyboard = std::make_unique<Keyboard>();
	inline static std::unique_ptr<Mouse> mouse = std::make_unique<Mouse>();

	inline static HWND* phWnd = nullptr;

};
