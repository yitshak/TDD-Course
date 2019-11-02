// ShoppingCartExample.cpp

#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "ShoppingCart_Example1.h"

class MockLogger : public LogUtilityIfs
{
public:
	~MockLogger() {};
	MOCK_METHOD2(logActivity, void(string, string));
	MOCK_METHOD1(logState, void(string));

};

class StubLogger : public LogUtilityIfs
{
public:
	virtual ~StubLogger() {};
	virtual void logActivity(string activity, string activityData) {};
	virtual void logState(string state) {};


};


class ProductTest : public ::testing::Test
{
protected:
	
};

TEST_F(ProductTest, setSpecialDiscountNotApplied)
{
	Product theProduct("testProduct",3,2);
	theProduct.setSpecialOffer(3, 1);

	EXPECT_FLOAT_EQ(6.0f, theProduct.getPrice());
}

TEST_F(ProductTest, setSpecialDiscountApplied)
{
	Product theProduct("testProduct", 3, 3);
	theProduct.setSpecialOffer(2, 1);

	EXPECT_FLOAT_EQ(6.0f, theProduct.getPrice());
}

TEST_F(ProductTest, setSpecialDiscountMoreThanOnce)
{
	Product theProduct("testProduct", 3, 12);
	theProduct.setSpecialOffer(3, 2);

	EXPECT_FLOAT_EQ(3.0f * 8, theProduct.getPrice());
}

class ShoppingCartTest : public ::testing::Test
{
protected:
	StubLogger stubLogger;
	ShoppingCart * cart;

	void SetUp(void)
	{
		cart = new ShoppingCart(&stubLogger);
	}

	void TearDown(void)
	{
		delete cart;
	}
};

TEST_F(ShoppingCartTest, AddProduct)
{
	Product milk("Milk", 5.4f);

	cart->addProduct(milk);

	EXPECT_EQ(1, cart->getProductCount());
	EXPECT_FLOAT_EQ(5.4f, cart->getTotalValue());
}

TEST_F(ShoppingCartTest, AddTwoDifferentProducts)
{
	Product milk("Milk", 5);
	Product coffee("Coffee", 30.2f);
	
	cart->addProduct(milk);
	cart->addProduct(coffee);

	EXPECT_EQ(2, cart->getProductCount());
	EXPECT_FLOAT_EQ(35.2f, cart->getTotalValue());
}

TEST_F(ShoppingCartTest, AddTwoSimilarProducts)
{
	Product milk("Milk", 5);
	milk.setQuantity(2);

	cart->addProduct(milk);

	EXPECT_EQ(2, cart->getProductCount());
	EXPECT_FLOAT_EQ(10.0f, cart->getTotalValue());
}

TEST_F(ShoppingCartTest, ApplyDiscountAtEnd)
{
	Product milk("Milk", 5);
	cart->addProduct(milk);

	cart->applyDiscount(50.0);

	// Discount means: total val = total val - discount
	EXPECT_FLOAT_EQ(2.5f, cart->getTotalValue());
}

TEST_F(ShoppingCartTest, ApplyDiscountInMiddle)
{
	Product milk("Milk", 5);
	cart->addProduct(milk);

	cart->applyDiscount(50.0);

	Product bread("Bread", 3);
	cart->addProduct(bread);

	// Discount means: total val = total val - discount
	EXPECT_FLOAT_EQ(4.0f, cart->getTotalValue());
}




/*
- logging empty cart creation and destruction- state Empty, activity creation
- adding item to empty cart - state Empty, activity addition
- adding item to non empty cart - state non-Empty, activity addition
- apply discount - state non-empty  discount
- get cost from non empty cart - show price calculation for each item and total
*/

TEST_F(ShoppingCartTest, LogCreatrion)
{
	MockLogger mockLoger;

	EXPECT_CALL(mockLoger, logState("Empty"))
		.Times(2);
	EXPECT_CALL(mockLoger, logActivity("Create Crat", ""))
		.Times(1);
	EXPECT_CALL(mockLoger, logActivity("Destroy Crat", ""))
		.Times(1);

	ShoppingCart theCart(&mockLoger);
}

TEST_F(ShoppingCartTest, AddProductToEmptyCrat)
{
	MockLogger mockLoger;

	EXPECT_CALL(mockLoger, logState("Empty"))
		.Times(2);
	EXPECT_CALL(mockLoger, logState("Non-Empty"))
		.Times(1);
	EXPECT_CALL(mockLoger, logActivity("Create Crat", ""))
		.Times(1);
	EXPECT_CALL(mockLoger, logActivity("Destroy Crat", ""))
		.Times(1);
	EXPECT_CALL(mockLoger, logActivity("Add Product", ""))
		.Times(1);

	ShoppingCart theCart(&mockLoger);
	Product milk("Milk", 5);
	theCart.addProduct(milk);
}

TEST_F(ShoppingCartTest, AddProductToNonEmptyCrat)
{
	MockLogger mockLoger;

	EXPECT_CALL(mockLoger, logState("Empty"))
		.Times(2);
	EXPECT_CALL(mockLoger, logState("Non-Empty"))
		.Times(2);
	EXPECT_CALL(mockLoger, logActivity("Create Crat", ""))
		.Times(1);
	EXPECT_CALL(mockLoger, logActivity("Destroy Crat", ""))
		.Times(1);
	EXPECT_CALL(mockLoger, logActivity("Add Product", ""))
		.Times(2);

	ShoppingCart theCart(&mockLoger);
	Product milk("Milk", 5);
	theCart.addProduct(milk);

	theCart.addProduct(milk);
}

TEST_F(ShoppingCartTest, SetDiscount)
{
	MockLogger mockLoger;

	EXPECT_CALL(mockLoger, logState("Empty"))
		.Times(2);
	EXPECT_CALL(mockLoger, logState("Non-Empty"))
		.Times(3);
	EXPECT_CALL(mockLoger, logActivity("Create Crat", ""))
		.Times(1);
	EXPECT_CALL(mockLoger, logActivity("Destroy Crat", ""))
		.Times(1);
	EXPECT_CALL(mockLoger, logActivity("Add Product", ""))
		.Times(1);
	EXPECT_CALL(mockLoger, logActivity("Apply Discount", "21.5"))
		.Times(1);


	ShoppingCart theCart(&mockLoger);
	Product milk("Milk", 10);
	theCart.addProduct(milk);

	theCart.applyDiscount(21.5);;
}