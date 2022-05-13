#include<iostream>
#include"User.h"
#include"String.h"
#include"Trip.h"
#include<fstream>


bool checkUserName(String username) {
	int length = username.length();
	for (int i = 0; i < length; i++) {
		if ((username.at(i)<'0' || (username.at(i) >'9') && username.at(i) <'A') || (username.at(i) >'Z' && username.at(i) <'a') || username.at(i) >'z')
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
void transformDate(String timeperiod, const int Index, int& date) {
	int h, s, d, e;
	if (Index == 6 || Index == 17) {
		shiftCharIntoInt(timeperiod.at(Index), h);
		shiftCharIntoInt(timeperiod.at(Index + 1), s);
		shiftCharIntoInt(timeperiod.at(Index + 2), d);
		shiftCharIntoInt(timeperiod.at(Index + 3), e);
		date = h * 1000 + s * 100 + d * 10 + e;
	}
	else {
		if (timeperiod.at(Index) == '0')
			shiftCharIntoInt(timeperiod.at(Index + 1), date);
		if (timeperiod.at(Index) >= '1' && timeperiod.at(Index) <= '9') {
			shiftCharIntoInt(timeperiod.at(Index), d);
			shiftCharIntoInt(timeperiod.at(Index + 1), e);
			date = d * 10 + e;
		}
	}
}
void transformTimePeriod(String timeperiod, int& day1, int& month1, int& year1, int& day2, int& month2, int& year2) {
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

//validation functions
bool checkTimePeriod(String timeperiod, const int day1, const int month1, const int year1, const int day2, const int month2, const int year2) {
	//check if the string is in the right form2
	if (timeperiod.size() != 21) return false;
	for (int i = 0; i < timeperiod.size(); i++) {
		if ((timeperiod.at(i) < '0' || timeperiod.at(i)>'9') && timeperiod.at(i) != '.' && timeperiod.at(i) != '-')
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
void inputUser(String& username, String& password, String& email) {
	std::cout << "Enter username:"; std::cin >> username; 
	while(!checkUserName(username)) {
		std::cin >> username;
	};
	std::cout << "Enter password:"; std::cin >> password;
	std::cout << "Enter email:"; std::cin >> email;
}
void inputTrip(String& destination,String& timeperiod, unsigned int& grade,String& comment) {
	std::cout << "Enter name of your Destination:"; std::cin>>destination;
	std::cout << "Enter the Time period:"; std::cin>>timeperiod;
	int day1, month1, year1, day2, month2, year2;
	transformTimePeriod(timeperiod, day1, month1, year1, day2, month2, year2);
	while (!checkTimePeriod(timeperiod, day1, month1, year1, day2, month2, year2)) {
		std::cout << "Invalid input for timeperiod!" << std::endl;
		std::cin >> timeperiod;
		std::cin.ignore();
		transformTimePeriod(timeperiod, day1, month1, year1, day2, month2, year2);
	}
	std::cin.ignore();
	std::cout << "Enter your Comment:"; std::cin>>comment;
	std::cout << "Enter your grade:"; std::cin >> grade;
	while (!checkGrade(grade)) {
		std::cout << "Invalid grade! It must be an integer number between 1 and 6! " << std::endl;
		std::cin >> grade;
	}

}
void readTripsFromBinaryFile(Trip* trips, size_t& size, char* username) {
	std::ifstream personalFile(username, std::ios::binary);
	personalFile.seekg(0, std::ios::end);
	size = personalFile.tellg() / sizeof(Trip);
	trips = new Trip[size];
	personalFile.seekg(0, std::ios::beg);
	for (int i = 0; i < size; i++) {
		personalFile.read((char*)&trips[i], sizeof(Trip));
	}
	personalFile.close();
	std::cout << "I am ready!" << std::endl;
	std::cout << size << std::endl;
}
//writing in/reading out of Trip File
void saveTripToBinaryFile(Trip trip1, char* username) {
	std::ofstream personalFile(username, std::ios::binary | std::ios::app | std::ios::ate);
	//personalFile.seekp(0, std::ios::end);
	personalFile.write((char*)&trip1, sizeof(Trip));
	personalFile.close();
}

//choices functions
void firstChoice(int& choice) {
	std::cout << "Make your choice:" << std::endl;
	std::cout << "Press 1 for REGISTER" << std::endl;
	std::cout << "Press 2 for LOGIN" << std::endl;
	std::cin >> choice;
	while (choice != 1 && choice != 2) {
		std::cout << "Invalid command!" << std::endl;
		std::cin >> choice;
	}
}
void secondChoice(int& choice2) {
	std::cout << "Make your choice:" << std::endl;
	std::cout << "Press 1 for REGISTER a new Trip!" << std::endl;
	std::cout << "Press 2 for search of a definite destination!" << std::endl;
	std::cin >> choice2;
	while (choice2 != 1 && choice2 != 2) {
		std::cout << "Invalid command!" << std::endl;
		std::cin >> choice2;
	}
}
//readingUsersFile
void readUsersFromBinaryFile(User* &users,size_t& size) {
	std::ifstream UsersDataBase("UsersDataBase", std::ios::binary);
	UsersDataBase.seekg(0, std::ios::end);
	size = UsersDataBase.tellg() / sizeof(User);
	users = new User[size];
	UsersDataBase.seekg(0, std::ios::beg);
	for(size_t i =  0; i < size; i++)
		UsersDataBase.read((char*)&users[i], sizeof(User));
	UsersDataBase.close();
}
//searchByDestination functions
void searchByDestination(String destination, char* username) {
	size_t size1 = 0;
	Trip* trips = nullptr;
	readTripsFromBinaryFile(trips, size1, username);
	std::cout << size1;
	for (unsigned int i = 0; i < size1; i++) {
		std::cout << "I am in the loop of trips for concrete user!"<<std::endl;
		//std::cout << trips[i].gettimeperiod() << std::endl;
		/*if (trips[i].getdestination() == destination) {
			std::cout << "timeperiod: " << trips[i].gettimeperiod() << " grade: " << trips[i].getgrade() << " comment: " << trips[i].getcomment() << std::endl;
		}*/
	}
}
/*void searchByDestinationGeneral() {
	String username;
	String destination1;
	std::cout << "Enter destination: "; std::cin >> destination1;

	size_t size = 0;
	User* currentDataBase = nullptr;
	readUsersFromBinaryFile(currentDataBase, size);
	for (int i = 0; i < size; i++) {
		username = currentDataBase[i].getUserName();
		std::cout << "I am in the loop of Users!" << std::endl;
		//std::ifstream mypersonalfile(username, std::ios::binary);
		searchByDestination(destination1, username);
	}

}*/
int main() {
	int choice=0;
	firstChoice(choice);
	String username, password, email;
	if (choice == 1) {
		//save the new user data into the whole DataBase
		std::cin.ignore();
		inputUser(username, password, email);
		User vassilena(username, password, email);
		std::cout << vassilena << std::endl;
		std::ofstream UsersDataBase("UsersDataBase", std::ios::binary | std::ios::app | std::ios::ate);
		UsersDataBase.write((const char *)&vassilena, sizeof(vassilena));
		UsersDataBase.close();
		////create a new ownDataBase
		////transform into username.myString char[]
		//char* username1 = username.getmyString();
		//std::fstream personalFile(username1, std::ios::binary);

		////choose next activity
		//int choice2=0;
		//secondChoice(choice2);
		//std::cin.ignore();
		//if (choice2 == 1) {
		//	String destination, timeperiod, comment;
		//	unsigned int grade;
		//	inputTrip(destination, timeperiod, grade, comment);
		//	Trip newTrip(destination, timeperiod, grade, comment);
		//	saveTripToBinaryFile(newTrip, username1);
		//}
		//if (choice2 == 2)
		//	searchByDestinationGeneral();
	}
	//if (choice == 2) {
	//	//I need to search through the DateBase and check if such user exists
	//	String inputUserName, inputPassword;
	//	std::cout << "Enter Username:"; std::cin >> inputUserName;
	//	std::cout << "Enter Password:"; std::cin >> inputPassword;

	//	size_t size = 0;
	//	User* currentDataBase = nullptr;
	//	readUsersFromBinaryFile(currentDataBase, size);
	//	bool check = false;
	//	for (int i = 0; i < size; i++) {
	//		if (currentDataBase[i].getUserName() == inputUserName) {
	//			std::cout << "Valid username"<<std::endl;
	//			if (currentDataBase[i].getPassword() == inputPassword) {
	//				int choice2 = 0;
	//				secondChoice(choice2);
	//				std::cin.ignore();
	//				if (choice2 == 1) {
	//					String destination, timeperiod, comment;
	//					unsigned int grade;
	//					inputTrip(destination, timeperiod, grade, comment);
	//					Trip newTrip(destination, timeperiod, grade, comment);
	//					char *inputUserName1 = inputUserName.getmyString();
	//					saveTripToBinaryFile(newTrip, inputUserName1);
	//					std::cout << "I am the new trip which was saved in my database!" << std::endl;
	//					
	//					size_t size = 0;
	//					Trip* trips = nullptr;
	//					readTripsFromBinaryFile(trips,size,inputUserName1);
	//					//here is the main part which is not working
	//					for (int i = 0; i < 3; i++) {
	//						std::cout << trips[i].getTimeperiod();
	//					}
	//					delete[] trips;
	//				}
	//				if (choice2 == 2)
	//					searchByDestinationGeneral();
	//				check = true;
	//			}
	//		}
	//	}
	//	if(!check)
	//		std::cout << "There is no such user! Invalid username or password!" << std::endl;
	//}
}