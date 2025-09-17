#pragma once

#include <chrono>

using time_point = std::chrono::high_resolution_clock::time_point;

class Timer {
public:
	Timer();
	float Mark();
	float Peek();

private:
	time_point last;
};