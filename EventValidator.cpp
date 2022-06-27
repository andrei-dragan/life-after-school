#include "EventValidator.h"

void EventValidator::validate(Event& e) {
	std::string errors = "";

	try {
		DateValidator::validate(e.getDate());
	}
	catch (DateException& de) {
		errors += std::string(de.getMessage());
	}

	if (errors.size() > 0) {
		errors = std::string("Event " + e.getTitle() + "has the following errors: \n") + errors;
		throw EventException(errors);
	}
}