#include "Order.h"
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include "welcome.h"
#include "welcome msg for oobject.h"

Order::Order()
{
	itemName = "";
	itemPrice = 0.0f;
	quantity = 0.0f;
}

bool Order::idDoneOrdering()
{
	bool isDone;
	std::cout << "Done with order? (y/N): ";
	char doneInput;
	std::cin >> doneInput;
	if (std::toupper(doneInput) == 'Y')
	{
		isDone = true;
	}
	else
	{
		isDone = false;
	}
	return isDone;
}

//yeta milauna abaaki xa hai  ................................................................................................................................................................................................

void Order::updateOrders(Order currOrderItem)
{
	orders.push_back(currOrderItem);
}

bool Order::placeOrder(Customer customer)
{
	bool success{ true };
	welcome("Hello");
	std::cout << "\n\nPLACE AN ORDER HERE...\n";
	//std::cout << "Hello, " << customer.getUsername() << "! Place an order here.\n";
	MenuItem menu;
	menu.showMenu();

	Order currOrder;
	currOrder.ordererName = customer.getUsername();
	currOrder.ordererPhone = customer.getUserPhone();

	std::cout << "\nPlace your order now!\n";
	bool done{ false };
	while (!done)
	{
		MenuItem currItem;
		Order currOrderItem;
		std::cout << "Item ID: ";
		int id;
		std::cin >> id;
		currItem = currItem.getItem(id);
		currOrderItem.itemName = currItem.getName();
		currOrderItem.itemPrice = currItem.getPrice();
		std::cout << "Item: " << currOrderItem.itemName << "\tPrice: " << currOrderItem.itemPrice << '\n';
		std::cout << "Quantity: ";
		float currItemQuantity;
		std::cin >> currItemQuantity;
		currOrderItem.quantity += currItemQuantity;
		currOrderItem.itemPrice *= currOrderItem.quantity;

		currOrder.updateOrders(currOrderItem);

		/*
		// make a data file with record of order items for this customer
		std::string orderfile = "RestaurantData/Orders/" + customer.getUsername() + ".txt";
		createOrderFile(currOrderItem, orderfile);
		*/
		updateOrderFile(currOrder);

		done = idDoneOrdering();
	}
	return success;
}

void Order::updateOrderFile(Order orderItem)
{
	std::ofstream outf;
	outf.open(ORDERS_FILE, std::ios::binary | std::ios::app);

	outf.write((char*)&orderItem, sizeof(orderItem));

	outf.close();
}

void Order::displayCustomerOrder(Customer customer)
{

}