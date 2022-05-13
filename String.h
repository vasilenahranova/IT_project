#pragma once
#include<iostream>
#include<stdexcept>
class String {
private:
	size_t Size;
	char* myString;
public:
	//constructors
	String() :Size(0), myString(nullptr) {};
	String(const char* myString0) {
		Size = strlen(myString0);
		myString = new char[Size + 1];
		strcpy_s(myString, Size + 1, myString0);
	}
	String(const String& other) {
		Size = other.Size;
		myString = new char[Size + 1];
		for (size_t i = 0; i < Size + 1; i++) {
			myString[i] = other.myString[i];
		}
	}
	String& operator=(const String& other) {
		if (this != &other) {
			delete[] myString;

			Size = other.Size;
			myString = new char[Size + 1];
			strcpy_s(myString, Size + 1, other.myString);
		}
		return *this;
	}
	~String() { delete[] myString; }

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

	char* getmyString() { return myString; }

	//operation functionalities
	//check what is c_str();
	/*char c_str() const;
	char* substr() const;*/
	friend std::ostream& operator<<(std::ostream& os, const String& obj1);
	friend std::istream& operator>>(std::istream& is, String& obj1);
	friend String operator+(const String& obj1, const String& obj2);

};
