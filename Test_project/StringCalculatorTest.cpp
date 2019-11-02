
#include <string>
#include <sstream>
using namespace std;

class StringCalculator
{
public:
	static unsigned int calculate(string inputString);
};


unsigned int StringCalculator::calculate(string inputString)
{ 
	unsigned int result=0;
	std::stringstream ss(inputString);
	

	unsigned int operand = 0;
	unsigned int currentDigit = 0;
	for (unsigned int i = 0; i < inputString.length(); i++)
	{
		char currentChar = inputString[i];
		if (currentChar == ',' || currentChar == '\n')
		{

			result += (operand>1000?0:operand);
			operand = 0;
		}
		else
		{	
			if (currentChar <= '9' && currentChar >= '0')
			{
				currentDigit = currentChar - '0';
				operand *= 10;
				operand += currentDigit;
			}
			else
			{
				throw new std::exception();
			}
		}
		
	}

	//adding last operand
	result += (operand>1000 ? 0 : operand);
	return result;

};


#include "gtest/gtest.h"

/*
Test List
-V CreateCalculator
-V Single number returns number
-V Two number delimited by comma returns the sum
-V Two number delimited by \n returns the sum
-V Three numbers delimited either way return sum
-V negative number throws exception
-V numbers greater than 1000 are ignored
*/

class StringCalculatorTest : public ::testing::Test
{
protected:
	StringCalculator theCalculator;
};


TEST_F(StringCalculatorTest, singleNumber)
{
	ASSERT_EQ(18,theCalculator.calculate("18"));
}

TEST_F(StringCalculatorTest, twoNumbersWithComma)
{
	ASSERT_EQ(89, theCalculator.calculate("54,35"));
}

TEST_F(StringCalculatorTest, twoNumbersWithNewline)
{
	ASSERT_EQ(89, theCalculator.calculate("54\n35"));
}

TEST_F(StringCalculatorTest, threeNumbersWithComma)
{
	ASSERT_EQ(489, theCalculator.calculate("54,35,400"));
}

TEST_F(StringCalculatorTest, threeNumbersWithNewline)
{
	ASSERT_EQ(989, theCalculator.calculate("54\n35\n900"));
}

TEST_F(StringCalculatorTest, threeNumbersWithNewlineAndComma)
{
	ASSERT_EQ(989, theCalculator.calculate("54,35\n900"));
}

TEST_F(StringCalculatorTest, numberGreaterThan1000)
{
	ASSERT_EQ(954, theCalculator.calculate("54,1001\n900"));
}

TEST_F(StringCalculatorTest, numberGreaterThan1000Last)
{
	ASSERT_EQ(54, theCalculator.calculate("54,1001\n1001"));
}

TEST_F(StringCalculatorTest, negativeNumber)
{
	ASSERT_ANY_THROW( theCalculator.calculate("-54,1001\n1001"));
}
