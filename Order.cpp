#include "Order.h"
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include "welcome.h"
#include <iomanip>

Order::Order()
{
	itemName = "";
	itemPrice = 0.0f;
	quantity = 0.0f;
	orders = "";
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
	welcome("Hello");
	std::cout << "\n\nPLACE AN ORDER HERE...\n";
	//std::cout << "Hello, " << customer.getUsername() << "! Place an order here.\n";
	MenuItem menu;
	menu.showMenu();

	std::cout << "\nPlace your order now!\n";
	bool done{ false };
	while (!done)
	{
		MenuItem currItem;
		std::cout << "Item ID: ";
		int id;
		std::cin >> id;

		currItem = currItem.getItem(id);

		Order currOrderItem;

		currOrderItem.itemName = currItem.getName();
		currOrderItem.itemPrice = currItem.getPrice();
		currOrderItem.quantity = 0.0f;
		currOrderItem.orderComplete = false;

		std::cout << "Item: " << currOrderItem.itemName << "\tPrice: " << currOrderItem.itemPrice << '\n';
		std::cout << "Quantity: ";
		float currItemQuantity;
		std::cin >> currItemQuantity;

		currOrderItem.quantity += currItemQuantity;
		currOrderItem.itemPrice *= currOrderItem.quantity;

		std::cout << currOrderItem.itemName << '\t' << currOrderItem.quantity << '\t' << currOrderItem.itemPrice << '\n';

		// make a data file with record of order items for this customer
		std::string orderfile = "RestaurantData/Orders/" + customer.getUsername() + ".txt";
		createOrderFile(currOrderItem, orderfile);

		done = idDoneOrdering();
	}
	customer.setAllOrderComplete(false);
	return success;
}

void Order::createOrderFile(Order currOrderItem, std::string path)
{
	std::ofstream outf(path, std::ios::app);

	outf << currOrderItem.itemName << ',' <<  currOrderItem.quantity << ',' << currOrderItem.itemPrice << ',' << (currOrderItem.orderComplete ? "true" : "false") << '\n';

	outf.close();
}

void Order::displayCustomerOrder(Customer customer)
{
	std::string filePath = "RestaurantData/Orders/" + customer.getUsername() + ".txt";

	std::ifstream inf(filePath);

	int itemTotal = 0;
	float priceTotal = 0.0f;

	if (!inf)
	{
		std::cout << "No order file for this customer: " << customer.getUsername() << "!\n";
	}
	else
	{
		std::cout << "SN\tItem\tQuantity\tPrice\tStatus\n";
		std::string line;
		int sn = 0;
		bool complete = false;
		while (std::getline(inf, line))
		{
			std::string name;
			float quantity;
			float price;

			int commaIndex1 = line.find(',');
			int commaIndex2 = line.find(',', commaIndex1 + 1);
			int commaIndex3 = line.find(',', commaIndex2 + 1);

			name = line.substr(0, commaIndex1);
			quantity = std::stof(line.substr(commaIndex1 + 1, commaIndex2));
			price = std::stof(line.substr(commaIndex2 + 1, commaIndex3));
			complete = line.substr(commaIndex3 + 1).compare("true") == 0 ? true : false;

			std::cout << ++sn << '\t' << name << '\t' << quantity << '\t' << price << '\t' << (complete ? "Complete" : "Pending") << '\n';
			itemTotal += quantity;
			priceTotal += price;

			customer.setAllOrderComplete(complete);
		}
	}
	std::cout << "Total\n";
	std::cout << "Item: " << itemTotal << '\n';
	std::cout << "Price: " << priceTotal << '\n';

	std::cout << "\nOrder Completed Status: " << (customer.getAllOrderComplete() ? "Complete" : "Not Complete") << '\n';

	inf.close();
}