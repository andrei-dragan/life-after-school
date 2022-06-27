#pragma once
#include "EventRepo.h"
#include "EventValidator.h"

class RepoException {
private:
	std::string message;
public:
	RepoException(std::string message) : message(message) {};
	std::string getMessage() const { return message; }
};

class RepoValidator {
public:
	static void validate(EventRepo& r);
};
