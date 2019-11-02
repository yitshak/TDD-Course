#pragma once
// ShoppingCart.cpp
#include "ShoppingCart_example1.h"

Product::Product(string name, float price,uint quantity)
	: mPrice(price), mQuantity(quantity), mX(1), mY(0) {
}

float Product::getPrice() {
	uint quantityForPayment = (mQuantity / (mX + mY))*mX;
	quantityForPayment += mQuantity % (mX + mY);
	return mPrice*quantityForPayment;
}

void Product::setQuantity(uint quantity)
{
	mQuantity = quantity;
}

void Product::setSpecialOffer(uint x, uint y)
{
	mX = x;
	mY = y;

}

uint Product::getQuantity()
{
	return mQuantity;
}

ShoppingCart::~ShoppingCart(void)
{
	logger_->logActivity("Destroy Crat", "");
	if (mProductCount > 0)
	{
		logger_->logState("Non-Empty");
	}
	else
	{
		logger_->logState("Empty");
	}
}

ShoppingCart::ShoppingCart(LogUtilityIfs * logger) :
	mProductCount(0), mTotalValue(0),mDiscount(0.0f) {
	logger_ = logger;

	logger_->logActivity("Create Crat","");
	logger_->logState("Empty");
}

void ShoppingCart::addProduct(Product p) {
	logger_->logActivity("Add Product", "");
	if (mProductCount > 0)
	{
		logger_->logState("Non-Empty");
	}
	else
	{
		logger_->logState("Empty");
	}
	mProductCount += p.getQuantity(); 
	mTotalValue += p.getPrice();
}

uint ShoppingCart::getProductCount() { 
	return mProductCount; 
}

float ShoppingCart::getTotalValue()
{
	return mTotalValue*(1-mDiscount/100.0f);
}

void ShoppingCart::applyDiscount(float discount)
{
	mDiscount = discount > 100.0 ? 100.0f : discount;
	mDiscount = mDiscount < 0.0f ? 0.0f : mDiscount;
	logger_->logActivity("Apply Discount", discount.toString());
	if (mProductCount > 0)
	{
		logger_->logState("Non-Empty");
	}
	else
	{
		logger_->logState("Empty");
	}

	"Apply Discount", "21.5"

}
