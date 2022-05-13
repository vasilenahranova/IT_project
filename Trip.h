#pragma once
#include<iostream>
#include"String.h"

class Trip {
private:
	String Destination;
	String Timeperiod;
	int Grade;
	String Comment;
	//how to insert field for image/array of images
public:
	Trip() : Destination("empty"), Timeperiod("empty"), Grade(0), Comment("empty") {
		//std::cout<<"I am the default constructor!"<<std::endl;
	};
	Trip(String destination, String timeperiod, int grade, String comment) :Destination(destination), Timeperiod(timeperiod), Grade(grade), Comment(comment) {
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
	String getDestination() { return Destination; }
	String getTimeperiod() { return Timeperiod; }
	int getGrade() { return Grade; }
	String getComment() { return Comment; }
	friend std::ostream& operator<<(std::ostream& os, const Trip& obj1);
};
