#pragma once
#include "Event.h"
#include "DateValidator.h"

class EventException {
private:
	std::string message;
public:
	EventException(std::string message) : message(message) {};
	std::string getMessage() const { return message; }
};

class EventValidator {
public:
	static void validate(Event& e);
};
