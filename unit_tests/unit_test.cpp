#include "gtest/gtest.h"
#include "test1.cpp"

//#include "../header/Composite.h"
#include "../header/Command.h"
//#include "../src/Parse.cpp"

int main(int argc, char**argv) {
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
