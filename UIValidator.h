#pragma once

class UIException {
private:
	std::string message;
public:
	UIException(std::string message) : message(message) {};
	std::string getMessage() const { return message; }
};
