#pragma once
#include "Customer.h"
#include "MenuItem.h"

#include <vector>

const std::string ORDERS_FILE{ "RestaurantData/Orders.txt" };

class Order
{
	std::string ordererName;
	std::string ordererPhone;
	std::string itemName;
	float itemPrice;
	float quantity;

	// DMA for order items per customer
	std::vector<Order> orders;
public:
	Order();
	bool idDoneOrdering();
	bool placeOrder(Customer customer);
	void updateOrderFile(Order orderItem);
	void updateOrders(Order currOrderItem);
	void displayCustomerOrder(Customer customer);
};