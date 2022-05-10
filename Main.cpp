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

//additional functions for the time period validation
void shiftCharIntoInt(const char ch, int& i) {
	if (ch == '0') i = 0;
	if (ch == '1') i = 1;
	if (ch == '2') i = 2;
	if (ch == '3') i = 3;
	if (ch == '4') i = 4;
	if (ch == '5') i = 5;
	if (ch == '6') i = 6;
	if (ch == '7') i = 7;
	if (ch == '8') i = 8;
	if (ch == '9') i = 9;
}
void transformDate(const std::string timeperiod, const int Index, int& date) {
	int h, s, d, e;
	if (Index == 6 || Index == 17) {
		shiftCharIntoInt(timeperiod[Index], h);
		shiftCharIntoInt(timeperiod[Index + 1], s);
		shiftCharIntoInt(timeperiod[Index + 2], d);
		shiftCharIntoInt(timeperiod[Index + 3], e);
		date = h * 1000 + s * 100 + d * 10 + e;
	}
	else {
		if (timeperiod[Index] == '0')
			shiftCharIntoInt(timeperiod[Index + 1], date);
		if (timeperiod[Index] >= '1' && timeperiod[Index] <= '9') {
			shiftCharIntoInt(timeperiod[Index], d);
			shiftCharIntoInt(timeperiod[Index + 1], e);
			date = d * 10 + e;
		}
	}
}
void transformTimePeriod(const std::string timeperiod, int& day1, int& month1, int& year1, int& day2, int& month2, int& year2) {
	transformDate(timeperiod, 0, day1);
	transformDate(timeperiod, 3, month1);
	transformDate(timeperiod, 6, year1);
	transformDate(timeperiod, 11, day2);
	transformDate(timeperiod, 14, month2);
	transformDate(timeperiod, 17, year2);
}
bool checkValidDates(const int day1, const int month1, const int year1, const int day2, const int month2, const int year2) {
	if (month1 > 12)  return false;
	if (month2 > 12) return false;
	if (month1 == 1 || month1 == 3 || month1 == 5 || month1 == 7 || month1 == 8 || month1 == 10 || month1 == 12)
		if (day1 > 31) return false;
	if (month2 == 1 || month2 == 3 || month2 == 5 || month2 == 7 || month2 == 8 || month2 == 10 || month2 == 12)
		if (day2 > 31) return false;
	if (month1 == 4 || month1 == 6 || month1 == 9 || month1 == 11)
		if (day1 > 30) return false;
	if (month2 == 4 || month2 == 6 || month2 == 9 || month2 == 11)
		if (day2 > 30) return false;
	if (month1 == 2)
		if (day1 > 28) return false;
	if (month2 == 2)
		if (day2 > 28) return false;
	return true;
}
bool checkAdditionalCondition(const int day1, const int month1, const int year1, const int day2, const int month2, const int year2) {

	if (year2 > year1)return true;
	if (year2 < year1) return false;
	if (year2 == year1) {
		if (month2 > month1) return true;
		if (month2 < month1) return false;
		if (month2 == month1) {
			if (day2 >= day1) return true;
			if (day2 < day1) return false;
		}
	}
	return true;
}

bool checkTimePeriod(const std::string timeperiod, const int day1, const int month1, const int year1, const int day2, const int month2, const int year2) {
	//check if the string is in the right form2
	if (timeperiod.size() != 21) return false;
	for (int i = 0; i < timeperiod.size(); i++) {
		if ((timeperiod[i] < '0' || timeperiod[i]>'9') && timeperiod[i] != '.' && timeperiod[i] != '-')
			return false;
	}
	//check for the valid dates 
	if (!checkValidDates(day1, month1, year1, day2, month2, year2)) return false;
	//check for the additional condition - the second needs to be bigger than the first
	if (!checkAdditionalCondition(day1, month1, year1, day2, month2, year2)) return false;
	return true;

}
bool checkGrade(const int grade) {
	return (grade>0 && grade < 7);
}
void inputUser(std::string& username, std::string& password, std::string& email) {
	std::cout << "Enter username:"; std::cin >> username; 
	while(!checkUserName(username)) {
		std::cin >> username;
	};
	std::cout << "Enter password:"; std::cin >> password;
	std::cout << "Enter email:"; std::cin >> email;
}
void inputTrip(std::string& destination,std::string& timeperiod, unsigned int& grade,std::string& comment) {
	std::cout << "Enter name of your Destination:"; std::getline(std::cin, destination, '\n');
	std::cout << "Enter the Time period:"; std::getline(std::cin, timeperiod, '\n');
	int day1, month1, year1, day2, month2, year2;
	transformTimePeriod(timeperiod, day1, month1, year1, day2, month2, year2);
	while (!checkTimePeriod(timeperiod, day1, month1, year1, day2, month2, year2)) {
		std::cout << "Invalid input for timeperiod!" << std::endl;
		std::cin >> timeperiod;
		transformTimePeriod(timeperiod, day1, month1, year1, day2, month2, year2);
	}
	std::cout << "Enter your Comment:"; std::getline(std::cin, comment, '\n');
	std::cout << "Enter your grade:"; std::cin >> grade;
	while (!checkGrade(grade)) {
		std::cout << "Invalid grade! It must be an integer number between 1 and 6! " << std::endl;
		std::cin >> grade;
	}

}

