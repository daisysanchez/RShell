#ifndef COMMAND_H
#define COMMAND_H

#include "Node.h"

#include <iostream> 
#include <vector>
//#include <string>

using std::vector;
using std::string;

class Command {
	private:
		string str;
		vector<string> CMD; 
	public:
		char *args[];
		Command();
		Command(string);
		~Command(){};
		virtual bool execute();
};

#endif
