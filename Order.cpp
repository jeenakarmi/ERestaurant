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
		currOrderItem.orderComplete = true;

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
	return success;
}

void Order::createOrderFile(Order currOrderItem, std::string path)
{
	std::ofstream outf(path, std::ios::app);

	outf << currOrderItem.itemName << ',' <<  currOrderItem.quantity << ',' << currOrderItem.itemPrice << ',' << (currOrderItem.orderComplete ? "true" : "false") << '\n';

	outf.close();
}

bool Order::displayCustomerOrder(Customer customer)
{
	bool fileExists{ true };
	std::string filePath = "RestaurantData/Orders/" + customer.getUsername() + ".txt";

	std::ifstream inf(filePath);

	int itemTotal = 0;
	float priceTotal = 0.0f;

	if (!inf)
	{
		std::cout << "No order file for this customer: " << customer.getUsername() << "!\n";
		fileExists = false;
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
		}
	}
	if (itemTotal != 0)
	{
		std::cout << "Total\n";
		std::cout << "Item: " << itemTotal << '\n';
		std::cout << "Price: " << priceTotal << '\n';

		std::cout << "\nOrder Completed Status: " << (isAllOrderComplete(customer) ? "Complete" : "Not Complete") << '\n';

	}
	inf.close();
	return fileExists;
}

bool Order::isAllOrderComplete(Customer customer)
{
	bool completed{ true };
	std::string orderFilePath{ "RestaurantData/Orders/" + customer.getUsername() + ".txt" };

	std::ifstream inf(orderFilePath);
	int orderCount = 0;
	
	while (!inf.eof())
	{
		std::string line;
		if (std::getline(inf, line))
		{
			int commaIndex1 = line.find(',');
			int commaIndex2 = line.find(',', commaIndex1 + 1);
			int commaIndex3 = line.find(',', commaIndex2 + 1);

			bool orderComplete = (line.substr(commaIndex3 + 1)).compare("true") == 0 ? true : false;

			if (!orderComplete)
			{
				completed = false;
			}
		}
	}

	inf.close();

	return completed;
}

void Order::cancelOrder(Customer customer)
{
	std::cout << "\nId: ";
	int id = 0;
	std::cin >> id;
	int count = 0;
	std::string orderFilePath{ "RestaurantData/Orders/" + customer.getUsername() + ".txt" };
	std::ifstream inf(orderFilePath);
	std::ofstream outf("temp.txt", std::ios::app);
	int orderCount = 0;
	while (!inf.eof())
	{
		std::string line;
		if (std::getline(inf, line))
		{
			int commaIndex1 = line.find(',');
			int commaIndex2 = line.find(',', commaIndex1 + 1);
			int commaIndex3 = line.find(',', commaIndex2 + 1);

			bool orderComplete = (line.substr(commaIndex3 + 1)).compare("true") == 0 ? true : false;
			count++;
			if (orderComplete && id == count)
			{
				std::cout << "Your order is complete! Cannot cancel completed order!\n";
				outf << line << '\n';
				orderCount++;
			}
			else if (!orderComplete && id == count)
			{
				std::cout << "Order Canceled!\n";
				continue;
			}
			else
			{
				outf << line << '\n';
				orderCount++;
			}
		}
	}

	inf.close();
	outf.close();

	std::remove(orderFilePath.c_str());
	std::rename("temp.txt", orderFilePath.c_str());

	if (count < 1)
	{
		std::remove(orderFilePath.c_str());
	}
}

void Order::payOrderBill(Customer customer)
{
	std::string orderFilePath{ "RestaurantData/Orders/" + customer.getUsername() + ".txt" };
	// payment process goes here

	std::cout << "Your password: ";
	std::string password;
	std::cin >> password;
	
	std::ifstream inf(CUSTOMER_LIST_FILE);
	while (!inf.eof())
	{
		std::string line;
		if (std::getline(inf, line))
		{
			int commaIndex1 = line.find(',');
			int commaIndex2 = line.find(',', commaIndex1 + 1);

			std::string username;
			std::string passFile;

			username = line.substr(0, commaIndex1);
			passFile = line.substr(commaIndex1 + 1, commaIndex2 - commaIndex1 - 1);

			if (customer.getUsername().compare(username) == 0)
			{
 				if (passFile.compare(password) == 0) 
				{
					std::cout << "Payment Successful!\n";
					std::remove(orderFilePath.c_str());
				}
				else
				{
					std::cout << "Only authorized individual and carry out payment!\n";
				}
				break;
			}
		}
	}

}