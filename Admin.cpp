#include "Admin.h"
#include <iostream>
#include <fstream>
#include <string>
#include <string_view>

#include "MenuItem.h"

void Admin::getAdminData()
{
	std::cout << "Enter username: ";
	std::cin >> username;
	std::cout << "Enter password: ";
	std::cin >> password;
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

bool Admin::mainMenuHandler()
{
	bool exit{ false };
	while (!exit)
	{
		std::cout << DISPLAY_ORDERS << " - DISPLAY_ORDERS\n";
		std::cout << DISPLAY_MENU << " - DISPLAY_MENU\n";
		std::cout << "2 - Exit Menu\n";

		int input{};
		std::cout << "Input: ";
		std::cin >> input;

		if (input == DISPLAY_ORDERS)
		{
			// display orders
		}
		else if (input == DISPLAY_MENU)
		{
			// DISPLAY MENU
			MenuItem menu;
			menu.showMenu();
			std::cout << "\nDo you want to update menu?(y/N): ";
			char updateInput;
			std::cin >> updateInput;
			if (std::toupper(updateInput) == 'Y')
			{
				// update menu
				MenuItem newItem;
				newItem.inputData();
				menu.updateMenu(newItem);
			}
			else
			{
				continue;
			}
		}
		else if (input == 2)
		{
			break;
		}
		else
		{
			std::cout << "Please choose valid input!\n";
		}
	}
	return exit;
}