#include "RepoValidator.h"

void RepoValidator::validate(EventRepo& r) {
	std::string errors = "";

	try {
		for (auto& ev : r.getEvents()) {
			EventValidator::validate(ev);
		}
	}
	catch (EventException& ee) {
		errors += std::string(ee.getMessage());
	}

	if (errors.size() > 0) {
		throw RepoException(errors);
	}
}