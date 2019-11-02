#pragma once
typedef unsigned int uint;


#include <string>
using namespace std;

class BadDiscountValue : public exception
{
};

typedef pair<uint, uint> BuyXGetyOffer;

class Product
{
public:
	Product(string name, uint price);

	double getUnitPrice();
	double getTotalValue();
	void setQuantity(uint quantity);
	uint getQuantity();

	void applySpecialOffer(uint buyX, uint getYForFree);

private:
	double mPrice;
	uint mQuantity;
	BuyXGetyOffer myOffer;
};

class ShoppingCart
{
public:
	ShoppingCart();

	void addProduct(Product p);

	uint getProductCount();
	double getTotalValue();

	void applyDiscount(uint discount);

private:
	double calculateValueAfterDiscount(double val);

	static const uint OneHundredPercent = 100;

	uint mProductCount;
	double mTotalValue;
	uint mDiscount;
};