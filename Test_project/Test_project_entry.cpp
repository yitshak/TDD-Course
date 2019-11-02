// VPU_Host_Test.cpp : Defines the entry point for the VPU host library test
//

#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include <stdio.h>


#define GLOG_NO_ABBREVIATED_SEVERITIES

//#include <glog/logging.h>


//using namespace google;
std::string g_logStr;

int main(int argc, char **argv)
{
	std::cout << "\nTests will start momentarily...\n\n";
	
	int tests_ret = -1;
	try
	{
		::testing::InitGoogleMock(&argc, argv);

		tests_ret = RUN_ALL_TESTS();


	}
	catch (std::exception * e)
	{
		std::cout << "Exception caught in main testing function" << e->what();
	}
	
    return tests_ret;
}
