#pragma once
#include<iostream>
#include<cstring>

class Trip {
private:
	std::string Destination;
	char Timeperiod[10];
	int Grade;
	std::string Comment;
	//how to insert field for image/array of images
public:
	//do I need a default constructor
	//Trip() :Destination(0), Grade(2), Comment(0) {
		//strcpy_s(Timeperiod, 10, 0);
	//};
	Trip(std::string destination, char timeperiod[], int grade, std::string comment):Destination(destination),Grade(grade),Comment(comment) {
		strcpy_s(Timeperiod, 10, timeperiod);
	}
	Trip(const Trip& other): Destination(other.Destination), Grade(other.Grade), Comment(other.Comment) {
		strcpy_s(Timeperiod, 10, other.Timeperiod);
	}
	Trip& operator=(const Trip& other) {
		if (this != &other) {
			Destination = other.Destination;
			Grade = other.Grade;
			Comment = other.Comment;
			strcpy_s(Timeperiod, 10, other.Timeperiod);
		}
		return *this;
	}
};
class User {
private:
	std::string UserName;
	std::string Email;
	std::string Password;
	//Trip* TripList;
public:
	User():UserName("empty"), Email("empty"), Password("empty") {};
	User(std::string userName, std::string email, std::string password) : UserName(userName), Email(email), Password(password) {};
	User(const User& other):UserName(other.UserName), Email(other.Email), Password(other.Password) {};

	//getters
	std::string getUserName() {return UserName;}
	std::string getEmail() { return Email;}
	std::string getPassword() { return Password; }
};
class ListOfUsers {
private:
	int Current;
	int Capacity;
	User* List;
public:
	//ListOfUsers();
	ListOfUsers(User* list,int current, int capacity): Current(current), Capacity(capacity){
		for (int i = 0; i < current; i++) {
			List[i] = list[i];
		}
	};
	//functions
	void Resize();
	void AddUser(const User& newUser);

};
