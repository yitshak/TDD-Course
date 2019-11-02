#include "gtest\gtest.h"
#include "Ants.h"

const std::string ref = "Iteration 0, num of ants = 100\n\
Iteration 1, num of ants = 95.6\n\
Iteration 2, num of ants = 91\n\
Iteration 3, num of ants = 86.248\n\
Iteration 4, num of ants = 81.416\n\
Iteration 5, num of ants = 76.5818\n\
Iteration 6, num of ants = 71.8182\n\
Iteration 7, num of ants = 67.1877\n\
Iteration 8, num of ants = 62.7401\n\
Iteration 9, num of ants = 58.512\n\
The end, num of ants = 54.5281\n";


TEST(AntsTests, RunSimulationReference)
{
	// This can be an ofstream as well or any other ostream
	std::stringstream buffer;

	// Save cout's buffer here
	std::streambuf *sbuf = std::cout.rdbuf();

	// Redirect cout to our stringstream buffer or any other ostream
	std::cout.rdbuf(buffer.rdbuf());

	// Use cout as usual
	Ants ants;
	ants.runSimulation();


	// When done redirect cout to its old self
	std::cout.rdbuf(sbuf);

	std::istringstream isst(buffer.str());

	
	ASSERT_EQ(0, strcmp(buffer.str().c_str(), ref.c_str()));
}

TEST(boardInit, legacyInit)
{
	Board theBoard;
	Init(legacyBoard);

	for (uint i; i < ARR_MAX; i++)
	{
		for (uint j; j < ARR_MAX; j++)
		{

		}
	}
}