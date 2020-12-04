CMAKE_MINIMUM_REQUIRED(VERSION 2.8)

SET(CMAKE_CXX_STANDARD 11)

ADD_SUBDIRECTORY(googletest)

ADD_EXECUTABLE(rshell
	./src/Node.cpp 
	./src/Tree.cpp 

	./src/Command.cpp

	./src/Parse.cpp

	./src/Test.cpp
	./src/rshell.cpp
)

ADD_EXECUTABLE(test

        unit_tests/unit_test.cpp
        src/Parse.cpp
        src/Command.cpp

)


TARGET_LINK_LIBRARIES(test gtest)
TARGET_COMPILE_DEFINITIONS(test PRIVATE gtest_disable_pthreads=ON)








