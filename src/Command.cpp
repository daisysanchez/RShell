#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <cstring>

#include <iostream>
#include "../header/Command.h" 

using std::cout;
using std::endl;

Command::Command(){
	this->str = "";
//	this->CMD.push_back(NULL);
} 

Command::Command(string command){
	this->str = command;
	
	//command is a string from vector
	//this iterates through each subCommand and seperates their arguments
	
	for(int i = 0; i<command.size(); i++){ //traverses command string
		string temp = ""; 
		for(int j=i; j<command.size(); j++){ //traverses command string, going ahead of i

			if(command.at(j) == ' '){ //if char at j is space
				CMD.push_back(temp); //push to cmd what is already in string
				i =j; //update i to j
				break; 
			} else if (command.at(j) == '"') { //if char at j is a quote, extract rest of string as string literal
				for(int k = j+1; k<command.size(); k++){
					if(command.at(k) == '"'){ //if closing quote found
						CMD.push_back(temp); //push back string literal
						temp = ""; //reset temp
						j = k; //make sure j is caught up to not overlap
					} else { //if char is not closing quote
						temp.push_back(command.at(k)); //then continue trating as string literal
					} 
				} //end string literal traversal
			} else { //if char is not space
				if(j != command.size() -1){ //and is not last char
					temp.push_back(command.at(j)); //add it to temp string
				} else { //if it is the last char
					i = j; //set i to j
					temp.push_back(command.at(j)); //add the char to temp string
					CMD.push_back(temp); //add temp to cmd
					break; //break
				} //end ifelse for char pushback
			} //end if else for if char not space
		} //end inner for loop 
	} //end  command traversal
} //end Command constructor


//converts the vector CMD into char**
//CMD is a vector of strings containing the executable and the arguments of a command
//pupose is to convert string into acceptable input for execvp
char** toCharPntr(vector<string> CMD){ 
	char** argv = new char*[CMD.size()+1]; 	//instantiate char** of one size greater to allow space for null
	
	for(int i=0; i<CMD.size(); i++){ //traverse the CMD
		//cout << CMD.at(i);
		argv[i] = (char*)CMD.at(i).c_str(); //cast string to c_string then to char*
	}
	
	argv[CMD.size()] = NULL; //append NULL bc execvp needs to knnow whhen it's reached the end with null

	return argv; //return the converted command
} //end toCHarPnt
	


//used execvp and fork to execute commands
bool Command::execute(){
    	pid_t pid = fork();
	int status = 1;

	//vector<string> cmds;
	//cmds.push_back("echo");
	//cmds.push_back("\"hello\"");

	//string ls = "ls";
	//char** argv = new char*[2];
	//argv[0] = (char*)ls.c_str();
	//argv[1] = NULL;

	//execvp(argv[0], argv);
	
	char** argv = toCharPntr(this->CMD);
	if(pid < 0){
		perror("FORKING FAILED");
		exit(EXIT_FAILURE);
	}

	if(pid == 0){ //in child
		if(execvp(argv[0], argv) < 0){//int execvp(const char*file, char *const argv[])
			perror("FAILED TO EXECUTE");
			exit(EXIT_FAILURE);
		}
	}

	if(pid > 0){
		if(waitpid(pid, &status, WCONTINUED) < 0){
			perror("WAIT FAILED");
			exit(EXIT_FAILURE);
		}

		if(status == 0)
			return true;
	

		//if in parent
	//	int status = wait(0);

	//	if(status == -1)
	//			perror("FAILED WAIT");

	}

	return false;

} //end execute()

//int main(){
//	vector<string> cmds;
///
//	cmds.push_back("ls");
//	cmds.push_back("-a");
//
//	Command* ls = new Command("ls -a");
//
//	ls->execute();
//
//	return 0;
//}
