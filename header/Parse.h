#ifndef PARSE_H
#define PARSE_H

#include <iostream> 
#include <string>
#include <vector> 

using namespace std; 

class Parse{
public:
	Parse();
	
	string removeLeadingWhiteSpace(string); 

	string removeTrailingWhiteSpace(string); 

	string ConvertTest(string); 

	vector<string> parse(string);
};

#endif 
