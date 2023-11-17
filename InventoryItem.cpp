#include "InventoryItem.h"
#include "MenuItem.h"
#include "UIElems.h"
#include <iostream>
#include "conio.h"
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

float InventoryItem::getPrice()
{
	return(inventoryItemPrice);
}
int InventoryItem::getStock()
{
	return(stock);
}

int InventoryItem::getMaxId()
{
	std::ifstream inf;
	inf.open(INVENTORY_FILE);
	int id;
	if (inf.is_open())
	{
		std::string line;
		while (std::getline(inf, line))
		{
			int commaIndex1 = line.find(",");
			//int commaIndex2 = line.find(",", commaIndex1 + 1);

			id = std::stoi(line.substr(0, commaIndex1));
		}
	}
	inf.close();
	return id;
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
		std::cout << std::setw(5) << std::left << "ID"
			<< std::setw(20) << std::left << "Item"
			<< std::setw(10) << std::left << "Price"
			<< std::setw(10) << std::left << "Stock" << std::endl;

		std::cout << std::setfill(' ') << std::setw(separatorPadding) << ' '
			<< std::setw(5) << std::setfill('-') << std::left << '-'
			<< std::setw(20) << std::left << '-'
			<< std::setw(10) << std::left << '-'
			<< std::setw(10) << std::left << '-' << std::setfill(' ') << std::setw(separatorPadding) << ' '
			<< std::endl;


		for (const std::string& inventoryItem : inventoryLines)
		{
			int id;
			std::string inventoryItemName;
			int stock;
			float inventoryItemPrice;
			int commaIndex1 = inventoryItem.find(",");
			int commaIndex2 = inventoryItem.find(",", commaIndex1 + 1);
			int commaIndex3 = inventoryItem.find(",", commaIndex2 + 1);

			id = std::stoi(inventoryItem.substr(0, commaIndex1));
			inventoryItemName = inventoryItem.substr(commaIndex1 + 1, commaIndex2 - commaIndex1 - 1);
			inventoryItemPrice = std::stof(inventoryItem.substr(commaIndex2 + 1, commaIndex3 - commaIndex2 -1));
			stock = std::stoi(inventoryItem.substr(commaIndex3 + 1));

			// Center-align the menu items
			std::cout << std::setw(padding) << ' ';
			std::cout << std::setw(5) << std::left << id
				<< std::setw(20) << std::left << inventoryItemName
				<< std::setw(10) << std::left << inventoryItemPrice
				<< std::setw(10) << std::left << stock << std::endl;
		}
	}
}
void InventoryItem::inputData()
{
	std::cout << "Enter item id: ";
	std::cin >> id;
	std::cout << "Enter item name: ";
	std::getline(std::cin >> std::ws, inventoryItemName);
	std::cout << "Enter item price: ";
	std::cin >> inventoryItemPrice;
	std::cout << "Enter item stock: ";
	std::cin >> stock;
}
void InventoryItem::inputId()
{
	std::cout << "Enter item id: ";
	std::cin >> id;
}
void InventoryItem::inputRestData()
{
	std::cout << "Enter item name: ";
	std::getline(std::cin >> std::ws, inventoryItemName);
	std::cout << "Enter item price: ";
	std::cin >> inventoryItemPrice;
	std::cout << "Enter item stock: ";
	std::cin >> stock;
}
void InventoryItem::inputNewData()
{
	std::cout << "Enter new item name: ";
	std::getline(std::cin >> std::ws, inventoryItemName);
	std::cout << "Enter item price: ";
	std::cin >> inventoryItemPrice;
	std::cout << "Enter item stock: ";
	std::cin >> stock;
}

