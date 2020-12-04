#ifndef __TEST1_CPP__
#define __TEST1_CPP__

#include "../header/Command.h"
#include "../header/Parse.h"

#include "gtest/gtest.h"
#include <vector>
#include <string> 

using namespace std; 

TEST(ParseTest1, oneCmd) {
	Parse* p = new Parse(); 
	vector<string> pcmds; 
	string command = "ls -a;"; 
	
	pcmds = p->parse(command); 
	EXPECT_EQ("ls -a", pcmds.at(0));
};

TEST(ParseTest2, quoteCmd) {
	Parse* p = new Parse(); 
	vector<string> pcmds; 
	string command = "ls -a; echo \"hello\""; 

	pcmds = p->parse(command); 

	EXPECT_EQ("ls -a", pcmds.at(0)); 
	EXPECT_EQ(";", pcmds.at(1));
	EXPECT_EQ("echo \"hello\"", pcmds.at(2)); 
};

TEST(ParseTest3, multCmd) {
	Parse* p = new Parse(); 
	vector<string> pcmds; 
	string command = "ls -a; echo hello && mkdir test || echo world; git status"; 

	pcmds = p->parse(command); 

	EXPECT_EQ("ls -a", pcmds.at(0)); 
	EXPECT_EQ(";", pcmds.at(1)); 
	EXPECT_EQ("echo hello", pcmds.at(2)); 
	EXPECT_EQ("&&", pcmds.at(3));
	EXPECT_EQ("mkdir test", pcmds.at(4)); 
	EXPECT_EQ("||", pcmds.at(5)); 
	EXPECT_EQ("echo world", pcmds.at(6)); 
	EXPECT_EQ(";", pcmds.at(7)); 
	EXPECT_EQ("git status", pcmds.at(8));
};

TEST(ParseTest4, commentCmd){
	Parse* p = new Parse(); 
	vector<string> pcmds;
	int size = 0; 
	string command = "ls -a && echo hello || mkdir test #make new directory";

	pcmds = p->parse(command);
	size = pcmds.size(); 

	EXPECT_EQ(5,size);
};

TEST(ParseTest5, quoteConnectorCmd){
	Parse* p = new Parse();
	vector<string> pcmds; 
	string command = "ls -a; echo \"hello && goodbye\"";

	pcmds = p->parse(command); 
	
	EXPECT_EQ("echo \"hello && goodbye\"", pcmds.at(2)); 
}

TEST(CommandTest1, commandExecute){
	string command = "ls -a";
	Command* c = new Command(command);
	
	EXPECT_TRUE(c->execute()); 

}

//Assignment 3 tests
TEST(CommandTest2, commandExecute){
	string command2 = "echo hello";
	Command* c2 = new Command(command2);  

	EXPECT_TRUE(c2->execute()); 
}

TEST(ParseTest6, convertTestpath){
	Parse* p = new Parse(); 
	vector<string> pcmds;
	string command = "[-e test/file/path]";

	pcmds = p->parse(command);

	EXPECT_EQ("test -e test/file/path", pcmds.at(0)); 
}

TEST(ParseTest7, convertTestPath2){
	Parse* p = new Parse(); 
	vector<string> pcmds; 
	string command = "[-f test/file/path]; mkdir test || echo hi"; 

	pcmds = p->parse(command); 
	
	EXPECT_EQ("test -f test/file/path", pcmds.at(0)); 
	EXPECT_EQ(";", pcmds.at(1)); 
	EXPECT_EQ("mkdir test", pcmds.at(2));
	EXPECT_EQ("||", pcmds.at(3)); 
	EXPECT_EQ("echo hi", pcmds.at(4)); 
};

TEST(ParseTest8, convertTestPathNoTag){
	Parse* p = new Parse();
	vector<string> pcmds; 
	string command = "[test/file/path]";

	pcmds = p->parse(command); 

	EXPECT_EQ("test -e test/file/path", pcmds.at(0));
};

TEST(ParseTest9, convertTestPathNoTag2){
	Parse* p = new Parse(); 
	vector<string> pcmds;
	string command = "echo hello || [test/file/path] && mkdir test";

	pcmds = p->parse(command); 

	EXPECT_EQ("echo hello", pcmds.at(0)); 
	EXPECT_EQ("||", pcmds.at(1)); 
	EXPECT_EQ("test -e test/file/path", pcmds.at(2)); 
	EXPECT_EQ("&&", pcmds.at(3)); 
	EXPECT_EQ("mkdir test", pcmds.at(4)); 
};

TEST(ParseTest10, convertTestpathAndParseParen){
	Parse* p = new Parse();
	vector<string> pcmds;
	string command = "ls -a; (echo a && echo b) || [-d test/file/path]";

	pcmds = p->parse(command); 

	EXPECT_EQ("ls -a", pcmds.at(0)); 
	EXPECT_EQ(";", pcmds.at(1)); 
	EXPECT_EQ("(", pcmds.at(2)); 
	EXPECT_EQ("echo a", pcmds.at(3)); 
	EXPECT_EQ("&&", pcmds.at(4)); 
	EXPECT_EQ("echo b", pcmds.at(5)); 
	EXPECT_EQ(")", pcmds.at(6)); 
	EXPECT_EQ("||", pcmds.at(7)); 
	EXPECT_EQ("test -d test/file/path", pcmds.at(8));
}

TEST(ParseTest11, ParseParen){
	Parse* p = new Parse(); 
	vector<string> pcmds; 
	string command = "(echo a)"; 

	pcmds = p->parse(command); 

	EXPECT_EQ("(", pcmds.at(0));
	EXPECT_EQ("echo a", pcmds.at(1)); 
	EXPECT_EQ(")", pcmds.at(2)); 
}

TEST(ParseTest12, ParseParen2){
	Parse* p = new Parse(); 
	vector<string> pcmds; 
	string command = "(echo a && echo b) || (echo c && echo d)";

	pcmds = p->parse(command); 

	EXPECT_EQ("(", pcmds.at(0)); 
	EXPECT_EQ("echo a", pcmds.at(1)); 
	EXPECT_EQ("echo b", pcmds.at(3));
	EXPECT_EQ(")", pcmds.at(4)); 
	EXPECT_EQ("||", pcmds.at(5)); 
	EXPECT_EQ("(", pcmds.at(6)); 
	EXPECT_EQ("echo c", pcmds.at(7)); 
	EXPECT_EQ("echo d", pcmds.at(9)); 
	EXPECT_EQ(")", pcmds.at(10)); 
};

//test shunting yard

#endif	
