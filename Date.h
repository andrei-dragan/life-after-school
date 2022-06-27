#pragma once
#include <string>
#include <vector>
#include <sstream>

class Date {
private:
	int day;
	int month;
	int year;
	int hour;
	int minute;
public:
	/*
		Constructor for Date
		Input: day - integer = day of the date
			   month - integer = month of the date
			   year - integer = year of the date
			   hour - integer = hour of the date
			   minute - integer = minute of the date
		Output: None
	*/
	Date(int day = 1, int month = 1, int year = 9999, int hour = 0, int minute = 0);
	
	/*
		Copy constructor for Date
		Input: &d - reference to a Date
		Output: None
	*/
	Date(const Date& d);

	/*
		Destructor for Date
		Input: None
		Output: None
	*/
	~Date() = default;

	/*
		Equality operator(==) between two Dates
		Two Dates are equal if the fields: day | month | year | hour | minute are equal
		Input: &d - reference to a Date to be checked for equality
		Output: true if equality stands, false otherwise
	*/
	bool operator==(const Date& d);

	/*
		Get the month of a Date
		Input: None
		Output: integere = the month of the Date
	*/
	int getMonth() { return this->month; }
	int getDay() { return this->day; }
	int getYear() { return this->year; }
	int getHour() { return this->hour; }
	int getMinute() { return this->minute; }

	/*
		Greater operator(>). Checks if the current Date is greater than another one.
		A Date is greater than another one, if it describes a later time.
		Input: &d - reference to a Date that will be compared
		Output: true if the current Date is greater, false otherwise
	*/
	bool operator>(const Date& d);
};