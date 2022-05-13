#include "User.h"

std::ostream& operator<<(std::ostream& os, const User& obj1)
{
	std::cout << obj1.UserName << " " << obj1.Password << " " << obj1.Email << std::endl;
	return os;
}