//functions for writing in/reading out of Files
void readTripsFromBinaryFile(Trip*& trips, int& size, const std::string username) {
	std::ifstream personalfile(username, std::ios::binary);
	personalfile.seekg(0, std::ios::end);
	size = personalfile.tellg() / sizeof(Trip);
	trips = new Trip[size];
	personalfile.seekg(0, std::ios::beg);
	personalfile.read((char*)trips, size * (sizeof(Trip)));
	personalfile.close();
}
void saveTripToBinaryFile(Trip trip1, const std::string username) {
	/*if (!trip1) {
		return;
	}*/
	std::ofstream personalFile(username, std::ios::binary);
	personalFile.seekp(0, std::ios::end);
	personalFile.write((char*)&trip1, sizeof(Trip));
	personalFile.close();
}
void searchAllInformationAboutADestination(std::string) {
	double Suma = 0, count = 0;
	for (int i = 0; i < size; i++) {
		if (currentUserTrip[i].getDestination() == chooseDestination) {
			count++;
			Suma += currentUserTrip[i].getGrade();
		}
	}
	for (int i = 0; i < size; i++) {
		if (currentUserTrip[i].getDestination() == chooseDestination) {
			std::cout << "The time period is " << currentUserTrip[i].getTimeperiod() << " " << "Their grade is " << currentUserTrip[i].getGrade() << " " << "Their comment is " << currentUserTrip[i].getComment() << std::endl;
		}
	}
	if (count > 0)
		std::cout << "The rate for this destination is " << Suma / count << std::endl;
	else
		std::cout << "There are no such trips!" << std::endl;
}
void readUsersFromBinaryFile(User*& users,int& size) {
	std::ifstream UsersDataBase("UsersDataBase", std::ios::binary);
	UsersDataBase.seekg(0, std::ios::end);
	size = UsersDataBase.tellg() / sizeof(User);
	users = new User[size];
	UsersDataBase.seekg(0, std::ios::beg);
	UsersDataBase.read((char*)users, size * (sizeof(User)));
	UsersDataBase.close();
}
int main() {
	int choice;
	std::cout << "Make your choice:" << std::endl;
	std::cout << "Press 1 for REGISTER" << std::endl;
	std::cout << "Press 2 for LOGIN" << std::endl;
	while (choice != 1 && choice != 2) {
		std::cout << "Invalid command!" << std::endl;
		std::cin >> choice;
	}
	std::string username, password, email;
	if (choice == 1) {
		//save the new user data into the whole DataBase
		inputUser(username, password, email);
		User vassilena(username, password, email);
		std::ofstream UsersDataBase("UsersDataBase", std::ios::binary);
		UsersDataBase.seekp(0, std::ios::end);
		UsersDataBase.write((char*)&username, sizeof(username));
		UsersDataBase.write((char*)&password, sizeof(password));
		UsersDataBase.write((char*)&email, sizeof(email));
		UsersDataBase.close();

		//create a new ownDataBase
		std::fstream personalFile(username, std::ios::binary);

		//choose next activity
		int choice2;
		std::cout << "Make your choice:" << std::endl;
		std::cout << "Press 1 for REGISTER a new Trip!" << std::endl;
		std::cout << "Press 2 for search of a definite destination!" << std::endl;
		while (choice2 != 1 && choice2 != 2) {
			std::cout << "Invalid command!" << std::endl;
			std::cin >> choice2;
		}
		if (choice2 == 1) {
			std::string destination, timeperiod, comment;
			unsigned int grade;
			inputTrip(destination, timeperiod, grade, comment);
			Trip newTrip(destination, timeperiod, grade, comment);
			saveTripToBinaryFile(newTrip, username);
		}
		if (choice2 == 2) {
			//still not written function
			std::string chooseDestination;
			std::cout << "Enter destination: "; std::cin >> chooseDestination;
			searchAllInformationAboutADestination(chooseDestination);
		}
	}
	if (choice == 2) {
		//I need to search through the DateBase and check if such user exists
		int size = 0;
		User* currentDataBase = nullptr;
		readUsersFromBinaryFile(currentDataBase, size);
		for (int i = 0; i < size; i++) {
			if (currentDataBase[i].getUserName() == inputUserName) {
				if (currentDataBase[i].getPassword() == inputPassword) {
					std::fstream personalFile(inputUserName, std::ios::binary);
					//call the function for choice2 again 
				}
			}
		}

	}
	std::string destination = "Sofia", timeperiod = "23.12.2021-25.12.2022", comment = "This is very beautiful";
	unsigned int grade = 4;
	//inputTrip(destination, timeperiod, grade, comment);
	Trip trip1(destination, timeperiod, grade, comment);
	destination = "Sofia", timeperiod = "23.12.2021-25.12.2022", comment = "This is beautiful", grade=5;
	Trip trip2(destination, timeperiod, grade, comment);
	Trip trips[] = { trip1,trip2 };
	saveTripToBinaryFile(trip1, username);
	
	int size = 0;
	Trip* currentUserTrip = nullptr;
	readTripsFromBinaryFile(currentUserTrip, size,username);


	
}