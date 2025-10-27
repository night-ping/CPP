// Time class member-function definitions
#include <iomanip>    // for setfill and setw
#include <stdexcept>  // for invalid_argument exception class
#include <sstream>    // for ostringstream class
#include <string>
#include "Time.h"     // include class definition 
		      
using namespace std;

void Time::setTime(int h, int m, int s)
{
	if((h >= 0 && h < 24) && (m >= 0 && m < 60) && (s >=0 && s < 60))
	{
		hour = h;
		minute = m;
		second = s;
	}else
	{
		throw invalid_argument("hour, minute and/or second was out of range!!");
	}
}

string Time::toUniversalString() const
{
	ostringstream output;
	output << setfill('0') << setw(2) << hour << ":"
		<< setw(2) << minute << ":" << setw(2) << second;
	return output.str();
}

string Time::toStandardString() const
{
	ostringstream output;
	output << setfill('0') << setw(2) << ((hour == 0 || hour == 12) ? 12 : hour % 12) << ":"
		<< setw(2) << minute << ":" << setw(2) << second << (hour < 12 ? " AM" : " PM");
	return output.str();
}

