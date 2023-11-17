
#pragma once
#include <string>
#include "MenuItem.h"

static const std::string INVENTORY_FILE{ "RestaurantData/Inventory.txt" };

enum InventoryMenuOptions {
	ZERO,
	SHOW_INVENTORY,
	ADD_ITEM,
	REMOVE_ITEM, 
	UPDATE_INVENTORY,
	EXIT_INVENTORY
};

class InventoryItem
{
protected:
	std::string inventoryItemName;
	int stock;
	int id;
	float inventoryItemPrice;
public:
	InventoryItem();
	int getId();
	int getMaxId();
	std::string getName();
	float getPrice();
	int getStock();
	/*std::string getItemName(int itemId);
	float getItemPrice(int itemId);
	int getItemStock(int itemId);*/
	bool menuHandler();
	void showInventory(); // just display the menu
	void inputData(); // data input for the menu item
	void inputId();
	void inputRestData();
	void inputNewData();
	//void displayItemDetails(int itemId);
	void updateInventory(InventoryItem newInventoryItem); // edits existing item or creates new one
	//void addInventory(InventoryItem newInventoryItem);
	void removeInventory(int itemId);
	void updateStock(InventoryItem item, int quantity);

	InventoryItem getItem(int itid);
};