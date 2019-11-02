#pragma once
typedef unsigned int uint;


// ShoppingCart.h
#include <string>
using namespace std;

class LogUtilityIfs
{
public:
	virtual ~LogUtilityIfs() {};
	virtual void logActivity(string activity, string activityData) = 0;
	virtual void logState(string state) = 0;

};

class Product
{
public:
	Product(string name, float price,uint quantity =1);

	float getPrice();
	void setSpecialOffer(uint x, uint y);
	void setQuantity(uint quantity);
	uint getQuantity();

private:
	float mPrice;
	uint mQuantity,mX,mY;
};

class ShoppingCart
{
public:
	ShoppingCart(LogUtilityIfs * logger);

	~ShoppingCart(void );
	void addProduct(Product p);

	uint  getProductCount();
	float getTotalValue();

	void applyDiscount(float discount);

private:
	uint mProductCount;
	float mTotalValue;
	float mDiscount;
	LogUtilityIfs * logger_;
};
