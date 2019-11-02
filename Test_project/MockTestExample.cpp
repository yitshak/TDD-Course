#include "gmock/gmock.h"
using ::testing::AtLeast;
using ::testing::Ref;
using ::testing::A;

class Turtle
{
public:
	virtual ~Turtle() {}
	virtual void PenUp() = 0;
	virtual void PenDown() = 0;
	virtual void Forward(int distance) = 0;
	virtual int GotoPoint(int& x, int& y) = 0;
};

class Painter
{
public:
	Painter(Turtle& t) : mTurtle(t) {}
	bool DrawShape(int& x, int& y) {
		mTurtle.GotoPoint(x, y);
		mTurtle.PenDown();
		return true;
	}
private:
	Turtle& mTurtle;
};

class MockTurtle : public Turtle
{
public:
	MOCK_METHOD0(PenUp, void());
	MOCK_METHOD0(PenDown, void());
	MOCK_METHOD1(Forward, void(int distance));
	MOCK_METHOD2(GotoPoint, int(int& x, int& y));
};

TEST(MockTestsExample, TurtleMockPenDownTest)
{
	int myX = 1, myY = 2;
	MockTurtle mockTurtle;

	EXPECT_CALL(mockTurtle, GotoPoint(Ref(myX), A<int&>())) // Expectation
		.Times(AtLeast(1));

	Painter painter(mockTurtle);
	ASSERT_TRUE(painter.DrawShape(myX, myY));  // Action
											   // Verification
}