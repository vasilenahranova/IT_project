#include<iostream>
#include"User.h"
#include"String.h"
#include"Trip.h"
#include<fstream>

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
bool checkUserName(String username) {
	int length = username.length();
	for (int i = 0; i < length; i++) {
		if ((username.at(i) < '0' || (username.at(i) > '9') && username.at(i) < 'A') || (username.at(i) > 'Z' && username.at(i) < 'a') || username.at(i) > 'z')
		{
			std::cout << "Invalid username.It must include ONLY Latin letters and numbers!Try again!" << std::endl;
			return false;
		}
	}
	return true;
}
bool checkTimePeriod(String timeperiod, const int day1, const int month1, const int year1, const int day2, const int month2, const int year2) {
	//check if the string is in the right form2
	if (timeperiod.size() != 21) return false;
	for (int i = 0; i < timeperiod.size(); i++) {
		if ((timeperiod.at(i) < '0' || timeperiod.at(i) > '9') && timeperiod.at(i) != '.' && timeperiod.at(i) != '-')
			return false;
	}
	//check for the valid dates 
	if (!checkValidDates(day1, month1, year1, day2, month2, year2)) return false;
	//check for the additional condition - the second needs to be bigger than the first
	if (!checkAdditionalCondition(day1, month1, year1, day2, month2, year2)) return false;
	return true;

}
bool checkGrade(const int grade) {
	return (grade > 0 && grade < 7);
}
//input functions
void inputUser(String& username, String& password, String& email) {
	std::cout << "Enter username(contains only letters and digits):"; std::cin >> username; 
	while(!checkUserName(username)) {
		std::cin >> username;
	};
	std::cout << "Enter password:"; std::cin >> password;
	std::cout << "Enter email:"; std::cin >> email;
}
void inputTrip(String& destination,String& timeperiod, unsigned int& grade,String& comment,String&photo) {
	std::cout << "Enter name of your Destination:"; std::cin>>destination;
	std::cout << "Enter the Time period(Format:DD.MM.YYYY-DD.MM.YYYY):"; std::cin>>timeperiod;
	int day1, month1, year1, day2, month2, year2;
	transformTimePeriod(timeperiod, day1, month1, year1, day2, month2, year2);
	while (!checkTimePeriod(timeperiod, day1, month1, year1, day2, month2, year2)) {
		std::cout << "Invalid input for timeperiod!It must be in the format DD.MM.YYYY-DD.MM.YYYY and the second date must be larger than the first!" << std::endl;
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
	std::cin.ignore();
	std::cout << "Enter your PhotoName:"; std::cin >> photo;

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

//searchByDestination and average grade function
void searchByDestinationGeneral() {
	//enter destination for search
	String destination1;
	std::cout << "Enter destination: "; std::cin >> destination1;

	double srednaOcenka = 0;
	int counter = 0;
	//extracts users from the file and put them into User array
	std::ifstream UsersDataBase("UsersDataBase", std::ios::binary);
	UsersDataBase.seekg(0, std::ios::end);
	size_t size = UsersDataBase.tellg() / sizeof(User);
	User* currentDataBase = new User[size];
	for (int i = 0; i < size; i++) {
		User user;
		user.readUserFromBinaryFile(user, i);
		currentDataBase[i] = user;
	}
	for (int i = 0; i < size; i++) {
		const char* username1 = currentDataBase[i].getUserName().getmyString();
		std::ifstream personalFile(username1, std::ios::binary);
		personalFile.seekg(0, std::ios::end);
		size_t size1 = UsersDataBase.tellg() / sizeof(User);
		Trip* currentTripsDataBase = new Trip[size1];
		for (int k = 0; k < size1; k++) {
			Trip trip;
			trip.readTripsFromBinaryFile(trip, i,username1);
			currentTripsDataBase[i] = trip;
		}

		for (int j = 0; j < size1; j++) {
			if (currentTripsDataBase[i].getDestination() == destination1) {
				std::cout<<currentTripsDataBase[i];
				srednaOcenka+= currentTripsDataBase[i].getGrade();
				counter++;
			}
		}
		delete[]currentDataBase;
		delete[]currentTripsDataBase;
	}
	if (counter != 0) {
		srednaOcenka /= counter;
		std::cout << "The average grade of this destination is: " << srednaOcenka << std::endl;
	}
	else
		std::cout << "There is no such destination, visited by our Users!"<<std::endl;
}
int main() {
	int choice=0;
	firstChoice(choice);

	String username, password, email;
	if (choice == 1) {
		//save the new user data into the whole DataBase
		std::cin.ignore();
		inputUser(username, password, email);
		User user(username, password, email);
		user.saveUserToBinaryFile();
		
		//choose next activity
		int choice2=0;
		secondChoice(choice2);
		std::cin.ignore();
		if (choice2 == 1) {
			String destination, timeperiod, comment,photo;
			unsigned int grade;
			inputTrip(destination, timeperiod, grade, comment,photo);
			Trip newtrip(destination, timeperiod, grade, comment,photo);
			//transform into username.myString char[]
			const char* username1 = username.getmyString();
			newtrip.saveTripsToBinaryFile(username1);
			delete[] username1;
		}
		if (choice2 == 2)
			searchByDestinationGeneral();
	}
	if (choice == 2) {
		//I need to search through the DateBase and check if such user exists
		String inputUserName, inputPassword;
			std::cout << "Enter Username:"; std::cin >> inputUserName;
			std::cout << "Enter Password:"; std::cin >> inputPassword;
		//read Users from the file and put them in an User array
		std::ifstream UsersDataBase("UsersDataBase", std::ios::binary);
		UsersDataBase.seekg(0, std::ios::end);
		size_t size = UsersDataBase.tellg() / sizeof(User);
		User* currentDataBase = new User[size];
		for (int i = 0; i < size; i++) {
			User user;
			user.readUserFromBinaryFile(user, i);
			currentDataBase[i] = user;
		}
		bool check = false;
		for (int i = 0; i < size; i++) {
			if (currentDataBase[i].getUserName() == inputUserName) {
				std::cout << "Valid username"<<std::endl;
				if (currentDataBase[i].getPassword() == inputPassword) {
					int choice2 = 0;
					secondChoice(choice2);
					std::cin.ignore();
					if (choice2 == 1) {
						String destination, timeperiod, comment,photo;
						unsigned int grade;
						inputTrip(destination, timeperiod, grade, comment,photo);
						Trip newTrip(destination, timeperiod, grade, comment,photo);
						const char *inputUserName1 = inputUserName.getmyString();
						newTrip.saveTripsToBinaryFile(inputUserName1);	
						delete[]inputUserName1;
					}
					if (choice2 == 2)
						searchByDestinationGeneral();
					check = true;
				}
			}
		}
		delete[]currentDataBase;

		if(!check)
			std::cout << "There is no such user! Invalid username or password!" << std::endl;
	}
	return 0;
}