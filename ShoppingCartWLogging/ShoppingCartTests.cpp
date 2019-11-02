#include "gtest/gtest.h"
#include "ShoppingCartWLogging.h"

TEST(ProductTest, CreateProduct)
{
	Product milk("Milk", 5);
	ASSERT_EQ(milk.getQuantity(), 1);
	ASSERT_EQ(milk.getUnitPrice(), 5);
}

TEST(ProductTest, UpdateProductQuantity)
{
	Product milk("Milk", 5);
	milk.setQuantity(7);

	ASSERT_EQ(milk.getQuantity(), 7);
}

TEST(ProductTest, TotalPrice)
{
	Product milk("Milk", 5);
	milk.setQuantity(7);

	ASSERT_EQ(milk.getTotalValue(), 35);
}

class ShoppingCartTest : public ::testing::Test
{
protected:
	ShoppingCart cart;
};

TEST_F(ShoppingCartTest, EmptyCart)
{
	EXPECT_EQ(0, cart.getProductCount());
	EXPECT_EQ(0, cart.getTotalValue());
}

TEST_F(ShoppingCartTest, AddOneProduct)
{
	Product milk("Milk", 5);

	cart.addProduct(milk);

	EXPECT_EQ(1, cart.getProductCount());
	EXPECT_EQ(5, cart.getTotalValue());
}

TEST_F(ShoppingCartTest, AddTwoDifferentProducts)
{
	Product milk("Milk", 5);
	Product coffee("Coffee", 30);
	
	cart.addProduct(milk);
	cart.addProduct(coffee);

	EXPECT_EQ(2, cart.getProductCount());
	EXPECT_EQ(35, cart.getTotalValue());
}

TEST_F(ShoppingCartTest, AddTwoSimilarProducts)
{
	Product milk("Milk", 5);
	milk.setQuantity(2);

	cart.addProduct(milk);

	EXPECT_EQ(2, cart.getProductCount());
	EXPECT_EQ(10, cart.getTotalValue());
}

TEST_F(ShoppingCartTest, ApplyRegularDiscount)
{
	Product milk("Milk", 50);
	cart.addProduct(milk);

	cart.applyDiscount(1);

	// Discount means: total val = total val - discount
	EXPECT_DOUBLE_EQ(cart.getTotalValue(), 49.5);
}

TEST_F(ShoppingCartTest, ApplyDiscountLargerThan100)
{
	Product milk("Milk", 50);
	cart.addProduct(milk);

	EXPECT_THROW(cart.applyDiscount(110), BadDiscountValue);
}

TEST_F(ShoppingCartTest, AddProductAfterDiscount)
{
	cart.applyDiscount(50);

	Product milk("Milk", 50);
	cart.addProduct(milk);

	EXPECT_DOUBLE_EQ(cart.getTotalValue(), 25.0);
}

TEST_F(ShoppingCartTest, SpecialOfferForProductQuantityMatches)
{
	Product milk("Milk", 50);
	milk.setQuantity(4);
	milk.applySpecialOffer(4, 1);

	EXPECT_DOUBLE_EQ(milk.getTotalValue(), 150);
}

TEST_F(ShoppingCartTest, SpecialOfferForProductQuantityMatches2)
{
	Product milk("Milk", 50);
	milk.setQuantity(7);
	milk.applySpecialOffer(4, 1);

	EXPECT_DOUBLE_EQ(milk.getTotalValue(), 300);
}

TEST_F(ShoppingCartTest, SpecialOfferForProduct2Free)
{
	Product milk("Milk", 50);
	milk.setQuantity(8);
	milk.applySpecialOffer(4, 2);

	EXPECT_DOUBLE_EQ(milk.getTotalValue(), 200);
}

TEST_F(ShoppingCartTest, SpecialOfferBeforeQuantityIsKnown)
{
	Product milk("Milk", 50);
	milk.applySpecialOffer(4, 1);
	milk.setQuantity(8);

	EXPECT_DOUBLE_EQ(milk.getTotalValue(), 300);
}

TEST_F(ShoppingCartTest, SpecialOfferCombinedWithDiscount)
{
	Product milk("Milk", 50);
	milk.applySpecialOffer(4, 3);
	milk.setQuantity(8);

	cart.applyDiscount(10);
	cart.addProduct(milk);

	EXPECT_DOUBLE_EQ(cart.getTotalValue(), 90);
}
