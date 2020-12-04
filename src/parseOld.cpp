#include <iostream>
#include <string>
#include <vector>

using std::cout;
using std::cin;
using std::vector;
using std::string;
using std::endl;

vector<string> parse(string);
//takes in a string from the user
//partitions the string into a vector
//each element of the vector is either a command and its arguments
//or a connector

string removeLeadingWhiteSpace(string);
//helper function for parse
//removes leading whitespace in commands

string removeTrailingWhiteSpace(string);
//helper function for parse
//removes following whitespace in commands

vector<string> parse(string command){
	vector<string> parsedCommand;

	string currCommand = "";

	for(int i=0; i<command.size(); i++){ //traverses command char by char
		//cout << "comma" << command.at(i) << endl;
		//cout << "cur" << currCommand << endl;
		if(i != command.size() - 1){ //if not at last char
			if (command.at(i) == '#'){ //if rest of command is a comment
				if(currCommand.size() != 0 && currCommand!=" "){ //if have stored command
					currCommand = removeLeadingWhiteSpace(currCommand); //remove leading whitespace
	                                currCommand = removeTrailingWhiteSpace(currCommand); //remove trailing whitespace
					parsedCommand.push_back(currCommand); //push back command to vector
					break;
				}
				break;

			} else if (command.at(i) == '"') { //if following is string literal
				currCommand.push_back(command.at(i)); //adds opening quote to currCommand
				i++; //moves to next char to ensure we can go into following while loop
				while(command.at(i) != '"'){ //traverses string for rest of literal, assuming ending '"' exists
					currCommand.push_back(command.at(i)); //if char is not '"'
					i++; 
				}
				//if exited while, char at i == '"'
				currCommand.push_back(command.at(i)); //adds ending quote to currCommand
				if(i == command.size()-1){ //if the ending quote was the last char of command, then readt to push back
					currCommand = removeLeadingWhiteSpace(currCommand); //removes leading whitespace
					currCommand = removeTrailingWhiteSpace(currCommand); //removes trailing whitespace
					parsedCommand.push_back(currCommand); //pushes to command vector
				}
				
			} else if(command.at(i) == ';'){ //if semicolon is detected
				currCommand = removeLeadingWhiteSpace(currCommand); //removes leading whitespace
                               	currCommand = removeTrailingWhiteSpace(currCommand); //removes trailing whitespace
				parsedCommand.push_back(currCommand); //push back currCommand bc we have reached the end of a subCommand
				currCommand = ""; //reset currCommand
				currCommand.push_back(command.at(i)); //sets currCommand to ;
				parsedCommand.push_back(currCommand); //push back the semicolon into the parsedCommand
				currCommand = ""; //resets currCommand
				i++; //"you can assume there will always be a space after the ; and before and after && and ||"
				continue;
				//HERE
			} else if (command.at(i) == '('){ //if curr is either closing or opening paranthesis
				currCommand = "";
				currCommand.push_back(command.at(i));
				parsedCommand.push_back(currCommand);
				currCommand = "";
//				cout << parsedCommand.at(0);
			} else if(command.at(i) == ')'){
				 //cout << "here" << endl;
				if(currCommand.size() != 0){
                                   //     cout << "here1" << endl;
                                        currCommand = removeLeadingWhiteSpace(currCommand);
                                        currCommand = removeTrailingWhiteSpace(currCommand);
				//	cout << "curr" << currCommand << endl;
                                        parsedCommand.push_back(currCommand); //push back currentCommand
					currCommand = "";
                                }
                                //cout << "here2" << endl;
                                currCommand = ")";
                                //currCommand.push_back(command.at(i));
                                parsedCommand.push_back(currCommand);
                                currCommand = "";
			} else if(command.substr(i,2) == "||" || command.substr(i, 2) == "&&"){		
				currCommand = removeLeadingWhiteSpace(currCommand);
                                currCommand = removeTrailingWhiteSpace(currCommand);
				if(currCommand.size() != 0){
                                	parsedCommand.push_back(currCommand); //push back currCommand bc we have reached the end of a subCommand
				}
                                currCommand = ""; //reset currCommand
                                currCommand.push_back(command.at(i)); //push back connector
				currCommand.push_back(command.at(i+1)); //twice bc && and || consist of two chars
                                parsedCommand.push_back(currCommand); //push back the connector into the parsedCommand
                                currCommand = "";
                                i+=2; //"you can assume there will always be a space after the ; and before and after && and ||"
                                continue;

			} else { //if not at last char and curr char is not a connector
				currCommand.push_back(command.at(i)); //push back to currCommand
			}
		} else { //if last char
			if(command.at(i) == ';' || command.at(i) == ')'){ //if the last char is a semicolon
				currCommand = removeLeadingWhiteSpace(currCommand);
                                currCommand = removeTrailingWhiteSpace(currCommand);
				parsedCommand.push_back(currCommand); //push back to parsedCommand currCommand
				if(command.at(i) == ')'){
					currCommand = ")";
					parsedCommand.push_back(currCommand);
					currCommand = "";
				}
				//no need to pass ";" into vector bc at the end, will have already executed rest of commands and ; will not have influence
				continue;
			} else { //if last char is not semicolon
				currCommand.push_back(command.at(i)); //then pushback current char to currCommand to complete currCommand
				currCommand = removeLeadingWhiteSpace(currCommand);
                                currCommand = removeTrailingWhiteSpace(currCommand);
				parsedCommand.push_back(currCommand); //push back currCommand to parsedCommand
			}
		}

		//for(int i=0; i<parsedCommand.size(); i++){
		//	cout << "\"" <<  parsedCommand.at(i) << "\"" << " ";
		//}
		//cout << endl;
	}

	return parsedCommand;
} //end parse function

string removeLeadingWhiteSpace(string command){
	if(command.size() == 0 || command.at(0) != ' '){
		return command;
	}
	return removeLeadingWhiteSpace(command.substr(1));

} //end removeWhiteSpace

string removeTrailingWhiteSpace(string command){
	if(command.size() == 0 || command.at(command.size()-1) != ' '){
			return command;
	} 

	return removeTrailingWhiteSpace(command.substr(0, command.size()-1));

} //end removeTrailingWhiteSpace

/*int main(){
	string command = "";
	cout << "$ "; //prompt user
	getline(cin, command);

//	while(command != "exit"){

		cin.clear();	
//
		//string command = "                           ls -a        ;             echo \"hello && mkdir test #\" #||         echo world; git status";
		vector<string> parsedCommand = parse(command);

	//	cout << "returned" << endl;

		cout << "printing contents of parsed vector" << endl;
		for(int i=0; i<parsedCommand.size(); i++){
			cout << "\"" << parsedCommand.at(i) << "\"" << endl;
		}

//		cout << "$ "; 
//		getline(cin, command);

//	}
//
//	return 0;

} *///end main
