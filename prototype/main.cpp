#include <iostream> 
#include <string> 
#include <vector> 
#include <sstream> 

using namespace std;

int main(){
 string command = "";
 string commandparts;
 vector<string> parse; 

 command =  "ls -a ; echo hello && mkdir test || echo world ;";
	
 stringstream ssin(command);
 
 while(getline(ssin, commandparts, ' ')){
    parse.push_back(commandparts); 
 }

 for(int i = 0; i < parse.size(); ++i){
    cout << parse.at(i) << endl;
 }

 return 0; 
} 
