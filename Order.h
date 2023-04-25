#pragma once
#include "Customer.h"
#include "MenuItem.h"

#include <vector>

const std::string ORDERS_FILE{ "RestaurantData/Orders.txt" };
const std::string CUSTOMER_LIST_FILE{ "UserData/CUSTOMER.txt" };

class Order
{
	std::string ordererName;
	std::string ordererPhone;
	std::string itemName;
	float itemPrice;
	float quantity;
	bool orderComplete;

	std::string orders;
public:
	Order();
	bool idDoneOrdering();
	bool placeOrder(Customer customer);
	void createOrderFile(Order currOrderItem, std::string path);
	bool displayCustomerOrder(Customer customer); // returns true if file exists

	bool isAllOrderComplete(Customer customer);

	void cancelOrder(Customer customer);
	void payOrderBill(Customer customer);
};