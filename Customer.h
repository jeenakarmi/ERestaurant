#pragma once

#include <string>

static const std::string CUSTOMER_FILE{ "UserData/CUSTOMER.txt" };
static const std::string CUSTOMER_TEMP_FILE{ "UserData/CustomerTemp.txt" };

enum CustomerMainMenuOptions
{
	DISPLAY_CUS_MENU,
	PLACE_ORDER,
	MY_ORDERS,
	MY_PROFILE,
	EXIT
};

class Customer
{
	std::string username;
	std::string password;
	std::string phone;
	std::string email;
	int id;
public:
	Customer()
	{
		username = "";
		password = "";
		phone = "";
		email = "";
	}
	std::string getUsername();
	std::string getUserPhone();
	void getUserInput();
	bool isNewUser();
	void createAccount();
	bool validateLogin();
	void displayProfile();
	bool mainMenuHandler();
};