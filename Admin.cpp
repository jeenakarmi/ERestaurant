#include "Admin.h"
#include <iostream>
#include <fstream>
#include <string>
#include <string_view>
#include <conio.h>

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


bool Admin::mainMenuHandler()
{
		
	bool exit{ false };
	while (!exit)
	{
		
		char option = 0;
		int opt = option - '0';
		while (opt != DISPLAY_ORDERS && opt != DISPLAY_MENU && opt != EXIT_MENU) {
			
			system("cls");
			welcome("MainMenu");
			std::cout << "\n\n";
			box(" ");
			gotoxy(40, 9);
			std::cout << "0 - DISPLAY_ORDER \n";
			gotoxy(40, 10);
			std::cout << "1 - DISPLAY_MENU\n";
			gotoxy(40, 11);
			std::cout << "2 - EXIT_MENU\n";
			option = _getch();
			opt = option - '0';
		}


		/*std::cout << DISPLAY_ORDERS << " - DISPLAY_ORDERS\n";
		std::cout << DISPLAY_MENU << " - DISPLAY_MENU\n";
		std::cout << "2 - Exit Menu\n";

		int input{};
		std::cout << "Input: ";
		std::cin >> input;
		*/
		if (opt == DISPLAY_ORDERS)
		{
			system("cls");
			welcome("Orders Placed");
			displayCustomersWhoOrdered();

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