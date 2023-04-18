#include "Customer.h"

#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>
#include <conio.h>

#include "MenuItem.h"
#include "Order.h"
#include "welcome.h"
#include "box.h"

/*
const char DISPLAY_MENU = '0';
const char PLACE_ORDERS = '1';
const char MY_ORDER = '2';
const char MY_PROFILES = '3';
const char EXITS = '4';
*/

std::string Customer::getUsername()
{
	return username;
}

void Customer::getUserInput()
{
	std::cout << "Enter username: ";
	std::cin >> username;
	std::cout << "Enter password: ";


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
	std::cout << '\n';
	std::cout << "Enter phone: ";
	std::cin >> phone;
	std::cout << "Enter email: ";
	std::cin >> email;
}

bool Customer::isNewUser()
{
	std::ifstream inf;
	inf.open(CUSTOMER_FILE);

	bool isNew{ true };
	
	if (inf.is_open())
	{
		std::string line;
		while (std::getline(inf, line))
		{
			std::string tUsername, tPhone, tEmail;
			int commaIndex1 = line.find(",");
			int commaIndex2 = line.find(",", commaIndex1 + 1);
			int commaIndex3 = line.find(",", commaIndex2 + 1);

			tUsername = line.substr(0, commaIndex1);
			tPhone = line.substr(commaIndex2 + 1, commaIndex3 - commaIndex2 - 1);
			tEmail = line.substr(commaIndex3 + 1);

			if (username == tUsername || email == tEmail || phone == tPhone)
			{
				if (username == tUsername)
				{
					std::cout << "Username already taken!\n";
				}
				else if (email == tEmail)
				{
					std::cout << "Email already taken!\n";
				}
				else if (phone == tPhone)
				{
					std::cout << "Phone already taken!\n";
				}
				isNew = false;
			}
		}
	}
	inf.close();
	return isNew;
}

void Customer::createAccount()
{

	std::string text = "CREATE ACCOUNT";  // admin login validation page
	const int boxWidth = 100;  // Define the width of the box
	int padding = (boxWidth - text.length()) / 2;   // Calculate the padding required to center the text
	std::cout << std::setfill('=') << std::setw(boxWidth) << "" << std::endl;	// Display the box
	std::cout << std::setfill(' ') << std::setw(padding) << "" << text << std::setw(padding) << "" << std::endl;	// Display the text with padding
	std::cout << std::setfill('=') << std::setw(boxWidth) << "" << std::endl;	// Display the bottom of the box
	//std::cout << "\nCreate Account\n";
	std::ofstream outf;
	outf.open(CUSTOMER_FILE, std::ios::app); 

	bool allGood{ false };
	while (!allGood)
	{
		getUserInput();
		if (isNewUser())
		{
			allGood = true;
		}
	}
	
	outf << username << ',' << password << ',' << phone << ',' << email << '\n';

	outf.close();
}

bool Customer::validateLogin()
{
	bool isValid{ false };

	std::cout << "\n\n";
	box(" ");
	gotoxy(40, 9);
	std::cout << "Enter username: ";
	std::cin >> username;
	gotoxy(40, 10);
	std::cout << "Enter password: ";
	//Enter password for validation
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

	std::ifstream inf;
	inf.open(CUSTOMER_FILE);

	if (inf.is_open())
	{
		std::string line;
		while (std::getline(inf, line))
		{
			std::string tUsername, tPassword, tPhone, tEmail;
			
			int commaIndex1 = line.find(",");
			int commaIndex2 = line.find(",", commaIndex1 + 1);
			int commaIndex3 = line.find(",", commaIndex2 + 1);

			tUsername = line.substr(0, commaIndex1);
			tPassword = line.substr(commaIndex1 + 1, commaIndex2 - commaIndex1 - 1);
			tPhone = line.substr(commaIndex2 + 1, commaIndex3 - commaIndex2 - 1);
			tEmail = line.substr(commaIndex3 + 1);

			if (username == tUsername && password == tPassword)
			{
				isValid = true;
				phone = tPhone;
				email = tEmail;
			}
		}
	}
	return isValid;
}

void Customer::displayProfile()
{
	system("cls");
	welcome("YOUR PROFILE");
	std::cout << "Username: " << username << '\n';
	std::cout << "Password: " << password << '\n';
	std::cout << "Phone: " << phone << '\n';
	std::cout << "Email: " << email << '\n';
}

bool Customer::mainMenuHandler()
{
	bool exit{ false };
	while (!exit)
	{
		system("cls");
		
		welcome("Mainmenu");

		char option = '\0';
		int opt = option - '0';

		std::cout << "\n\n";
		box(" ");
		while (opt != DISPLAY_CUS_MENU && opt != PLACE_ORDER && opt != MY_ORDERS && opt != MY_PROFILE && opt != EXIT) {
			gotoxy(40, 8);
			std::cout << "0 - DISPLAY MENU\n";
			gotoxy(40, 9);
			std::cout << "1 - PLACE ORDER\n";
			gotoxy(40, 10);
			std::cout << "2 - MY ORDER\n";
			gotoxy(40, 11);
			std::cout << "3 - MY PROFILE\n";
			gotoxy(40, 12);
			std::cout << "4 - EXIT\n";
			option = _getch();
			opt = option - '0';

		}

		if (opt == DISPLAY_CUS_MENU) {
			MenuItem menu;
			system("CLS");
			welcome("TODAY STUFFS");
			std::cout << "\n\n";
			box(" ");

			gotoxy(5, 5);
			menu.showMenu();
			std::cout << std::endl;
			system("pause");
		}
		else if (opt == PLACE_ORDER) {
			system("cls");
			
			Order order;
			bool orderPlaced = order.placeOrder(*this);
			if (!orderPlaced)
			{
				std::cout << "Failed to place Order!\n";
			}
			else
			{
				std::cout << "Order placed! Check out on \"MY ORDERS\"\n";
				system("pause");
			}
		}		
		/*
		else if (opt == MY_ORDERS) {
		
			// lekhna baki xa
			std::cout << MY_ORDERS ;
		}
		*/
		else if (opt == MY_PROFILE) {
			displayProfile();
			std::cout << std::endl;
			system("pause");
		}

		else if (opt == EXIT) {
			exit = true;
		}

		else
		{
			std::cout << "Please enter the provided options!\n";
		}
		
		/*std::cout << DISPLAY_CUS_MENU << " - DISPLAY MENU\n";
		std::cout << PLACE_ORDER << " - PLACE ORDER\n";
		std::cout << MY_ORDERS << " - MY ORDERS\n";
		std::cout << MY_PROFILE << " - MY PROFILE\n";
		std::cout << EXIT << " - EXIT\n";
		
		int input;
		std::cout << "Input: ";
		std::cin >> input;

		if (input == EXIT)
		{
			exit = true;
		}
		else if (input == DISPLAY_CUS_MENU)
		{
			MenuItem menu;
			menu.showMenu();
			std::cout << std::endl;
			system("pause");
		}
		else if (input == PLACE_ORDER)
		{
			Order order;
			bool orderPlaced = order.placeOrder(*this);
			if (!orderPlaced)
			{
				std::cout << "Failed to place Order!\n";
			}
			else
			{
				std::cout << "Order placed! Check out on \"MY ORDERS\"\n";
				system("pause");
			}
		}
		else if (input == MY_PROFILE)
		{
			displayProfile();
			std::cout << std::endl;
			system("pause");
		}
		else
		{
			std::cout << "Please enter the provided options!\n";
		}*/
	}
	return exit;
}