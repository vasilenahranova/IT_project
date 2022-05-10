#include "User.h"

void ListOfUsers::Resize(){
	int length = 2 * Capacity;
	User* List1=new User[length];
	for (int i = 0; i < length; i++) {
		List1[i] = List[i];
	}
	delete[]List;
	List = List1;
	Capacity *= 2;
}

void ListOfUsers::AddUser(const User& newUser){
	if (Current > Capacity)
		Resize();
	List[Current] = newUser;
	Current++;
}


