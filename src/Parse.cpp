#include "../header/Parse.h"

#include <iostream>

using std::cout;
using std::cin;


Parse::Parse(){
}

string Parse::removeLeadingWhiteSpace(string command){
	if(command.at(0) != ' '){
		return command; 
	}
		return removeLeadingWhiteSpace(command.substr(1));
}
//helper function for parse
//removes leading whitespace in commands

string Parse::removeTrailingWhiteSpace(string command){
	if(command.at(command.size() - 1) != ' '){
		return command; 
	}
		return  removeTrailingWhiteSpace(command.substr(0, command.size()-1)); 
}
//helper function for parse
//removes following whitespace in commands

string Parse::ConvertTest(string command){
	string tag = "";
	string path = "";
	string newcommand = "";

	for(int i = 0; i < command.size() - 3; ++i){
		if(command.find(' ') != string::npos){
			tag = command.substr(1,2);
			if(command.at(i) == ' '){
				path = command.substr(i + 1, command.size() - 5);
			}
		}
	}

	for(int i = 0; i < command.size() - 2; ++i){
		if(command.find(' ') == string::npos){
			tag = "-e";
			path.push_back(command.at(i + 1));
		}
	}

	newcommand = "test " + tag + " " + path;
	return newcommand; 

} //end of ConvertTest
//helper function 
//converts bracket format into other format

vector<string> Parse::parse(string command){
	vector<string> parsedCommand;

	string currCommand = "";

	for(int i=0; i<command.size(); i++){ //traverses command char by char
		if(i != command.size() - 1){ //if not at last char
			if (command.at(i) == '#'){ //if rest of command is a comment
				if(currCommand.size() != 0){ //if have stored command
					parsedCommand.push_back(currCommand); //push back command to vector
				}
				break;

			} else if (command.at(i) == '"') { //if following is string literal
				currCommand.push_back(command.at(i)); //adds opening quote to currCommand
				i++; //moves to next char to ensure we can go into following while loop
				while(command.at(i) != '"'){ //traverses string for rest of literal, assuming ending '"' exists
					currCommand.push_back(command.at(i)); //if char is not '"'
					i++; 
				}
				currCommand.push_back(command.at(i)); //adds ending quote to currCommand
				if(i == command.size()-1){ //if the ending quote was the last char of command, then readt to push back
					parsedCommand.push_back(currCommand); //pushes to command vector
				}
				
			} else if(command.at(i) == ';' || (command.at(i) == '>' && command.at(i+1) != '>') || command.at(i) == '<' || (command.at(i) == '|' && command.at(i+1) != '|')){ //if one-char connector 
				parsedCommand.push_back(currCommand); //push back currCommand bc we have reached the end of a subCommand
				currCommand = ""; //reset currCommand
				currCommand.push_back(command.at(i)); //sets currCommand to ;
				parsedCommand.push_back(currCommand); //push back the semicolon into the parsedCommand
				currCommand = ""; //resets currCommand
				i++; //"you can assume there will always be a space after the ; and before and after && and ||"
				continue;
			} else if(command.at(i) == '('){ //if semicolon is detected
				currCommand = ""; //reset currCommand
				currCommand.push_back(command.at(i)); //sets currCommand to ;
				parsedCommand.push_back(currCommand); //push back the semicolon into the parsedCommand
				currCommand = ""; //resets currCommand
				continue;
			} else if(command.at(i+1) == ')'){ //if semicolon is detected
				currCommand.push_back(command.at(i));
				parsedCommand.push_back(currCommand); //push back currCommand bc we have reached the end of a subCommand
				currCommand = ""; //reset currCommand
				currCommand.push_back(command.at(i+1)); //sets currCommand to ;
				currCommand = ""; //resets currCommand
				continue;
			} else if(command.substr(i,2) == "||" || command.substr(i, 2) == "&&" || command.substr(i,2) == ">>"){	
                                parsedCommand.push_back(currCommand); //push back currCommand bc we have reached the end of a subCommand
                                currCommand = ""; //reset currCommand
                                currCommand.push_back(command.at(i)); //push back connector
				currCommand.push_back(command.at(i+1)); //twice bc && and || consist of two chars
                                parsedCommand.push_back(currCommand); //push back the connector into the parsedCommand
                                currCommand = "";
                                i+=2; //"you can assume there will always be a space after the ; and before and after && and ||"

			} else { //if not at last char and curr char is not a connector
				currCommand.push_back(command.at(i)); //push back to currCommand
			}
		} else { //if last char
			if(command.at(i) == ';'){ //if the last char is a semicolon
				parsedCommand.push_back(currCommand); //push back to parsedCommand currCommand
				continue;
			} else { //if last char is not semicolon
				currCommand.push_back(command.at(i)); //then pushback current char to currCommand to complete currCommand
				parsedCommand.push_back(currCommand); //push back currCommand to parsedCommand
			}
		}
	}

	for(int i=0; i<parsedCommand.size(); i++){
		parsedCommand.at(i) = removeLeadingWhiteSpace(parsedCommand.at(i));
		parsedCommand.at(i) = removeTrailingWhiteSpace(parsedCommand.at(i));
	}

	vector<int> index;
	vector<string> pcmds;  
	for(int j = 0; j < parsedCommand.size(); j++) {
		if(parsedCommand.at(j).substr(0,1) == "["){
			index.push_back(j);
		}
	}

	for(int k = 0; k < index.size(); k++){
		parsedCommand.at(index.at(k)) = ConvertTest(parsedCommand.at(index.at(k)));
	}

	return parsedCommand;
} //end parse function

/*int main(){
	cout << "$ ";

	string command = "";

	getline(cin, command);

	cin.clear();

	Parse* p = new Parse();

	vector<string> parsedCommand = p->parse(command);

	cout << "printing contents of parsed vector" << endl;
        for(int i=0; i<parsedCommand.size(); i++){
	        cout << "\"" << parsedCommand.at(i) << "\"" << endl;
        }


}*/
