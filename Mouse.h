#pragma once

class Mouse {
public:
	void OnLClick();
	void OnMClick();
	void OnRClick();

	void OnLRelease();
	void OnMRelease();
	void OnRRelease();

	void OnMove(int x, int y);
	void OnWheel(short delta);

private:
	bool buttons[3];
	int x, y;
	int wheelDelta;

};
