#pragma once
#include<iostream>
#include<cstring>

class Trip {
private:
	std::string Destination;
	std::string Timeperiod;
	int Grade;
	std::string Comment;
	//how to insert field for image/array of images
public:
	Trip() : Destination("empty"),Timeperiod("empty"), Grade(0), Comment("Empty") {
		//std::cout<<"I am the default constructor!"<<std::endl;
	};
	Trip(std::string destination, std::string timeperiod, int grade, std::string comment) :Destination(destination),Timeperiod(timeperiod), Grade(grade), Comment(comment) {
		//std::cout<<"I am the constructor!"<<std::endl;
	}
	Trip(const Trip& other) : Destination(other.Destination), Timeperiod(other.Timeperiod), Grade(other.Grade), Comment(other.Comment) {
		//std::cout<<"I am the copy constructor!"<<std::endl;
	}
	Trip& operator=(const Trip& other) {
		//std::cout<<"I am the operator =!"<<std::endl;
		if (this != &other) {
			Destination = other.Destination;
			Timeperiod = other.Timeperiod;
			Grade = other.Grade;
			Comment = other.Comment;
		}
		return *this;
	}
	std::string getDestination() { return Destination; }
	std::string getTimeperiod() {return Timeperiod;}
	int getGrade() { return Grade; }
	std::string getComment() { return Comment; }

};
class User {
private:
	std::string UserName;
	std::string Password;
	std::string Email;
	//Trip* TripList;
public:
	User() :UserName("empty"), Password("empty"), Email("empty") {
		// std::cout<<"Hi! I am the default constructor!"<<std::endl;
	};
	User(std::string username, std::string email, std::string password) : UserName(username), Password(password), Email(email) {
		//std::cout<<"Hi! I am the parametric constructor!"<<std::endl;
	};
	User(const User& other) :UserName(other.UserName), Password(other.Password), Email(other.Email) {
		//std::cout<<"Hi! I am the copy constructor!"<<std::endl;
	};
	User& operator=(const User& other) {
		// std::cout<<"Hi!I am the operator =!"<<std::endl;
		if (this != &other) {
			setUserName(other.UserName);
			setPassword(other.Password);
			setEmail(other.Email);
		}
		return *this;
	}

	//setters
	void setUserName(std::string username) {
		this->UserName = username;
	}
	void setPassword(std::string password) {
		this->Password = password;
	}
	void setEmail(std::string email) {
		this->Email = email;
	}
	//getters
	std::string getUserName() { return UserName; }
	std::string getEmail() { return Email; }
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
