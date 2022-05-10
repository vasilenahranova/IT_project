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
class String {
private:
	unsigned int Size, Capacity;
	char* myString;
public:
	//constructors
	String() :myString(nullptr), Size(0), Capacity(strlen(myString)) {};
	String(const char* myString0) {
		Size = strlen(myString0);
		Capacity = Size;
		char* string = new char[Size + 1];
		strcpy_s(this->myString, Size + 1, myString0);
	}
	String(const String& other) {
		Size = strlen(other.myString);
		Capacity = Size;
		char* string = new char[Size + 1];
		strcpy_s(this->myString, Size + 1, other.myString);
	}
	String& operator=(const String& other) {
		if (this != &other) {
			delete myString;

			Size = other.size();
			Capacity = Size;
			myString = new char[Size];
			strcpy_s(myString, Size + 1, other.myString);
		}
		return *this;
	}
	~String() { delete myString; }

	//size functionality
	int size() const;
	int capacity() const;
	int length() const;
	void resize(unsigned int);
	char at(unsigned int)const;
	char back() const;
	char front() const;

	//modification functionality
	String& operator+=(const char*);
	String& operator+=(const char);
	void push_back(char);
	//void insert();
	//void erase();
	//void replase();
	void swap(String& obj2);
	void pop_back();

	//operation functionalities
	//check what is c_str();
	/*char c_str() const;
	char* substr() const;*/
	friend std::ostream& operator<<(std::ostream& os, const String& obj1);
	friend std::istream& operator>>(std::istream& is, const String& obj1);
	friend String operator+(const String& obj1, const String& obj2);

};