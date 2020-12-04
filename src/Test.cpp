#include "../header/Test.h"
#include <sys/stat.h>

#include <vector>
#include <iostream>

using std::cout;
using std::endl;
using std::vector;

Test::Test(){
	command = "";
	flag = "";
	path = "";
}

Test::Test(string command){
	this->command = command;
	extract();

////	cout << "command: " << command << endl;
//	cout << "flag: " << flag << endl;
//	cout << "path: " << path << endl;
}

bool Test::execute(){
	struct stat statbuf;
	bool status;

	const char* dir = path.c_str();
	
	if(flag.size() == 0){
		setFlag("-e");
	}

	if(stat(dir, &statbuf) == 0){
		if(flag == "-e"){
			status = (S_ISREG(statbuf.st_mode) + S_ISDIR(statbuf.st_mode)) != 0 ;
		} else if(flag == "-d"){
			status = S_ISDIR(statbuf.st_mode) != 0;
		} else if(flag == "-f"){
			status = (S_ISREG(statbuf.st_mode) != 0);
		} else {
			exit(EXIT_FAILURE);
		}
	} else {
		//exit(1);
		status = false;
	}
	if(status) cout << "(True)" << endl;
	else cout << "(False)" << endl;

	return status;
}

string Test::getFlag(){
	return flag;
}

string Test::getPath(){
	return path;
}

void Test::setFlag(string flag){
	this->flag = flag;
	
}

void Test::extract(){
	vector<string> temp;
	string str;
//	cout << command.size();
	for(int i=0; i<command.size(); i++){
		//cout << "com: " << command << endl;
		if(command.at(i) != ' '){
			str.push_back(command.at(i));
		} else {
			if(str.size() > 0){
				temp.push_back(str);
				str = "";
			}
		}

		if(i == command.size()-1){
			temp.push_back(str);
		}
	}

	///for(int i=0; i<temp.size(); i++){
	//	cout << temp.at(i) << endl;
	//}

	flag = temp.at(1);
	path = temp.at(2);
}
