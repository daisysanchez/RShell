CMAKE_MINIMUM_REQUIRED(VERSION 2.8)

SET(CMAKE_CXX_STANDARD 11)

ADD_EXECUTABLE(rshell	
	Node.cpp 
	Tree.cpp

	Connectors.cpp
        Ampersand.cpp
        Bars.cpp
	Semicolon.cpp
        
	Command.cpp

	Parse.cpp

	Test.cpp
	rshell.cpp
	)




