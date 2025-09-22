#include "Keyboard.h"
#include "Print.h"
#include "Window.h"
#include "WindowsFiltered.h"

char GetChar(unsigned int keycode) {
	// Numbers
	if (0x30 <= keycode && keycode <= 0x39) {
		return (char)(keycode);
	}

	// Letters
	else if (0x41 <= keycode && keycode <= 0x5A) {
		return (char)(keycode);
	}
}

void Keyboard::OnKeyDown(unsigned int keycode) {
	if (!keys[keycode])
	{
		keys[keycode] = true;
		std::string keyName{ GetChar(keycode) };
		std::string output{ "Pressed: " + keyName };

		print(output.c_str());
	}
}

void Keyboard::OnKeyUp(unsigned int keycode) {
	keys[keycode] = false;
}

