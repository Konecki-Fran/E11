#include "WindowsFiltered.h"

#include <string>

#include "Mouse.h"
#include "Print.h"

void Mouse::OnLClick() {
	buttons[0] = true;
	std::string output = "Left Click";
	print(output.c_str());
}

void Mouse::OnMClick() {
	buttons[1] = true;
	std::string output = "Middle Click";
	print(output.c_str());
}
void Mouse::OnRClick() {
	buttons[2] = true;
	std::string output = "Right Click";
	print(output.c_str());
}

void Mouse::OnLRelease() {
	buttons[0] = false;
	std::string output = "Left Release";
	print(output.c_str());
}
void Mouse::OnMRelease() {
	buttons[1] = false;
	std::string output = "Middle Release";
	print(output.c_str());
}
void Mouse::OnRRelease() {
	buttons[2] = false;
	std::string output = "Right Release";
	print(output.c_str());
}

void Mouse::OnMove(int x, int y) {
	this->x = x;
	this->y = y;
	std::string output = "Mouse Move: " + std::to_string(x) + ", " + std::to_string(y);
	print(output.c_str());
}
void Mouse::OnWheel(short delta) {
	wheelDelta += delta;
	std::string output = "Mouse Wheel: " + std::to_string(delta);
	print(output.c_str());
}

