#include "User.h"
#include<iostream>
#include<fstream>

std::ostream& operator<<(std::ostream& os, const User& obj1)
{
	std::cout << obj1.UserName << " " << obj1.Password << " " << obj1.Email << std::endl;
	return os;
}

//read/write function
void User::saveUserToBinaryFile() const
{
	std::ofstream UsersDataBase("UsersDataBase", std::ios::binary |std::ios::app);
	size_t lengthU = UserName.size();
	const char* username = UserName.getmyString();
	size_t lengthP = Password.size();
	const char* password = Password.getmyString();
	size_t lengthE = UserName.size();
	const char* email = Email.getmyString();

	UsersDataBase.write((char*)&lengthU , sizeof(lengthU));
	UsersDataBase.write(username, lengthU);
	UsersDataBase.write((char*)&lengthP, sizeof(lengthP));
	UsersDataBase.write(password, lengthP);
	UsersDataBase.write((char*)&lengthE, sizeof(lengthE));
	UsersDataBase.write(email, lengthE);
	UsersDataBase.close();
	//this->UserName = username;
	std::ofstream UserName(username, std::ios::binary | std::ios::app);
}

void User::readUserFromBinaryFile(User &User1,int Index)
{
	std::ifstream UsersDataBase("UsersDataBase", std::ios::binary);
	//here my idea was to start reading file from Index position in order to get all Users, instead of just the first one but that does not work
	//UsersDataBase.seekg(Index*sizeof(User), std::ios::beg);

	size_t lengthU = 0;
	char* username =new char[100];
	UsersDataBase.read((char*)& lengthU, sizeof(size_t));
	UsersDataBase.read(username, lengthU);
	username[lengthU] = '\0';

	size_t lengthP = 0;
	char* password = new char[100];
	UsersDataBase.read((char*)&lengthP, sizeof(size_t));
	UsersDataBase.read(password, lengthU);
	password[lengthP] = '\0';

	size_t lengthE = 0;
	char* email = new char[100];
	UsersDataBase.read((char*)&lengthE, sizeof(size_t));
	UsersDataBase.read(email, lengthE);
	email[lengthE] = '\0';

	UsersDataBase.close();
	User1=User(username, password, email);
}
