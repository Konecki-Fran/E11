#pragma once

#include <chrono>

using time_point = std::chrono::high_resolution_clock::time_point;

class Timer {
public:
	Timer() noexcept;
	float Mark() noexcept;
	float Peek() noexcept;

private:
	time_point last;
};