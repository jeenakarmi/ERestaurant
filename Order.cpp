#include "Order.h"
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <vector>
#include <iomanip>
#include <conio.h>

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
	std::cout << "Done with order? (Y/N): ";
	char doneInput;
	std::cin >> doneInput;
	// refactor this to ternary operator
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


bool Order::placeOrder(Customer* customer)
{
	bool success{ true };
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

		if (customer->getUsername() == "")
		{
			customer->createOrderAccount();
			// make a data file with record of order items for this customer
			std::string orderFile = "RestaurantData/Orders/" + customer->getUsername() + ".txt";
			std::ofstream outf(orderFile, std::ios::app);
			outf << currOrderItem.itemName << ',' << currOrderItem.quantity << ',' << currOrderItem.itemPrice << ',' << (currOrderItem.orderComplete ? "true" : "false") << '\n';
			outf.close();
		}
		else
		{
			std::string customerOrderFile = "RestaurantData/Orders/" + customer->getUsername() + ".txt";
			std::ofstream outf(customerOrderFile, std::ios::app);
			outf << currOrderItem.itemName << ',' << currOrderItem.quantity << ',' << currOrderItem.itemPrice << ',' << (currOrderItem.orderComplete ? "true" : "false") << '\n';
			outf.close();
		}

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
	system("cls");
	bool fileExists{ true };
	std::string filePath = "./RestaurantData/Orders/" + customer.getUsername() + ".txt";

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
		std::cout << std::setw(5) << std::left << std::setfill(' ') << "" << std::setw(20) << std::left << "" << std::setw(10) << std::left << "" << std::setw(11) << "" << std::setw(12) << "" << std::setfill(' ') << std::endl;
		std::cout << std::setw(5) << "SN" << std::setw(20) << "Item" << std::setw(10) << "Quantity" << std::setw(11) << "Price" << std::setw(12) << "Status\n";
		std::cout << std::setw(5) << std::left << std::setfill('-') << "" << std::setw(5) << std::left << "" << std::setw(20) << std::left << "" << std::setw(10) << "" << std::setw(10) << "" << std::setfill(' ') << std::endl;

		//std::cout << "SN\tItem\tQuantity\tPrice\tStatus\n";
		std::string line;
		int sn = 0;
		bool complete = false;
		int lineCount = 0;
		while (std::getline(inf, line))
		{
			if (lineCount == 0)
			{
				++lineCount;
				continue;
			}
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


			std::cout << std::setw(5) << ++sn << std::setw(20) << name << std::setw(10) << quantity << std::setw(11) << price << std::setw(11) << (complete ? "Complete" : "Pending") << '\n';

			//std::cout << ++sn << '\t' << name << '\t' << quantity << '\t' << price << '\t' << (complete ? "Complete" : "Pending") << '\n';
			itemTotal += quantity;
			priceTotal += price;
		}
	}
	if (itemTotal != 0)
	{
		std::cout << "\n" << std::setw(5) << "" << std::setw(20) << "Total" << std::setw(10) << itemTotal << std::setw(11) << priceTotal << std::setw(5) << (isAllOrderComplete(customer) ? "Complete" : "Not Complete") << "\n";

		/*std::cout << "Total\n";
		std::cout << "Item: " << itemTotal << '\n';
		std::cout << "Price: " << priceTotal << '\n';
		*/
		std::cout << "\nOrder Completed Status: " << (isAllOrderComplete(customer) ? "Complete" : "Not Complete") << '\n';

	}
	inf.close();
	return fileExists;
}



void Order::displayOrderFromFile(std::string path)
{
	std::ifstream inf(path);
	if (!inf)
	{
		std::cout << "No order file for this path: " << path << "!\n";
	}
	else
	{
		
		std::cout << std::setfill(' ') << std::setw(5) << ' '
			<< std::setw(20) << ' '
			<< std::setw(10) << ' ' << std::setfill(' ') << std::endl;

		std::cout << std::setw(3) << "SN" << std::setw(20) << "Item" << std::setw(15) << "Quantity" << std::setw(15) << "Status" << '\n';
		std::cout << "--------------------------------------------------------------\n";
		std::string line;
		int sn = 0;
		bool complete = false;
		int lineCount = 0;
		while (std::getline(inf, line))
		{
			if (lineCount == 0)
			{
				++lineCount;
				continue;
			}
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

			std::cout << std::setw(3) << ++sn << std::setw(20) << name << std::setw(15) << quantity << std::setw(15) << (complete ? "Complete" : "Pending") << '\n';
		}
		std::cout << "--------------------------------------------------------------\n";
	}
}


void Order::markItemOrderComplete(std::string path, int id)
{
	std::ifstream inf(path);
	std::ofstream outf("temp.txt", std::ios::app);
	int count = 0;
	if (!inf)
	{
		std::cout << "No order file for this path: " << path << "!\n";
	}
	else
	{
		std::string line;
		int sn = 0;
		bool complete = false;
		int lineCount = 0;
		while (std::getline(inf, line))
		{
			if (lineCount == 0)
			{
				++lineCount;
				outf << line << '\n';
				continue;
			}
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

			if (++count == id)
			{
				complete = !complete; // toggle complete
			}

			outf << name << ',' << quantity << ',' << price << ',' << (complete ? "true" : "false") << '\n';
		}
	}
	outf.close();
	inf.close();

	std::remove(path.c_str());
	std::rename("temp.txt", path.c_str());
}


bool Order::isAllOrderComplete(Customer customer)
{
	bool completed{ true };
	std::string orderFilePath{ "./RestaurantData/Orders/" + customer.getUsername() + ".txt" };

	std::ifstream inf(orderFilePath);
	int orderCount = 0;
	
	int lineCount = 0;
	while (!inf.eof())
	{
		std::string line;
		if (std::getline(inf, line))
		{
			if (lineCount == 0)
			{
				++lineCount;
				continue;
			}
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
	std::string orderFilePath{ "./RestaurantData/Orders/" + customer.getUsername() + ".txt" };
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

	if (count <= 1)
	{
		system("CLS");
		std::cout << "You have not placed an order yet!\n";
		std::remove(orderFilePath.c_str());
	}
}

void Order::payOrderBill(Customer customer)
{
	std::string orderFilePath{ "RestaurantData/Orders/" + customer.getUsername() + ".txt" };
	// payment process goes here

	std::cout << "Your password: ";
	std::string password;
	//Enter password for new customer
	char ch;
	while ((ch = _getch()) != '\r') {
		if (ch == '\b') { // Backspace character
			if (!password.empty()) {
				password.pop_back();
				std::cout << "\b \b"; // Move cursor back and erase the character
			}
		}
		else {
			password.push_back(ch);
			std::cout << '*';
		}
	}

	if (customer.getPassword() == password)
	{
		std::cout << "\nPayment Successful!\n";
		std::remove(orderFilePath.c_str());
	}
	else
	{
		std::cout << "\nOnly authorized individual and carry out payment!\n";
	}
}