#include "Customer.h"

#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>
#include <conio.h>
#include<regex>

#include "MenuItem.h"
#include "Order.h"
#include "welcome.h"
#include "box.h"

bool Emailcheck(std::string email);
bool isValidPhoneNumber(std::string phone);
/*
const char DISPLAY_MENU = '0';
const char PLACE_ORDERS = '1';
const char MY_ORDER = '2';
const char MY_PROFILES = '3';
const char EXITS = '4';
*/

std::string Customer::getUsername()
{
	return username;
}

std::string Customer::getUserPhone()
{
	return phone;
}

void Customer::getUserInput()
{
	std::cout << "Enter username: ";
	std::cin >> username;
	std::cout << "Enter password: ";


	//Enter password for new customer
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
	std::cout << '\n';

	while (true)
	{

		std::cout << "Enter phonenumber: +977-98";
		std::cin >> phone;
		if (!isValidPhoneNumber(phone))
		{
			std::cout << "\nEnter valid phonenumber \n";
			continue;
		}
		break;
	}
	
	while (true)
	{

		std::cout << "Enter email: ";
		std::cin >> email;
		if (!Emailcheck(email))
		{
			std::cout << "\nEnter valid email \n";
			continue;
		}
		break;
	}
}

bool isValidPhoneNumber(std::string phone) {
	const std::regex pattern4("\\d{8}"); // regular expression pattern for 10-digit integer phone number
	return regex_match(phone, pattern4); // returns true if the phone number matches the pattern
}


bool Emailcheck(std::string email)
{
	const std::regex pattern1("(\\w+)(\\.|)?(\\w*)@gmail(\\.com)+");
	const std::regex pattern2("(\\w+)(\\.|)?(\\w*)@yahoo(\\.com)+");
	const std::regex pattern3("(\\w+)(\\.|)?(\\w*)@khec(\\.np)+");
	return regex_match(email, pattern1) || regex_match(email, pattern2) || regex_match(email, pattern3);
}
bool Customer::isNewUser()
{
	std::ifstream inf;
	inf.open(CUSTOMER_FILE);

	bool isNew{ true };
	
	if (inf.is_open())
	{
		std::string line;
		while (std::getline(inf, line))
		{
			std::string tUsername, tPhone, tEmail;
			int commaIndex1 = line.find(",");
			int commaIndex2 = line.find(",", commaIndex1 + 1);
			int commaIndex3 = line.find(",", commaIndex2 + 1);

			tUsername = line.substr(0, commaIndex1);
			tPhone = line.substr(commaIndex2 + 1, commaIndex3 - commaIndex2 - 1);
			tEmail = line.substr(commaIndex3 + 1);

			if (username == tUsername || email == tEmail || phone == tPhone)
			{
				if (username == tUsername)
				{
					std::cout << "Username already taken!\n";
				}
				else if (email == tEmail)
				{
					std::cout << "Email already taken!\n";
				}
				else if (phone == tPhone)
				{
					std::cout << "Phone already taken!\n";
				}
				isNew = false;
			}
		}
	}
	inf.close();
	return isNew;
}

void Customer::createAccount()
{

	
	welcome("CREATE ACCOUNT");
	//std::cout << "\nCreate Account\n";
	std::ofstream outf;
	outf.open(CUSTOMER_FILE, std::ios::app); 

	bool allGood{ false };
	while (!allGood)
	{
		getUserInput();
		if (isNewUser())
		{
			allGood = true;
		}
	}
	
	// username, password, phone, email, isDiscoutEligible
	outf << username << ',' << password << ',' << "+977-98" << phone << ',' << email << ',' << "true" << '\n';

	outf.close();
}

bool Customer::validateLogin()
{
	bool isValid{ false };

	std::cout << "\n\n";
	box(" ");
	gotoxy(40, 9);
	std::cout << "Enter username: ";
	std::cin >> username;
	gotoxy(40, 10);
	std::cout << "Enter password: ";
	//Enter password for validation
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

	std::ifstream inf;
	inf.open(CUSTOMER_FILE);

	if (inf.is_open())
	{
		std::string line;
		while (std::getline(inf, line))
		{
			std::string tUsername, tPassword, tPhone, tEmail;
			
			int commaIndex1 = line.find(",");
			int commaIndex2 = line.find(",", commaIndex1 + 1);
			int commaIndex3 = line.find(",", commaIndex2 + 1);
			int commaIndex4 = line.find(",", commaIndex3 + 1);

			tUsername = line.substr(0, commaIndex1);
			tPassword = line.substr(commaIndex1 + 1, commaIndex2 - commaIndex1 - 1);
			tPhone = line.substr(commaIndex2 + 1, commaIndex3 - commaIndex2 - 1);
			tEmail = line.substr(commaIndex3 + 1, commaIndex4 - commaIndex3 - 1);

			if (username == tUsername && password == tPassword)
			{
				isValid = true;
				phone = tPhone;
				email = tEmail;
			}
		}
	}
	inf.close();
	return isValid;
}

