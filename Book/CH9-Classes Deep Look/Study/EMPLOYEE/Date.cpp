#include <array>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include "Date.h"
using namespace std;

Date::Date(unsigned int mn, unsigned int dy, unsigned int yr)
	: month{mn}, day{checkDay(dy)}, year{yr}
{
	if(mn < 1 || mn > monthsPerYear)
	{
		throw invalid_argument("month must be 1-12");
	}

	cout << "Date object constructor for date " << toString() << endl; 
}

string Date::toString() const 
{
	ostringstream output;
	output << month << '/' << day << '/' << year;
	return output.str();

}

Date::~Date()
{
	cout << "Date object destructor for date " << toString() << endl;
}

// utility funciton to confirm proper day value based on month and year , handle leep year
unsigned int Date::checkDay(int testDay) const {
	static const array<int ,monthsPerYear + 1> daysPerMonth{
		0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31
	};

	if (testDay > 0 && testDay <= daysPerMonth[month])
	{
		return testDay;
	}

	if(month == 2 && testDay == 29 && (year % 400 == 0 || ( year % 4 == 0 && year % 100 != 0 )))
	{
		return testDay;
	}
	throw invalid_argument("Invalid day for current month and year");
} 
