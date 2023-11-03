#include <iostream>
#include <string>
#include <Windows.h>
#include <conio.h>

#include "Admin.h"
#include "Customer.h"

enum CUSTOMER_LOG_CHOICE
{
    LOG_ZERO,
    LOG_IN,
    CREATE_ACCOUNT,
    USER_SELECTION
};

enum UserType
{
    USER_ZERO,
    USER_ADMIN,
    USER_CUSTOMER,
    EXIT_PROGRAM
};

int getUserType(); // function that gets who is the user (admin or customer)
void unauthorizedUserMessage();


int getUserType()
{
    //system("cls");
    
    int user; // kun chai user ho ta vanera rakheko ni...
    char option = 0;
    int opt = option - '0'; // converts char single digit number into int
    while (opt != USER_ADMIN && opt != USER_CUSTOMER) {
        system("cls");
        std::cout << "\n\n\n";
        std::cout << USER_ADMIN << ": ADMIN_LOGIN" << std::endl;
        std::cout << USER_CUSTOMER << ": CUSTOMER_LOGIN" << std::endl;
        std::cout << "ALT + F4: EXIT_PROGRAM" << std::endl;

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
            system("cls");
            Sleep(900);
            system("cls");
            user = USER_ADMIN;
            break;
        }
        else if (opt == USER_CUSTOMER) {
            system("cls");
            Sleep(900);
            system("cls");
            user = USER_CUSTOMER;
            break;
        }
        
    }
    return user;
}

void unauthorizedUserMessage()
{
    system("cls");
    std::cout << "\n\n";
    system("cls");
    std::cout << "\n\n\n";
    Sleep(900);
}

int main()
{
    std::cout << "PRESS ANY KEY TO CONTINUE...\n";
    _getch();

    system("cls");

    bool quit{ false }; // application termination flag
    while (!quit)
    {
        int user{ getUserType() };
        if (user == USER_ADMIN)
        {
            // admin login validation page
            
            // prompts out the message adim login
            

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
          
                Sleep(900);
                system("cls");
                Sleep(900);
                system("cls");
                bool exit = admin.mainMenuHandler();
            }
        }
        else
        {
            while (true)
            {
                char option = 0;
                int opt = option - '0';
                std::cout << "\n\n";
                while (opt != LOG_IN && opt != CREATE_ACCOUNT && opt != USER_SELECTION) {
                    // prompts out message login or create account
                    system("cls");
                    std::cout << LOG_IN << " - LOG IN\n";
                    std::cout << CREATE_ACCOUNT << " - CREATE ACCOUNT\n";
                    std::cout << USER_SELECTION << " - USER SLECTION\n";

                    option = _getch();
                    opt = option - '0';
                }
                
                if (opt == LOG_IN)
                {
                    system("CLS");;
                    
                    //prompts the message login
                    Customer customer;
                    bool isCustomerUser{ customer.validateLogin() };
                    if (!isCustomerUser)
                    {
                        system("cls");
                        std::cout << "\n\n";
                        Sleep(900);
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
                else if (opt == CREATE_ACCOUNT)
                {
                    // create account
                    Customer newCustomer;
                    system("CLS");
                    newCustomer.createAccount();
                    
                    break;
                }
                else if (opt == USER_SELECTION)
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