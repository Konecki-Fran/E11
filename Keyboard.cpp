#include "Keyboard.h"

void Keyboard::OnKeyDown(unsigned int keycode) {
	keys[keycode] = true;
}

void Keyboard::OnKeyUp(unsigned int keycode) {
	keys[keycode] = false;
}