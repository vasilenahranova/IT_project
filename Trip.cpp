#include<iostream>
#include<fstream>
#include"Trip.h"
std::ostream& operator<<(std::ostream& os, const Trip& obj1)
{
	std::cout << obj1.Destination << " " << obj1.Timeperiod << " " << obj1.Grade << " " << obj1.Comment <<" "<<obj1.Photo<< std::endl;
	return os;
}

void Trip::saveTripsToBinaryFile(const char* username) const
{
	//open binary file for writing
	std::ofstream personalFile(username, std::ios::binary | std::ios::app);

	//get the sizes and the lengths of the fields,which we want to put into the file
	size_t lengthD = Destination.size();
	const char* destination = Destination.getmyString();
	size_t lengthT = Timeperiod.size();
	const char* timeperiod = Timeperiod.getmyString();
	size_t lengthC = Comment.size();
	const char* comment= Comment.getmyString();
	size_t lengthP = Photo.size();
	const char* photo = Photo.getmyString();

	//write in the file
	personalFile.write((char*)&lengthD, sizeof(size_t));
	personalFile.write(destination, lengthD);

	personalFile.write((char*)&lengthT, sizeof(size_t));
	personalFile.write(timeperiod, lengthT);

	personalFile.write((char*)&Grade, sizeof(int));
	
	personalFile.write((char*)&lengthC, sizeof(size_t));
	personalFile.write(comment, lengthC);

	personalFile.write((char*)&lengthP, sizeof(size_t));
	personalFile.write(photo, lengthP);

	personalFile.close();
}

void Trip::readTripsFromBinaryFile(Trip& Trip1,int Index,const char* username)
{
	std::ifstream personalFile(username, std::ios::binary);
	//here my idea was to start reading file from Index position in order to get all Trips, instead of just the first one but that does not work
	//personalFile.seekg(Index*sizeof(Trip), std::ios::beg);

	size_t lengthD = 0;
	char* destination = new char[100];
	personalFile.read((char*)&lengthD, sizeof(size_t));
	personalFile.read(destination, lengthD);
	destination[lengthD] = '\0';

	size_t lengthT = 0;
	char* timeperiod = new char[100];
	personalFile.read((char*)&lengthT, sizeof(size_t));
	personalFile.read(timeperiod, lengthT);
	timeperiod[lengthT] = '\0';

	int grade;
	personalFile.read((char*)&grade, sizeof(int));

	size_t lengthC = 0;
	char* comment = new char[100];
	personalFile.read((char*)&lengthC, sizeof(size_t));
	personalFile.read(comment, lengthC);
	comment[lengthC] = '\0';

	size_t lengthP = 0;
	char* photo = new char[100];
	personalFile.read((char*)&lengthP, sizeof(size_t));
	personalFile.read(photo, lengthP);
	photo[lengthP] = '\0';

	personalFile.close();
	Trip1 = Trip(destination,timeperiod,grade,comment,photo);
}

