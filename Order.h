#pragma once
#include "Customer.h"
#include "MenuItem.h"

class Order
{
	std::string itemName;
	float itemPrice;
	float quantity;
public:
	Order();
	bool idDoneOrdering();
	bool placeOrder(Customer customer);
	void createOrderFile(Order orderItem, std::string path);
};