void InventoryItem::updateStock(InventoryItem item, int quantity)
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
			
			int Stock;
			int ID;
			std::string Name;
			float Price;
			int commaIndex1 = line.find(","); // "find" returns unsigned int while we're storing in signed int so possible loss of data
			int commaIndex2 = line.find(",", commaIndex1 + 1);
			int commaIndex3 = line.find(",", commaIndex2 + 1);

			ID = std::stoi(line.substr(0, commaIndex1));
			Name = line.substr(commaIndex1 + 1, commaIndex2 - commaIndex1 - 1);
			Price = std::stof(line.substr(commaIndex2 + 1, commaIndex3 - commaIndex2 - 1));
			Stock = std::stoi(line.substr(commaIndex3 + 1));
			if (item.getId() == ID) {
				Stock -= quantity;
				if (Stock < 0) {
					Stock = 0;  // Ensure Stock does not go below zero
					outf << ID << ',' << Name << ',' << Price << ',' << Stock << '\n';
				}
				else
				{
					outf << ID << ',' << Name << ',' << Price << ',' << Stock << '\n';
				}
			}
			else
			{
				outf << ID << ',' << Name << ',' << Price << ',' << Stock << '\n';
			}
		}
		inf.close();
		outf.close();

		std::remove("RestaurantData/Inventory.txt");
		std::rename("RestaurantData/temp.txt", "RestaurantData/Inventory.txt");
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
			int tID, tStock;
			std::string tName;
			float tPrice;
			int commaIndex1 = line.find(","); // "find" returns unsigned int while we're storing in signed int so possible loss of data
			int commaIndex2 = line.find(",", commaIndex1 + 1);
			int commaIndex3 = line.find(",", commaIndex2 + 1);
			tID = std::stoi(line.substr(0, commaIndex1));
			tName = line.substr(commaIndex1 + 1, commaIndex2 - commaIndex1 - 1);
			tPrice = std::stof(line.substr(commaIndex2 + 1, commaIndex3 - commaIndex2 - 1));
			tStock = std::stoi(line.substr(commaIndex3 + 1));

			if (tID == newInventoryItem.getId())
			{
				outf << newInventoryItem.getId() << ',' << newInventoryItem.getName() << ',' << newInventoryItem.getPrice() << ',' << newInventoryItem.getStock() << '\n';
				entryFound = true;
			}
			else
			{
				outf << tID << ',' << tName << ',' << tPrice << ',' << tStock <<'\n';
			}
		}

		if (!entryFound)
		{
			outf << newInventoryItem.getId() << ',' << newInventoryItem.getName() << ',' << newInventoryItem.getPrice() << ',' << newInventoryItem.getStock() << '\n';
		}

		inf.close();
		outf.close();

		std::remove("RestaurantData/Inventory.txt");
		std::rename("RestaurantData/temp.txt", "RestaurantData/Inventory.txt");
	}
}
void InventoryItem::removeInventory(int itemId) 
{
	std::ifstream inf;
	inf.open(INVENTORY_FILE);

	std::ofstream outf;
	outf.open("RestaurantData/temp.txt", std::ios::app);

	bool entryFound{ false }; // if the provided menu item is found and is there to be updated

	if (inf.is_open())
	{
		int newId = 1;
		std::string line;
		while (std::getline(inf, line))
		{
			int tID,tStock;
			std::string tName;
			float tPrice;
			int commaIndex1 = line.find(","); // "find" returns unsigned int while we're storing in signed int so possible loss of data
			int commaIndex2 = line.find(",", commaIndex1 + 1);
			int commaIndex3 = line.find(",", commaIndex2 + 1);
			tID = std::stoi(line.substr(0, commaIndex1));
			tName = line.substr(commaIndex1 + 1, commaIndex2 - commaIndex1 - 1);
			tPrice = std::stof(line.substr(commaIndex2 + 1, commaIndex3 - commaIndex2 - 1));
			tStock = std::stoi(line.substr(commaIndex3 + 1));
			if (tID != itemId)
			{
				outf << newId << ',' << tName << ',' << tPrice << ',' << tStock << '\n';
				newId++;
			}
		}

		inf.close();
		outf.close();

		std::remove("RestaurantData/Inventory.txt");
		std::rename("RestaurantData/temp.txt", "RestaurantData/Inventory.txt");
	}
}
InventoryItem InventoryItem::getItem(int itid)
{
	InventoryItem theItem;
	std::ifstream inf;
	inf.open(INVENTORY_FILE);

	if (inf.is_open())
	{
		std::string line;
		while (std::getline(inf, line))
		{
			int itemid;
			std::string name;
			float price;
			int stocks;

			int commaIndex1 = line.find(",");
			int commaIndex2 = line.find(",", commaIndex1 + 1);
			int commaIndex3 = line.find(",", commaIndex2 + 1);
			itemid = std::stoi(line.substr(0, commaIndex1));
			name = line.substr(commaIndex1 + 1, commaIndex2 - commaIndex1 - 1);
			price = std::stof(line.substr(commaIndex2 + 1, commaIndex3 - commaIndex2 - 1));
			stocks = std::stoi(line.substr(commaIndex3 + 1));

			if (itid == itemid)
			{
				theItem.id = itemid;
				theItem.inventoryItemName = name;
				theItem.inventoryItemPrice = price;
				theItem.stock = stocks;
			}
		}
	}
	inf.close();
	return theItem;
}


