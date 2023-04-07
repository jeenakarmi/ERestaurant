#include <iostream>
#include <string>
#include <chrono>
#include <thread>

#include "Admin.h"
#include "Customer.h"

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
	int user = 0; // by default admin however below loop will make sure to get input from user
	std::cout << "CUTOMER OR ADMIN\n";
	std::cout << USER_ADMIN << " - USER_ADMIN\n";
	std::cout << USER_CUSTOMER << " - USER_CUSTOMER\n";
	while (true)
	{
		std::cout << "Enter Choice: ";
		std::cin >> user;

		if (user == USER_ADMIN || user == USER_CUSTOMER)
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
				std::cout << "Login Or Create Account\n";
				std::cout << "0 - LOG IN\n";
				std::cout << "1 - CREATE ACCOUNT\n";
				std::cout << "2 - USER SLECTION\n";
				int choice;
				std::cout << "Input: ";
				std::cin >> choice;
				if (choice == 0)
				{
					// admin login validation page
					std::cout << "CUSTOMER LOGIN\n";
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
				else if (choice == 1)
				{
					// create account
					Customer newCustomer;
					newCustomer.createAccount();
					break;
				}
				else if (choice == 2)
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