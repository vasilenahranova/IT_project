#include<iostream>
#include"Trip.h"
std::ostream& operator<<(std::ostream& os, const Trip& obj1)
{
	std::cout << obj1.Destination << " " << obj1.Timeperiod << " " << obj1.Grade << " " << obj1.Comment << std::endl;
	return os;
}