bool InventoryItem::menuHandler()
{
	bool exit{ false };
	while (!exit)
	{
		char option = 0;
		int opt = option - '0';
		while (opt != SHOW_INVENTORY && opt != ADD_ITEM && opt != REMOVE_ITEM && opt != UPDATE_INVENTORY && opt != EXIT_INVENTORY) {
			system("cls");
			Title("INVENTORY", centerY - 4);
			std::cout << "\n\n";
			MenuItems({ "1: SHOW INVENTORY", "2: ADD ITEM", "3: REMOVE ITEM", "4: UPDATE INVENTORY", "5: EXIT" });
			option = _getch();
			opt = option - '0';
		}
		if (opt == SHOW_INVENTORY)
		{
			system("cls");
			InventoryItem inventory;
			inventory.showInventory();
			system("pause");
		}
		else if (opt == ADD_ITEM)
		{
			InventoryItem inventory, newItem;
			system("cls");
			inventory.showInventory();
			std::cout << "\nAdd Item\n";
			std::cout << "\n";
			//std::cout << "Max id in inventory: " << inventory.getMaxId();
			newItem.inputId();
			if (newItem.getId() <= getMaxId())
			{
				std::cout << "\n\nInvalid ID...\nEnter ID not present above...\n";
			}
			else if ((getMaxId() + 1) != newItem.getId())
			{
				std::cout << "\n\nEnter valid ID...\nID must be in chronology...\n";
			}
			else
			{
				newItem.inputRestData();
				inventory.updateInventory(newItem);
				std::cout << "\n\nItem has been added succesfully...\n";
			}
			
			system("pause");
		}
		else if (opt == REMOVE_ITEM)
		{
			InventoryItem inventory, currItem;
			int itemId;
			system("cls");
			inventory.showInventory();
			std::cout << "\nRemove Item\n";
			std::cout << "\n";
			currItem.inputId();
			if (currItem.getId() > getMaxId() || currItem.getId() == 0)
			{
				std::cout << "\n\nEnter valid ID...\n";
			}
			else
			{
				currItem = currItem.getItem(currItem.getId());
				std::cout << " Current Item: " << currItem.inventoryItemName << "\n";
				std::cout << " Current Price: " << currItem.inventoryItemPrice << "\n";
				std::cout << " Current Stock: " << currItem.stock << "\n\n";
				currItem.removeInventory(currItem.getId());
				std::cout << "\n\nItem has been removed succesfully...\n";
			}
			system("pause");
		}
		else if (opt == UPDATE_INVENTORY)
		{
			
			InventoryItem inventory, currItem;
			system("cls");
			inventory.showInventory();
			std::cout << "\nUpdate Item\n";
			std::cout << "\n";
			//std::cout << "Max id in inventory: " << inventory.getMaxId();
			currItem.inputId();
			if (currItem.getId() > getMaxId() || currItem.getId() == 0)
			{
				std::cout << "\n\nInvalid ID...\nEnter ID from above...\n";
			}
			else
			{
				currItem = currItem.getItem(currItem.getId());
				std::cout << " Current Item: " << currItem.inventoryItemName << "\n";
				std::cout << " Current Price: " << currItem.inventoryItemPrice << "\n";
				std::cout << " Current Stock: " << currItem.stock << "\n\n";
				currItem.inputNewData();
				inventory.updateInventory(currItem);
				std::cout << "\n\nItem has been added succesfully...\n";
			}
			system("pause");
		}
		else if (opt == EXIT_INVENTORY)
		{
			system("cls");
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