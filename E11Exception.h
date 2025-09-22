#pragma once

#include <exception>

class E11Exception : public std::exception {
public:
	E11Exception(const char* message) : std::exception(message) {}

};