#include<iostream>
#include<string>
#include"String.h"
#include<stdexcept>


int String::size() const
{
	return Size;
}

int String::length() const
{
	return Size;
}

void String::resize(size_t capacity) {
	char* helpString = new char[capacity];
	strcpy_s(helpString, Size, myString);

	delete[] myString;
	myString = helpString;
	Size = capacity;
}

char String::at(unsigned int i) const
{
	if (i >= size())
		throw std::exception();
	return myString[i];
}

char String::back() const
{
	return myString[Size - 1];
}

char String::front() const
{
	return myString[0];
}

String& String::operator+=(const char* string2) {
	int length = strlen(string2);
	resize(Size + length + 1);
	for (unsigned int i = 0; i < length; i++) {
		myString[i + size()] = string2[i];
	}
	Size += length;
	myString[size() + length] = '\0';
	return *this;
}

String& String::operator+=(const char c)
{
	this->push_back(c);
	return *this;
}

void String::push_back(char ch)
{
	resize(Size * 2);
	myString[Size++] = ch;
}

void String::swap(String& obj2) {
}

void String::pop_back() {
	resize(Size--);
}

std::ostream& operator<<(std::ostream& os, const String& obj1)
{
	std::cout << obj1.myString;
	return os;
}

std::istream& operator>>(std::istream& is, String& obj1)
{
	char* temp = new char[100];
	std::cin.getline(temp, 100);
	obj1 = String{ temp };
	return is;
}

String operator+(const String& obj1, const String& obj2)
{
	int length = strlen(obj1.myString) + strlen(obj2.myString);
	char* helpArray = new char[length + 1];
	//copy the strings to the helpArray
	strcpy_s(helpArray, strlen(obj1.myString) + 1, obj1.myString);
	strcat_s(helpArray, strlen(obj1.myString) + strlen(obj2.myString) + 1, obj2.myString);
	helpArray[length] = '\0';

	String string = helpArray;
	delete[] helpArray;
	return string;
}