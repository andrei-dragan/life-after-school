#include "DateValidator.h"

using namespace std;

void DateValidator::validate(Date& d) {
	string errors;
	
	int day = d.getDay();
	int month = d.getMonth();
	int year = d.getYear();
	int hour = d.getHour();
	int minute = d.getMinute();

	if (0 >= day || day >= 32)
		errors += string("Date should not have that many days!\n");

	if (0 >= month || month >= 13)
		errors += string("Date should not have that many months!\n");

	if (!(year >= 2021))
		errors += string("Date should be no earlier than the beginning of 2021!\n");

	if ((month == 4 || month == 6 || month == 9 || month == 11) && day == 31)
		errors += string("This month of the date does not have that many days!\n");
	if (month == 2) {
		if (!(year % 4 == 0 && year % 100 != 0) && day >= 29)
			errors += string("Februry does not have that many days!\n");
		else if (year % 4 == 0 && year % 100 != 0 && day >= 30)
			errors += string("Februry does not have that many days!\n");
	}

	if (0 > hour || hour >= 24)
		errors += string("Hour should be between 0 and 23!\n");

	if (0 > minute || minute > 59)
		errors += string("Minute should be between 0 and 59!\n");

	if (errors.size() > 0)
		throw DateException(errors);
}