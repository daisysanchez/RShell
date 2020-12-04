#ifndef COMPOSITE_H
#define COMPOSITE_H

#include "Command.h"
#include "Connectors.h"

#include <iostream> 
#include <vector>
#include <string> 

using namespace std;  

class Composite {
 public:
	Composite(); 
	vector<string>Parsing(string);
	//int main();  
};

#endif 
