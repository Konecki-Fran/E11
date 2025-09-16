#include "Timer.h"

Timer::Timer() {
	last = std::chrono::steady_clock::now();
};
float Timer::Mark() {
	auto oldTimePoint = last;
	last = std::chrono::steady_clock::now();
	std::chrono::duration<float> result = last - oldTimePoint;
	return result.count();

};
float Timer::Peek() {
	auto now = std::chrono::steady_clock::now();
	std::chrono::duration<float> result = now - last;
	return result.count();
};