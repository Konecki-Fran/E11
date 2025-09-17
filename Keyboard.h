#pragma once

class Keyboard {
	void OnKeyDown(unsigned int keyCode);
	void OnKeyUp(unsigned int keyCode);


private:
	bool keys[256];

};