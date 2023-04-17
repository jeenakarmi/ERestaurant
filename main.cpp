#include <iostream>
#include <string>
#include <chrono>
#include <thread>
#include <iomanip>
#include <Windows.h>
#include <conio.h>

#include "Admin.h"
#include "Customer.h"

const char ADMIN_OPTION = '0';
const char CUSTOMER_OPTION = '1';

const char LOG_IN = '0';
const char CREATE_ACCOUNT = '1';
const char USER_SELECTION = '2';

enum UserType
{
	USER_ADMIN,
	USER_CUSTOMER
};

int getUserType(); // function that gets who is the user (admin or customer)
void unauthorizedUserMessage();

int getUserType()
{
	//system("cls");
	int user = -1 ; //invalid value given so that in loop it checks with enterd value in loop

	std::string text = "ADMIN OR CUSTOMER";

	// Define the width of the box
	const int boxWidth = 100;

	// Calculate the padding required to center the text
	int padding = (boxWidth - text.length()) / 2;

	// Display the box
	std::cout << std::setfill('=') << std::setw(boxWidth) << "" << std::endl;

	// Display the text with padding
	std::cout << std::setfill(' ') << std::setw(padding) << "" << text << std::setw(padding) << "" << std::endl;

	// Display the bottom of the box
	std::cout << std::setfill('=') << std::setw(boxWidth) << "" << std::endl;

	char option = 0;
	while (option != ADMIN_OPTION && option != CUSTOMER_OPTION) {
		std::cout << "\n\n\n";


		std::cout << USER_ADMIN << ": ADMIN_LOGIN" << std::endl;
		std::cout << USER_CUSTOMER << ": CUSTOMER_LOGIN" << std::endl;
		std::cout << "\n\n";
		option = _getch();
	}

	std::cout << "\n\n\n";
	std::cout << "WAIT_FOR_A_WHILE...\n";
	//Sleep(900);
	system("CLS");
	
	while (true)
	{
		
		if (option == ADMIN_OPTION || option == CUSTOMER_OPTION)
		{
			// valid choice
			break;
		}
		else
		{
			// invalid input
			std::cout << "Invalid Input! Please choose from given options!\n";
		}
	}
	return user;
}

void unauthorizedUserMessage()
{
	std::cout << "Sorry, you are not authorized!\n";
	std::cout << "Back to user type selection...\n";
	std::this_thread::sleep_for(std::chrono::seconds(2)); // this adds delay
}

int main()
{
	std::string text = "ERestaurant";

	// Define the width of the box
	const int boxWidth = 100;

	// Calculate the padding required to center the text
	int padding = (boxWidth - text.length()) / 2;

	// Display the box
	std::cout << std::setfill('=') << std::setw(boxWidth) << "" << std::endl;

	// Display the text with padding
	std::cout << std::setfill(' ') << std::setw(padding) << "" << text << std::setw(padding) << "" << std::endl;

	// Display the bottom of the box
	std::cout << std::setfill('=') << std::setw(boxWidth) << "" << std::endl;

	bool quit{ false };

	while (!quit)
	{
		int user{ getUserType() };
		if (user == USER_ADMIN)
		{
			 
			// admin login validation page
			std::cout << "ADMIN LOGIN\n";
			Admin admin;
			admin.getAdminData();
			bool isAdminAuthorized{ admin.validateLogin() };
			if (!isAdminAuthorized)
			{
				unauthorizedUserMessage();
				continue;
			}
			else
			{
				system("cls");
				std::cout << "Welcome " << admin.getUserName() << "!\n\n";
				bool exit = admin.mainMenuHandler();
			}
		}
		else
		{
			while (true)
			{
				// customer login or sign up page
				std::string text = "LOGIN OR CREATE ACCOUNT";

				// Define the width of the box
				const int boxWidth = 100;

				// Calculate the padding required to center the text
				int padding = (boxWidth - text.length()) / 2;

				// Display the box
				std::cout << std::setfill('=') << std::setw(boxWidth) << "" << std::endl;

				// Display the text with padding
				std::cout << std::setfill(' ') << std::setw(padding) << "" << text << std::setw(padding) << "" << std::endl;

				// Display the bottom of the box
				std::cout << std::setfill('=') << std::setw(boxWidth) << "" << std::endl;

				
				
				
				char option = 0;
				while (option != LOG_IN && option != CREATE_ACCOUNT && option != USER_SELECTION) {
					std::cout <<"0 - LOG IN\n";
					std::cout <<"1 - CREATE ACCOUNT\n";
					std::cout <<"2 - USER SLECTION\n";

					option = _getch();
				}
				
				if (option == LOG_IN)
				{
					system("CLS");;
					
					std::string text = "LOGIN";  // admin login validation page
					const int boxWidth = 100;  // Define the width of the box
					int padding = (boxWidth - text.length()) / 2;   // Calculate the padding required to center the text
					std::cout << std::setfill('=') << std::setw(boxWidth) << "" << std::endl;	// Display the box
					std::cout << std::setfill(' ') << std::setw(padding) << "" << text << std::setw(padding) << "" << std::endl;	// Display the text with padding
					std::cout << std::setfill('=') << std::setw(boxWidth) << "" << std::endl;	// Display the bottom of the box

					Customer customer;
					bool isCustomerUser{ customer.validateLogin() };
					if (!isCustomerUser)
					{
						std::cout << "Sorry, incorrect username or password!\n\n";
						continue;
					}
					else
					{
						system("cls");
						std::cout << "Welcome " << customer.getUsername() << "!\n\n";
						bool exit = customer.mainMenuHandler();
					}
					break;
				}
				else if (option == CREATE_ACCOUNT)
				{
					// create account
					Customer newCustomer;
					newCustomer.createAccount();
					break;
				}
				else if (option == USER_SELECTION)
				{
					break;
				}
				else
				{
					std::cout << "Please enter valid input!\n";
				}
			}
		}

	}
	
	return 0;
}