#include "Customer.h"

#include <iostream>
#include <string>
#include <fstream>

#include "MenuItem.h"
#include "Order.h"

std::string Customer::getUsername()
{
	return username;
}

void Customer::getUserInput()
{
	std::cout << "Enter username: ";
	std::cin >> username;
	std::cout << "Enter password: ";
	std::cin >> password;
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
	std::cout << "\nCreate Account\n";
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

	std::cout << "Enter username: ";
	std::cin >> username;
	std::cout << "Enter password: ";
	std::cin >> password;

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

			std::cout << tUsername << '\t' << tPassword << '\n';
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
	std::cout << "YOUR PROFILE\n";
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
		std::cout << "MAIN MENU\n";
		std::cout << DISPLAY_CUS_MENU << " - DISPLAY MENU\n";
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
		}
	}
	return exit;
}