#ifndef TEST_H_
#define TEST_H_

//#include "Command.h"

#include <string>

using std::string;

class Test{
	private:
		string command;
		string flag;
		string path;
	public:
		Test();
		Test(string);
		~Test(){};

		string getFlag();
		string getPath();

		void setFlag(string);

		void extract();
		bool execute();
};

#endif
