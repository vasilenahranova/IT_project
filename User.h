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
	};
	User(String username, String email, String password) : UserName(username), Password(password), Email(email) {
	};
	User(const User& other) :UserName(other.UserName), Password(other.Password), Email(other.Email) {
	};
	User& operator=(const User& other) {
		if (this != &other) {
			setUserName(other.UserName);
			setPassword(other.Password);
			setEmail(other.Email);
		}
		return *this;
	}
	
	//save and read users
	void saveUserToBinaryFile() const;
	void readUserFromBinaryFile(User& User,int Index);
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