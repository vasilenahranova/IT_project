#include<iostream>
#include<cstring>
#include"User.h"
#include<fstream>

int main() {
	User vassilena("vhranova", "vasihrannova@abv.bg", "vassilen3");
	//std::cout << vassilena.getUserName() << " " << vassilena.getEmail() << " " << vassilena.getPassword() << std::endl;
	
	User* Array=new User[20];
	for (int i = 0; i < 20; i++) {
		Array[i] = vassilena;
	}
	ListOfUsers List1(Array, 0, 20);
	
	int choice;
	std::cout << "Make your choice:" << std::endl;
	std::cout << "Press 1 for REGISTER" << std::endl;
	std::cout << "Press 2 for LOGIN" << std::endl;
	std::cin >> choice;
	std::string username,password,email;
	std::ofstream userlist("userlist.txt", std::ios::app);
		if (choice == 1) {
			std::cout << "Enter username" << std::endl;
			std::cin >> username;
			std::cout << "Enter password" << std::endl;
			std::cin >> password;
			std::cout << "Enter email" << std::endl;
			std::cin >> email;
			User newUser(username, password, email);
			List1.AddUser(newUser);
			std::cout << "ME";
			/*if (userlist.is_open()) {
				userlist << newUser.getUserName() << std::endl;
				userlist << newUser.getEmail() << std::endl;
				userlist << newUser.getPassword() << std::endl;
			}
			userlist.close();*/
		}
	if(choice==2){
		//enter();
		std::cout << "Still not ready";
	}
	return 0;
	
}