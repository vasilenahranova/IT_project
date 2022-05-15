#pragma once
#include<iostream>
#include"String.h"

class Trip {
private:
	String Destination;
	String Timeperiod;
	int Grade;
	String Comment;
	String Photo;
public:
	//constructors
	Trip() : Destination("empty"), Timeperiod("empty"), Grade(0), Comment("empty"), Photo("empty") {
	};
	Trip(String destination, String timeperiod, int grade, String comment, String photo) :Destination(destination), Timeperiod(timeperiod), Grade(grade), Comment(comment),Photo(photo) {}
	Trip(const Trip& other) : Destination(other.Destination), Timeperiod(other.Timeperiod), Grade(other.Grade), Comment(other.Comment), Photo(other.Photo) {}
	Trip& operator=(const Trip& other) {
		if (this != &other) {
			Destination = other.Destination;
			Timeperiod = other.Timeperiod;
			Grade = other.Grade;
			Comment = other.Comment;
			Photo = other.Photo;
		}
		return *this;
	}

	//getters
	String getDestination() { return Destination; }
	String getTimeperiod() { return Timeperiod; }
	int getGrade() { return Grade; }
	String getComment() { return Comment; }
	String getPhotos() { return Photo; }



	//save and read from Files
	void saveTripsToBinaryFile(const char*) const;
	void readTripsFromBinaryFile(Trip&,int,const char*);

	friend std::ostream& operator<<(std::ostream& os, const Trip& obj1);
};