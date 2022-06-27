#pragma once
#include "Date.h"

class DateException {
private:
	std::string message;
public:
	DateException(std::string message) : message(message) {};
	std::string getMessage() const { return message; }
};

class DateValidator {
public:
	static void validate(Date& d);
};