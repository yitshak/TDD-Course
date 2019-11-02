#include "ShoppingCartWLogging.h"

Product::Product(string name, uint price)
	: mPrice(price), mQuantity(1) {
	myOffer.first = 1;
	myOffer.second = 0;
}

double Product::getUnitPrice() {
	return mPrice;
}

double Product::getTotalValue() {
	uint numOFFreeUnits = (mQuantity / myOffer.first) * myOffer.second;

	return mPrice * (mQuantity - numOFFreeUnits);
}

void Product::setQuantity(uint quantity)
{
	mQuantity = quantity;
}

uint Product::getQuantity()
{
	return mQuantity;
}

void Product::applySpecialOffer(uint buyX, uint getYForFree)
{
	myOffer.first = buyX;
	myOffer.second = getYForFree;
}

ShoppingCart::ShoppingCart() : 
	mProductCount(0) , mTotalValue(0), mDiscount(0) {
}

void ShoppingCart::addProduct(Product p) { 
	mProductCount += p.getQuantity(); 
	mTotalValue += calculateValueAfterDiscount(p.getTotalValue());
}

uint ShoppingCart::getProductCount() { 
	return mProductCount; 
}

double ShoppingCart::getTotalValue()
{
	return mTotalValue;
}

void ShoppingCart::applyDiscount(uint discount)
{
	mDiscount = discount;

	if (discount > OneHundredPercent)
		throw BadDiscountValue();
	
	mTotalValue = calculateValueAfterDiscount(mTotalValue);
}

double ShoppingCart::calculateValueAfterDiscount(double val)
{
	return val * ((OneHundredPercent - mDiscount) / (double)OneHundredPercent);
}
