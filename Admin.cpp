#include "Admin.h"
#include <iostream>
#include <fstream>
#include <string>
#include <string_view>
#include <conio.h>
#include <cstdio>
#include <errno.h>

#include "MenuItem.h"
#include "Order.h"
#include "box.h"
#include "welcome.h"
//#include "welcome msg for oobject.h"

void Admin::getAdminData()
{
	std::cout << "\n\n";
	box(" ");
	gotoxy(30, 8);
	std::cout << "Enter username: ";
	//gotoxy(45, 4);
	std::cin >> username;
	gotoxy(30, 9);
	std::cout << "Enter password: ";
	//admimn password
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
	std::cout << "\n";
}

bool Admin::validateLogin()
{
	bool isValid{ false };

	std::ifstream inf;
	inf.open(ADMIN_FILE, std::ios::in);

	Admin currAdmin;
	if (!inf)
	{
		
		std::cout << "File Could Not Be Opened! filename: " << ADMIN_FILE << '\n';
		return false;
	}

	std::string line;
	while (std::getline(inf, line))
	{
		std::string userNameData; // from file
		std::string passwordData;
		
		int commaIndex1 = line.find(",");

		userNameData = line.substr(0, commaIndex1);
		passwordData = line.substr(commaIndex1 + 1);

		if (username == userNameData && password == passwordData)
		{
			isValid = true;
		}
	}

	return isValid;
}

std::string Admin::getUserName()
{
	return username;
}

void Admin::displayCustomersWhoOrdered()
{
	std::ifstream customerFile(CUSTOMER_FILE);
	
	std::string line;
	int count = 0;
	while (std::getline(customerFile, line))
	{
		int commaIndex1 = line.find(',');
		std::string cusUserName = line.substr(0, commaIndex1);
		std::string orderFilePath{ "RestaurantData/Orders/" + cusUserName + ".txt" };

		std::ifstream orderFile(orderFilePath);

		if (orderFile)
		{
			
			gotoxy(40, 4);
			std::cout << ++count << '\t' << cusUserName << '\n';
		}

		orderFile.close();
	}

	customerFile.close();
}

bool Admin::displayOrdersOfCustomer(int id)
{
	welcome("ORDERS");
	std::ifstream customerFile(CUSTOMER_FILE);

	std::string line;
	int count = 0;
	std::string orderFilePath;

	Order cusOrder;
	while (std::getline(customerFile, line))
	{
		int commaIndex1 = line.find(',');
		std::string cusUserName = line.substr(0, commaIndex1);
		orderFilePath = "RestaurantData/Orders/" + cusUserName + ".txt";

		std::ifstream orderFile(orderFilePath);

		if (orderFile)
		{
			if (id == ++count)
			{
				cusOrder.displayOrderFromFile(orderFilePath);
				break;
			}
		}
	}
	customerFile.close();

	std::cout << "Mark order complete/pending? (y/N): ";
	char ch;
	std::cin >> ch;
	bool exit = false;
	if (std::toupper(ch) == 'Y')
	{
		std::cout << "ID: ";
		int orderItemId;
		std::cin >> orderItemId;
		cusOrder.markItemOrderComplete(orderFilePath, orderItemId);
	}
	else if (std::toupper(ch) == 'N')
	{
		exit = true;
	}
	else
	{
		std::cout << "Invalid input. Please enter 'y' or 'n'." << std::endl;
	}
	return exit;
}

void Admin::displayDiscountReqests()
{
	std::ifstream customerFile(CUSTOMER_FILE);

	std::string line;
	int count = 0;
	while (std::getline(customerFile, line))
	{
		int commaIndex1 = line.find(',');
		std::string cusUserName = line.substr(0, commaIndex1);
		std::string requestFilePath{ "RestaurantData/DiscountRequests/" + cusUserName + ".txt" };

		std::ifstream requestFile(requestFilePath);

		if (requestFile)
		{
			std::cout << ++count << '\t' << cusUserName << '\n';
		}

		requestFile.close();
	}

	customerFile.close();
}

void Admin::displayRegularCustomers()
{
	std::ifstream customerFile(CUSTOMER_FILE);

	std::string line;
	int count = 0;
	std::cout << "SN\t" << "Name\n";
	while (std::getline(customerFile, line))
	{
		int commaIndex1 = line.find(',');
		int commaIndex2 = line.find(',', commaIndex1 + 1);
		int commaIndex3 = line.find(',', commaIndex2 + 1);
		int commaIndex4 = line.find(',', commaIndex3 + 1);

		std::string customerName = line.substr(0, commaIndex1);
		bool isRegular = (line.substr(commaIndex4 + 1)) == "true" ? true : false;

		if (isRegular)
		{
			std::cout << count << '\t' << customerName << '\n';
		}
	}

	customerFile.close();
}

void Admin::approveRequest(int id)
{
	// create seperate file for seperate customer
}

