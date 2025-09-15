#pragma once

class Keyboard {
	void OnKeyDown();
	void OnKeyUp();


private:
	bool keys[256];

};