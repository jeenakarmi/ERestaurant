#include "InventoryItem.h"
#include "UIElems.h"
#include <iostream>
#include <fstream>
#include <string>
#include <string_view>
#include <iomanip>

InventoryItem::InventoryItem()
{
	id = 0;
	inventoryItemName = "";
	stock = 0;
}

int InventoryItem::getId()
{
	return(id);
}

std::string InventoryItem::getName()
{
	return(inventoryItemName);
}

int InventoryItem::getStock()
{
	return(stock);
}

void InventoryItem::showInventory()
{
	SetWindowSizeAndCentre(); // Center the console window

	std::ifstream inf;
	inf.open(INVENTORY_FILE, std::ios::in);

	if (!inf)
	{
		std::cout << "File could not be open! FILE_NAME: " << INVENTORY_FILE << '\n';
	}
	else
	{
		Title("Inventory", centerY - 15); // Center the "Menu" title
		std::cout << std::endl;

		std::string line;
		std::vector<std::string> inventoryLines;

		// Read menu lines into a vector
		while (std::getline(inf, line))
		{
			inventoryLines.push_back(line);
		}

		// Calculate padding for centering menu items
		int consoleWidth = GetWindowSize().X;
		int padding = (consoleWidth - 35) / 2;
		int separatorPadding = (consoleWidth - 40) / 2;

		std::cout << std::setw(padding) << ' ';
		std::cout << std::setw(5) << std::left << "SN"
			<< std::setw(20) << std::left << "Item"
			<< std::setw(10) << std::left << "Stock" << std::endl;

		std::cout << std::setfill(' ') << std::setw(separatorPadding) << ' '
			<< std::setw(5) << std::setfill('-') << std::left << '-'
			<< std::setw(20) << std::left << '-'
			<< std::setw(10) << std::left << '-' << std::setfill(' ') << std::setw(separatorPadding) << ' '
			<< std::endl;


		for (const std::string& inventoryItem : inventoryLines)
		{
			int id;
			std::string inventoryItemName;
			float inventoryItemPrice;
			int commaIndex1 = inventoryItem.find(",");
			int commaIndex2 = inventoryItem.find(",", commaIndex1 + 1);
			id = std::stoi(inventoryItem.substr(0, commaIndex1));
			inventoryItemName = inventoryItem.substr(commaIndex1 + 1, commaIndex2 - commaIndex1 - 1);
			inventoryItemPrice = std::stof(inventoryItem.substr(commaIndex2 + 1));

			// Center-align the menu items
			std::cout << std::setw(padding) << ' ';
			std::cout << std::setw(5) << std::left << id
				<< std::setw(20) << std::left << inventoryItemName
				<< std::setw(10) << std::left << inventoryItemPrice << std::endl;
		}

	}
}
void InventoryItem::inputData()
{
	std::cout << "\nUpdate Or Add Item\n";
	std::cout << "\n";
	std::cout << "Enter item id: ";
	std::cin >> id;
	std::cout << "Enter item name: ";
	std::getline(std::cin >> std::ws, inventoryItemName);
	std::cout << "Enter item price: ";
	std::cin >> stock;
}

void InventoryItem::updateStock(int quantity)
{
	stock -= quantity;
	if (stock < 0) {
		stock = 0;  // Ensure stock does not go below zero
	}
}

void InventoryItem::updateInventory(InventoryItem newInventoryItem)
{
	std::ifstream inf;
	inf.open(INVENTORY_FILE);

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

			if (tID == newInventoryItem.getId())
			{
				outf << newInventoryItem.getId() << ',' << newInventoryItem.getName() << ',' << newInventoryItem.getStock() << '\n';
				entryFound = true;
			}
			else
			{
				outf << tID << ',' << tName << ',' << tPrice << '\n';
			}
		}

		if (!entryFound)
		{
			outf << newInventoryItem.getId() << ',' << newInventoryItem.getName() << ',' << newInventoryItem.getStock() << '\n';
		}

		inf.close();
		outf.close();

		std::remove("RestaurantData/Inventory.txt");
		std::rename("RestaurantData/temp.txt", "RestaurantData/Inventory.txt");
	}
}
