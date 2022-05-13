#pragma once
#include<iostream>
#include"String.h"

class User {
private:
	String UserName;
	String Password;
	String Email;
public:
	User() :UserName("empty"), Password("empty"), Email("empty") {
		// std::cout<<"Hi! I am the default constructor!"<<std::endl;
	};
	User(String username, String email, String password) : UserName(username), Password(password), Email(email) {
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
	void setUserName(String username) {
		this->UserName = username;
	}
	void setPassword(String password) {
		this->Password = password;
	}
	void setEmail(String email) {
		this->Email = email;
	}
	//getters
	String getUserName() { return UserName; }
	String getEmail() { return Email; }
	String getPassword() { return Password; }

	friend std::ostream& operator<<(std::ostream& os, const User& obj1);
};