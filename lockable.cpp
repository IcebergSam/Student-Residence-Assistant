#include"lockable.h"
#include<string>
using namespace std;

Lockable::Lockable(){ 
	locked = false; 
	password = "default";
}

bool Lockable::isLocked(){ return locked; }


bool Lockable::authenticate(string pswd){
	if (pswd == password) {
		return true; 
	}
	return false;
}

bool Lockable::unlock(std::string pswd){ 
	if (authenticate(pswd)) { 
		locked = false; 
	}
	return pswd == password;
}

bool Lockable::lock(std::string pswd){
	locked = true;
	password = pswd;
	return locked;
}

bool Lockable::lock(){
    locked = true;
    return true;
}
