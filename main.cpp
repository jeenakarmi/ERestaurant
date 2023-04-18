#include <iostream>
#include <string>
#include <chrono>
#include <thread>
#include <iomanip>
#include <Windows.h>
#include <conio.h>

#include "Admin.h"
#include "Customer.h"
#include "box.h"

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

void welcome(std::string text)
{
	// customer login or sign up page
				//std::string text = "WELCOME";

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
}

void welcome_for_username(std::string text, std::string username1)
{
	// customer login or sign up page
				//std::string text = "WELCOME";

				// Define the width of the box
	const int boxWidth = 100;

	// Calculate the padding required to center the text
	int padding = (boxWidth - text.length()) / 2;

	// Display the box
	std::cout << std::setfill('=') << std::setw(boxWidth) << "" << std::endl;

	// Display the text with padding
	std::cout << std::setfill(' ') << std::setw(padding) << "" << "Welcome, " << username1 << "!" << std::setw(padding) << "" << std::endl;

	// Display the bottom of the box
	std::cout << std::setfill('=') << std::setw(boxWidth) << "" << std::endl;
}

int getUserType()
{
	//system("cls");
	

	int user; // kun chai user ho ta vanera rakheko ni...
	char option = 0;
	int opt = option - '0'; // converts char single digit number into int
	while (opt != USER_ADMIN && opt != USER_CUSTOMER) {
		system("cls");
		welcome("ADMIN OR COSTUMER");
		std::cout << "\n\n\n";
		box(" ");
		gotoxy(40, 13);
		std::cout << USER_ADMIN << ": ADMIN_LOGIN" << std::endl;
		gotoxy(40, 14);
		std::cout << USER_CUSTOMER << ": CUSTOMER_LOGIN" << std::endl;
		std::cout << "\n\n";
		option = _getch();
		opt = option - '0';
	}

	std::cout << "\n\n\n";
	std::cout << "WAIT_FOR_A_WHILE...\n";
	//Sleep(900);
	system("CLS");
	
	while (true)
	{

		if (opt == USER_ADMIN) {
			user = USER_ADMIN;
			break;
		}
		else if (opt == USER_CUSTOMER) {
			user = USER_CUSTOMER;
			break;
		}
		
	}
	return user;
}

void unauthorizedUserMessage()
{
	std::cout << "Sorry, you are not authorized!\n";
	std::cout << "Back to user type selection...\n";
	std::this_thread::sleep_for(std::chrono::seconds(2)); // this adds delay
	system("CLS");
}

int main()
{
	
	welcome("C++ PROJECT ON ERestaurant");
	welcome("WELCOME TO FUTURISTIC ERestaurant");
	std::cout << "\n\n";
	
	box("PRESS ANY KEY TO CONTINE...");
	//std::cout << "\n\n\nPRESS ANY KEY TO CONTINE...\n";
	gotoxy(46, 13);
	_getch();

	system("cls");
	welcome("ERestaurant");
	
	bool quit{ false };

	while (!quit)
	{
		int user{ getUserType() };
		if (user == USER_ADMIN)
		{
			 
			// admin login validation page
			
			// prompts out the message adim login
			welcome("ADMIN LOGIN");

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
				
				// it prints the message welcome, SauravDhoju
				welcome_for_username("Welcome", admin.getUserName());
				
				//std::cout << "Welcome " << admin.getUserName() << "!\n\n";
				bool exit = admin.mainMenuHandler();
			}
		}
		else
		{
			while (true)
			{
				// prompts out message login or create account
				welcome("LOGIN OR CREATE ACCOUNT");
				
								
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
					
					//prompts the message login
					welcome("LOGIN");


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
					system("CLS");
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