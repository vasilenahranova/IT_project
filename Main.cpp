#include<iostream>
#include<cstring>
#include<string>
#include"User.h"
#include<fstream>
bool checkUserName(const std::string username) {
	int length = username.length();
	for (int i = 0; i < length; i++) {
		if ((username[i]<'0' || (username[i]>'9') && username[i]<'A') || (username[i]>'Z' && username[i]<'a') || username[i]>'z') 
		{
			std::cout <<"Invalid username.It must include ONLY Latin letters and numbers!Try again!" << std::endl;
			return false;
		}
	}
	return true;
}
void inputUser(std::string& username, std::string& password, std::string& email) {
	std::cout << "Enter username:"; std::cin >> username; 
	while(!checkUserName(username)) {
		std::cin >> username;
	};
	std::cout << "Enter password:"; std::cin >> password;
	std::cout << "Enter email:"; std::cin >> email;
}
void inputTrip(std::string& destination,std::string& timeperiod, int& grade,std::string& comment) {
	std::cout << "Enter name of your Destination:"; std::getline(std::cin, destination, '\n');
	std::cout << "Enter the Time period:"; std::getline(std::cin, timeperiod, '\n');
	std::cout << "Enter your Comment:"; std::getline(std::cin, comment, '\n');
	std::cout << "Enter your grade:"; std::cin >> grade;
}

int main() {
	std::string username, password, email;
	inputUser(username, password, email);
	User vassilena(username, password, email);
	std::ofstream UsersFile("UsersFile.txt", std::ios::app);
	if (UsersFile.is_open()) {
		UsersFile << username << " " << password << " " << email << std::endl;
	}
	UsersFile.close();
	std::cout << vassilena.getUserName() << " " << vassilena.getEmail() << " " << vassilena.getPassword() << std::endl;

	/*std::string destination,timeperiod,comment;
	int grade;
	inputTrip(destination, timeperiod, grade, comment);
	Trip trip1(destination, timeperiod, grade, comment);
	std::cout << trip1.getDestination() << " " << trip1.getTimeperiod() << " " << trip1.getGrade() << " " <<trip1.getComment() << std::endl;*/

}