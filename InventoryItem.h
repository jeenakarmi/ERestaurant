
#pragma once
#include <string>


static const std::string INVENTORY_FILE{ "RestaurantData/Inventory.txt" };

class InventoryItem
{
protected:
	std::string inventoryItemName;
	int stock;
	int id;
public:
	InventoryItem();
	int getId();
	std::string getName();
	int getStock();
	void showInventory(); // just display the menu
	void inputData(); // data input for the menu item
	void updateInventory(InventoryItem newInventoryItem); // edits existing item or creates new one
	void updateStock(int quantity);

	InventoryItem getItem(int itid);
};