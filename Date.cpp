#include "Date.h"
#include <assert.h>
#include <iostream>
#include <stdexcept>

Date::Date(int day, int month, int year, int hour, int minute) {	
	this->day = day;
	this->month = month;
	this->year = year;
	this->hour = hour;
	this->minute = minute;
}

Date::Date(const Date& d) {
	this->day = d.day;
	this->month = d.month;
	this->year = d.year;
	this->hour = d.hour;
	this->minute = d.minute;
}

bool Date::operator==(const Date& d) {
	return (this->day == d.day && this->month == d.month && this->year == d.year && this->hour == d.hour && this->minute == d.minute);
}

bool Date::operator>(const Date& d) {
	if (this->year > d.year)
		return true;
	else if (this->year < d.year)
		return false;

	if (this->month > d.month)
		return true;
	else if (this->month < d.month)
		return false;

	if (this->day > d.day)
		return true;
	else if (this->day < d.day)
		return false;

	if (this->hour > d.hour)
		return true;
	else if (this->hour < d.hour)
		return false;

	if (this->minute > d.minute)
		return true;
	return false;
}