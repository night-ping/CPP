// Time class definition 
// member functions are defined in Time.cpp

#include <string>

#ifndef TIME_H
#define TIME_H

class Time
{
	public:
		void setTime(int, int, int);           // set hour, minute and second
		std::string toUniversalString() const; // 24-hour time format string
		std::string toStandardString() const;  // 12-hour time format string
	private:
		unsigned int hour{0};
		unsigned int minute{0};
		unsigned int second{0};		
};

#endif
