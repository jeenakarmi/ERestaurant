#include "MenuItem.h"
#include "UIElems.h"
#include <iostream>
#include <fstream>
#include <string>
#include <string_view>
#include <iomanip>

MenuItem::MenuItem()
{
	id = 0;
	menuItemName = "";
	menuItemPrice = 0.00f;
}

int MenuItem::getId()
{
	return (id);
}

std::string MenuItem::getName()
{
	return (menuItemName);
}

float MenuItem::getPrice()
{
	return (menuItemPrice);
}

void MenuItem::showMenu()
{
	SetWindowSizeAndCentre(); // Center the console window

	std::ifstream inf;
	inf.open(MENU_FILE, std::ios::in);

	if (!inf)
	{
		std::cout << "File could not be open! FILE_NAME: " << MENU_FILE << '\n';
	}
	else
	{
		Title("Today's Menu", centerY - 15); // Center the "Menu" title
		std::cout<< std::endl;

		std::string line;
		std::vector<std::string> menuLines;

		// Read menu lines into a vector
		while (std::getline(inf, line))
		{
			menuLines.push_back(line);
		}

		// Calculate padding for centering menu items
		int consoleWidth = GetWindowSize().X;
		int padding = (consoleWidth - 35) / 2;
		int separatorPadding = (consoleWidth - 40) / 2;

		std::cout << std::setw(padding) << ' ';
		std::cout << std::setw(5) << std::left << "ID"
			<< std::setw(20) << std::left << "Item"
			<< std::setw(10) << std::left << "Price" << std::endl;

		std::cout << std::setfill(' ') << std::setw(separatorPadding) << ' '
			<< std::setw(5) << std::setfill('-') << std::left << '-'
			<< std::setw(20) << std::left << '-'
			<< std::setw(10) << std::left << '-' << std::setfill(' ') << std::setw(separatorPadding) << ' '
			<< std::endl;


		for (const std::string& menuItem : menuLines)
		{
			int id;
			std::string menuItemName;
			float menuItemPrice;
			int commaIndex1 = menuItem.find(",");
			int commaIndex2 = menuItem.find(",", commaIndex1 + 1);
			id = std::stoi(menuItem.substr(0, commaIndex1));
			menuItemName = menuItem.substr(commaIndex1 + 1, commaIndex2 - commaIndex1 - 1);
			menuItemPrice = std::stof(menuItem.substr(commaIndex2 + 1));

			// Center-align the menu items
			std::cout << std::setw(padding) << ' ';
			std::cout << std::setw(5) << std::left << id
				<< std::setw(20) << std::left << menuItemName
				<< std::setw(10) << std::left << menuItemPrice << std::endl;
		}

	}
}
void MenuItem::inputData()
{
	std::cout << "\nUpdate Or Add Item\n";
	std::cout << "\n";
	std::cout << "Enter item id: ";
	std::cin >> id;
	std::cout << "Enter item name: ";
	std::getline(std::cin >> std::ws, menuItemName);
	std::cout << "Enter item price: ";
	std::cin >> menuItemPrice;
}

void MenuItem::updateMenu(MenuItem newMenuItem)
{
	std::ifstream inf;
	inf.open(MENU_FILE);

	std::ofstream outf;
	outf.open("RestaurantData/temp.txt", std::ios::app);

	bool entryFound{ false }; // if the provided menu item is found and is there to be updated

	if (inf.is_open())
	{
		std::string line;
		while (std::getline(inf, line))
		{
			int tID;
			std::string tName;
			float tPrice;
			int commaIndex1 = line.find(","); // "find" returns unsigned int while we're storing in signed int so possible loss of data
			int commaIndex2 = line.find(",", commaIndex1 + 1);

			tID = std::stoi(line.substr(0, commaIndex1));
			tName = line.substr(commaIndex1 + 1, commaIndex2 - commaIndex1 - 1);
			tPrice = std::stof(line.substr(commaIndex2 + 1));

			if (tID == newMenuItem.getId())
			{
				outf << newMenuItem.getId() << ',' << newMenuItem.getName() << ',' << newMenuItem.getPrice() << '\n';
				entryFound = true;
			}
			else
			{
				outf << tID << ',' << tName << ',' << tPrice << '\n';
			}
		}

		if (!entryFound)
		{
			outf << newMenuItem.getId() << ',' << newMenuItem.getName() << ',' << newMenuItem.getPrice() << '\n';
		}

		inf.close();
		outf.close();

		std::remove("RestaurantData/Menu.txt");
		std::rename("RestaurantData/temp.txt", "RestaurantData/Menu.txt");
	}
}

MenuItem MenuItem::getItem(int itid)
{
	MenuItem theItem;
	std::ifstream inf;
	inf.open(MENU_FILE);

	if (inf.is_open())
	{
		std::string line;
		while (std::getline(inf, line))
		{
			int itemid;
			std::string name;
			float price;

			int commaIndex1 = line.find(",");
			int commaIndex2 = line.find(",", commaIndex1 + 1);

			itemid = std::stoi(line.substr(0, commaIndex1));
			name = line.substr(commaIndex1 + 1, commaIndex2 - commaIndex1 - 1);
			price = std::stof(line.substr(commaIndex2 + 1));

			if (itid == itemid)
			{
				theItem.id = itemid;
				theItem.menuItemName = name;
				theItem.menuItemPrice = price;
			}
		}
	}
	inf.close();
	return theItem;
}