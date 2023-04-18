#ifndef ADMIN
#define ADMIN

#include <iostream>
#include <fstream>
#include <string>
#include <string_view>
#include <chrono>
#include <thread>

static const std::string ADMIN_FILE = "UserData/ADMIN.txt";

enum AdminMainMenuOptions {
	DISPLAY_ORDERS,
	DISPLAY_MENU,
	EXIT_MENU
};

class Admin
{
	std::string username;
	std::string password = "";
public:
	void getAdminData();
	bool validateLogin(); // string_view makes string read only to save memory
	std::string getUserName();
	bool mainMenuHandler();
};

#endif // !ADMIN
