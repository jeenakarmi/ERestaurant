#include "Order.h"
#include <iostream>
#include <string>
#include <fstream>

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

bool Order::placeOrder(Customer customer)
{
	bool success{ true };
	std::cout << "Hello, " << customer.getUsername() << "! Place an order here.\n";
	MenuItem menu;
	menu.showMenu();

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

		// make a data file with record of order items for this customer
		std::string orderfile = "RestaurantData/Orders/" + customer.getUsername() + ".txt";
		createOrderFile(currOrderItem, orderfile);

		done = idDoneOrdering();
	}
	return success;
}

void Order::createOrderFile(Order orderItem, std::string path)
{
	std::ofstream outf;
	outf.open(path.c_str(), std::ios::app);

	outf << orderItem.itemName << ',' << orderItem.itemPrice << ',' << orderItem.quantity << '\n';

	outf.close();
}