void Admin::denyRequest(int id)
{
	std::string path;
	std::ifstream customerFile(CUSTOMER_FILE);

	std::string line;
	int count = 0;
	while (std::getline(customerFile, line))
	{
		int commaIndex1 = line.find(',');
		std::string cusUserName = line.substr(0, commaIndex1);
		std::string requestFilePath{ "RestaurantData/DiscountRequests/" + cusUserName + ".txt" };

		std::ifstream requestFile(requestFilePath);

		if (requestFile && ++count == id)
		{
			path = requestFilePath;
			break;
		}
		requestFile.close();
	}

	std::remove(path.c_str());
	customerFile.close();
}

bool Admin::mainMenuHandler()
{
		
	bool exit{ false };
	while (!exit)
	{
		
		char option = 0;
		int opt = option - '0';
		while (opt != DISPLAY_ORDERS && opt != DISPLAY_MENU && opt != EXIT_MENU && opt != DISPLAY_DISCOUNT_REQUESTS && opt != DISPLAY_REGULAR_CUSTOMERS) {
			
			system("cls");
			welcome("MainMenu");
			std::cout << "\n\n";
			box(" ");
			gotoxy(40, 9);
			std::cout << DISPLAY_ORDERS << " - DISPLAY_ORDER \n";
			gotoxy(40, 10);
			std::cout << DISPLAY_MENU <<  " - DISPLAY_MENU\n";
			gotoxy(40, 11);
			std::cout << DISPLAY_DISCOUNT_REQUESTS << " - DISPLAY_DISCOUNT_REQUESTS\n";
			gotoxy(40, 12);
			std::cout << DISPLAY_REGULAR_CUSTOMERS << " - DISPLAY_REGULAR_CUSTOMERS\n";
			gotoxy(40, 13);
			std::cout << EXIT_MENU << " - EXIT_MENU\n";
			option = _getch();
			opt = option - '0';
		}

		if (opt == DISPLAY_ORDERS)
		{
			system("cls");
			welcome("Orders Placed");
			displayCustomersWhoOrdered();

			gotoxy(40, 5);
			std::cout << "ID: ";
			int id;
			std::cin >> id;
			bool exit = false;
			while (!exit)
			{
				system("cls");
				exit = displayOrdersOfCustomer(id);
			}

			system("pause");
			// display orders
		}
		else if (opt == DISPLAY_DISCOUNT_REQUESTS)
		{
			system("cls");
			welcome("Discount Requests");

			displayDiscountReqests();

			std::cout << "Approve (A) || Deny (D) || Exit (E): ";
			char approveDeny{ };
			std::cin >> approveDeny;
			if (toupper(approveDeny) == 'A')
			{
				// do approve
				std::cout << "ID: ";
				int id;
				std::cin >> id;
				approveRequest(id);
			}
			else if (toupper(approveDeny) == 'D')
			{
				// do deny
				std::cout << "ID: ";
				int id;
				std::cin >> id;
				denyRequest(id);
			}
			else
			{
				continue;
			}

			system("pause");
		}
		else if (opt == DISPLAY_REGULAR_CUSTOMERS)
		{
			system("cls");
			welcome("Regular Customers");

			// display customers
			displayRegularCustomers();

			std::cout << "Add Regular Customer(y / n): ";
			char addNew;
			std::cin >> addNew;
			if (toupper(addNew) == 'Y')
			{
				std::cout << "do it!\n";
			}
			system("pause");
		}
		else if (opt == DISPLAY_MENU)
		{
			system("cls");

			welcome("Available Menus");
			//box(" ");
			// DISPLAY MENU
			MenuItem menu;
			gotoxy(40, 3);                                                //yo milauna baaki xa hai 
			menu.showMenu();
			std::cout << "\nDo you want to update menu?(y/N): ";
			char updateInput;
			std::cin >> updateInput;
			if (std::toupper(updateInput) == 'Y')
			{
				//system("cls");
				//welcome("Updating Menu");
				//box(" ");
				// update menu
				//gotoxy(40, 5);                                              //yo line ma ni gotoxy x coordinates aagadi gayena hera hai kasle herni ho 
				MenuItem newItem;
				newItem.inputData();
				menu.updateMenu(newItem);
				std::cout << "\n\nItem has been added succesfully...\n";
				Sleep(900);
				system("cls");
				welcome("Menu");
			}
			else
			{
				system("cls");
				gotoxy(0, 5);
				welcome("Heading towards MainMenu...");
				Sleep(900);
				system("cls");
				welcome("MainMenu");
				
				continue;
			}
		}
		else if (opt == EXIT_MENU)
		{
			system("cls");
			gotoxy(0, 5);
			welcome("Exiting...");
			Sleep(500);
			system("cls");
			gotoxy(0, 5);
			welcome("Heading towards LOGIN...");
			Sleep(600);

			
			break;
		}
		else
		{
			std::cout << "Please choose valid input!\n";
		}
	}
	return exit;
}