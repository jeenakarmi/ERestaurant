#include "Admin.h"
#include <iostream>
#include <fstream>
#include <string>
#include <string_view>
#include <conio.h>

#include "MenuItem.h"
#include "box.h"

void Admin::getAdminData()
{
	box(" ");
	gotoxy(30, 6);
	std::cout << "Enter username: ";
	//gotoxy(45, 4);
	std::cin >> username;
	gotoxy(30, 7);
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

bool Admin::mainMenuHandler()
{
	bool exit{ false };
	while (!exit)
	{
		const char DISPLAY_ORDER = '0';
		const char DISPLAY_MENU = '1';
		const char EXIT_MENU = '2';
		char option = 0;
		while (option != DISPLAY_ORDER && option != DISPLAY_MENU && option != EXIT_MENU) {
			std::cout << "0 - DISPLAY_ORDER \n";
			std::cout << "1 - DISPLAY_MENU\n";
			std::cout << "2 - EXIT_MENU\n";

			option = _getch();
		}


		/*std::cout << DISPLAY_ORDERS << " - DISPLAY_ORDERS\n";
		std::cout << DISPLAY_MENU << " - DISPLAY_MENU\n";
		std::cout << "2 - Exit Menu\n";

		int input{};
		std::cout << "Input: ";
		std::cin >> input;
		*/
		if (option == DISPLAY_ORDER)
		{
			// display orders
		}
		else if (option == DISPLAY_MENU)
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
		else if (option == EXIT_MENU)
		{
			system("cls");
			
			break;
		}
		else
		{
			std::cout << "Please choose valid input!\n";
		}
	}
	return exit;
}