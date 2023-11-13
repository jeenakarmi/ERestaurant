#ifndef MENU_ITEM
#define MENU_ITEM

#include "Customer.h"

//static const std::string INVENTORY_FILE{ "RestaurantData/Menu.txt" };

class MenuItem
{
protected:
	std::string menuItemName;
	float menuItemPrice;
	int id;
public:
	MenuItem();
	int getId();
	std::string getName();
	float getPrice();
	void showMenu(); // just display the menu
	void inputData(); // data input for the menu item
	void updateMenu(MenuItem newMenuItem); // edits existing item or creates new one

	MenuItem getItem(int itid);
};

#endif // !MENU_ITEM
