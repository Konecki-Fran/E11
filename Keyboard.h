#pragma once

class Keyboard {
public:
	void OnKeyDown(unsigned int keyCode);
	void OnKeyUp(unsigned int keyCode);

private:
	bool keys[256];

};