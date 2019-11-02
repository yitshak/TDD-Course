// SharedPointerTests.cpp
#include "gtest\gtest.h"
#include <string>
#include "SharedPtr.h"

TEST(SharedPointerTests, nullPointer)
{
	SharedPointer<int> p1;
	EXPECT_EQ(p1.getPtr(), (int*)NULL);
}

TEST(SharedPointerTests, zeroRefrences)
{
	SharedPointer<int> p1;
	EXPECT_EQ(p1.getRefCnt(), 0);
}

TEST(SharedPointerTests, nonNullPointer)
{
	int* pInt = new int(7);
	SharedPointer<int> p2(pInt);
	EXPECT_EQ(p2.getRefCnt(), 1);
}

TEST(SharedPointerTests, pointerCorrect)
{
	int* pInt = new int(7);
	SharedPointer<int> p2(pInt);
	EXPECT_EQ(p2.getPtr(), pInt);
}

TEST(SharedPointerTests, valueCorrect)
{
	int* pInt = new int(7);
	SharedPointer<int> p2(pInt);
	EXPECT_EQ(*p2, 7);
}

TEST(SharedPointerTests, copyConstructor)
{
	int* pInt = new int(7);
	SharedPointer<int> p2(pInt);
	SharedPointer<int> p3(p2);
	EXPECT_EQ(p3.getPtr(), pInt);
	
}

TEST(SharedPointerTests, referenceCount)
{
	int* pInt = new int(7);
	SharedPointer<int> p2(pInt);
	SharedPointer<int> p3(p2);
	SharedPointer<int> p4(p3);
	
	EXPECT_EQ(p4.getRefCnt(), 3);
}

TEST(SharedPointerTests, referenceCountAfterDelete)
{
	int* pInt = new int(7);
	SharedPointer<int> p2(pInt);
	SharedPointer<int> p3(p2);
	{
		SharedPointer<int> p4(p3);
	}
	EXPECT_EQ(p3.getRefCnt(), 2);
}

TEST(SharedPointerTests, referenceCountWithEqOperator)
{
	int* pInt = new int(7);
	SharedPointer<int> p2(pInt);
	SharedPointer<int> p3;
	p3 = p2;
	EXPECT_EQ(p3.getRefCnt(), 2);
}


TEST(SharedPointerTests, valueAfterDelete)
{
	int* pInt = new int(7);
	SharedPointer<int> p2(pInt);
	SharedPointer<int> p3(p2);
	{
		SharedPointer<int> p4(p3);
	}
	EXPECT_EQ(p3.getRefCnt(), 2);
}

TEST(SharedPointerTests, valueAfterAddition)
{
	int* pInt = new int(7);
	SharedPointer<int> p2(pInt);
	SharedPointer<int> p3(p2);
	{
		SharedPointer<int> p4(p3);
		SharedPointer<int> p5(p4);
		EXPECT_EQ(p5.getRefCnt(), 4);
	}
	EXPECT_EQ(p3.getRefCnt(), 2);
}

TEST(SharedPointerTests, valueAfterModification)
{
	int* pInt = new int(7);
	SharedPointer<int> p2(pInt);
	SharedPointer<int> p3(p2);
	*p2 = 8;
	EXPECT_EQ(*p3, 8);
}

TEST(SharedPointerTests, usingPointerToSharedPtr)
{
	int* pInt = new int(7);
	SharedPointer<int> * p2 = new SharedPointer<int>(pInt);
	SharedPointer<int> p3(*p2);
	delete p2;
	EXPECT_EQ(*p3, 7);
}

TEST(SharedPointerTests, nullPtrCopying)
{
	int* pInt = new int(7);

	SharedPointer<int> p2(NULL);
	SharedPointer<int> p3(p2);

	ASSERT_EQ(0, p3.getRefCnt());
}

TEST(SharedPointerTests, initNullPtrCopying)
{
	int* pInt = new int(7);

	SharedPointer<int> p2(NULL);
	ASSERT_DEATH(*p2 = 7, "");
}