void Customer::displayProfile()
{
	system("cls");
	welcome("YOUR PROFILE");
	box(" ");
	gotoxy(40, 7);
	std::cout << "Username: " << username << '\n';
	gotoxy(40, 8); 
	std::cout << "Password: " << password << '\n';
	gotoxy(40, 9); 
	std::cout << "Phone: " << phone << '\n';
	gotoxy(40, 10); 
	std::cout << "Email: " << email << '\n';
}

void Customer::placeDiscountRequest()
{
	// where the customer request is added
	std::string requestFilePath{ "./RestaurantData/DiscountRequests/" + username + ".txt" };

	std::ofstream outf(requestFilePath, std::ios::app);

	outf << "Customer Has Requested For DISCOUNT: 10%\n";

	outf.close();
}

bool Customer::mainMenuHandler()
{
	bool exit{ false };
	while (!exit)
	{
		system("cls");

		welcome("Mainmenu");

		char option = '\0';
		int opt = option - '0';

		std::cout << "\n\n";
		box(" ");
		// only able to choose these options
		while (opt != DISPLAY_CUS_MENU && opt != PLACE_ORDER && opt != REQUEST_DISCOUNT && opt != MY_ORDERS && opt != MY_PROFILE && opt != EXIT) {
			gotoxy(40, 8);
			std::cout << DISPLAY_CUS_MENU << " - DISPLAY MENU\n";
			gotoxy(40, 9);
			std::cout << PLACE_ORDER << " - PLACE ORDER\n";
			gotoxy(40, 10);
			std::cout << REQUEST_DISCOUNT << " - REQUEST DISCOUNT\n";
			gotoxy(40, 11);
			std::cout << MY_ORDERS << " - MY ORDER\n";
			gotoxy(40, 12);
			std::cout << MY_PROFILE << " - MY PROFILE\n";
			gotoxy(40, 13);
			std::cout << EXIT << " - EXIT\n";
			option = _getch();
			opt = option - '0';
		}

		if (opt == DISPLAY_CUS_MENU) {
			MenuItem menu;
			system("CLS");
			welcome("TODAY STUFFS");
			std::cout << "\n\n";


			gotoxy(5, 5);
			menu.showMenu();
			std::cout << std::endl;
			system("pause");
		}
		else if (opt == PLACE_ORDER) {
			system("cls");

			Order order;
			bool orderPlaced = order.placeOrder(*this);
			if (!orderPlaced)
			{
				std::cout << "Failed to place Order!\n";
			}
			else
			{
				system("cls");
				welcome("Your order has been placed.");
				welcome("Checkout on \"MY ORDERS\" ");
				//std::cout << "Order placed! Check out on \"MY ORDERS\"\n";
				system("pause");
			}
		}
		else if (opt == REQUEST_DISCOUNT)
		{
			system("cls");
			std::cout << "Request 10% discount as a regular customer? (y/n): ";
			char choice{ 'n' };
			std::cin >> choice;
			if (toupper(choice) == 'Y')
			{
				placeDiscountRequest();
			}
		}
		else if (opt == MY_ORDERS)
		{
			Order myOrder;
			bool fileExists = myOrder.displayCustomerOrder(*this); // display order for this customer

			// if not all order complete and the file exists then be able to cancel pending orders
			if (fileExists)
			{
				if (!myOrder.isAllOrderComplete(*this))
				{
					std::cout << "Cancel Order? (y/N): ";
					char cancel;
					std::cin >> cancel;
					if (std::toupper(cancel) == 'Y')
					{
						myOrder.cancelOrder(*this);
					}
				}
				else
				{
					std::cout << "Checkout? (y/N): ";
					char checkout;
					std::cin >> checkout;
					if (std::toupper(checkout) == 'Y')
					{
						myOrder.payOrderBill(*this);
					}
				}
			}
			system("pause");
		}
		else if (opt == MY_PROFILE)
		{
			displayProfile();
			std::cout << std::endl;
			system("pause");
		}

		else if (opt == EXIT) {
			exit = true;
		}

		else
		{
			std::cout << "Please enter the provided options!\n";
		}
	}
	return exit;
}