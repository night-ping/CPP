#include <iostream>
#include <stdexcept>
#include "Time.h"

using namespace std;

void displayTime(const string& message, const Time& time)
{
	cout << message << "\nUniversal time: " << time.toUniversalString() 
		<< "\nStandard time: " << time.toStandardString() << "\n\n";
}

int main()
{
	Time t;
	displayTime("Initial time: ", t); // display t's initial values
	t.setTime(13, 27, 6); // change the time
	displayTime("After setTime: ", t);

	try{
		t.setTime(99, 99, 99); // try all out of range values

	}catch (invalid_argument& e)
	{
		cout << "Exception: " << e.what() << "\n\n";
	}

	displayTime("After attempting to set an invalid time: ", t);

}
