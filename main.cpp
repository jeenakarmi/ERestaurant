#include <iostream>
#include <string>
#include <chrono>
#include <thread>
#include <iomanip>
#include <Windows.h>
#include <conio.h>
#include <process.h>
#include <Windows.h>

#include "Admin.h"
#include "Customer.h"
#include "box.h"

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
        gotoxy(40, 10);
        std::cout << USER_ADMIN << ": ADMIN_LOGIN" << std::endl;
        gotoxy(40, 11);
        std::cout << USER_CUSTOMER << ": CUSTOMER_LOGIN" << std::endl;
        gotoxy(33, 12);
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
            gotoxy(0, 5);
            welcome("Only Authorized Person");
            Sleep(900);
            system("cls");
            user = USER_ADMIN;
            break;
        }
        else if (opt == USER_CUSTOMER) {
            system("cls");
            gotoxy(0, 5);
            welcome("Customers");
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
    welcome("You are not authorized!!! ");
    std::cout << "\n\n\n";
    welcome("Back to user type selection...");
    Sleep(900);
    /*box(" ");
    gotoxy(35, 8);
    std::cout << "Sorry, you are not authorized!\n";
    gotoxy(35, 9);
    std::cout << "Back to user type selection...\n";
    std::this_thread::sleep_for(std::chrono::seconds(2)); // this adds delay
    system("CLS");
    */
}

int main()
{
    
    welcome("C++ PROJECT ON ERestaurant");
    welcome("WELCOME TO ERestaurant");
    std::cout << "\n\n";
    
    box("PRESS ANY KEY TO CONTINUE...");
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
                welcome("Validating...");
                Sleep(900);
                system("cls");
                gotoxy(0, 5);
                welcome_for_username("Welcome", admin.getUserName());
                Sleep(900);
                system("cls");
                welcome_for_username("Welcome", admin.getUserName());
                //std::cout << "Welcome " << admin.getUserName() << "!\n\n";
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
                    welcome("LOGIN OR CREATE ACCOUNT");
                    box(" ");
                    gotoxy(40, 8);
                    std::cout << LOG_IN << " - LOG IN\n";
                    gotoxy(40, 9);
                    std::cout << CREATE_ACCOUNT << " - CREATE ACCOUNT\n";
                    gotoxy(40, 10); 
                    std::cout << USER_SELECTION << " - USER SLECTION\n";

                    option = _getch();
                    opt = option - '0';
                }
                
                if (opt == LOG_IN)
                {
                    system("CLS");;
                    
                    //prompts the message login
                    welcome("LOGIN");

                    Customer customer;
                    bool isCustomerUser{ customer.validateLogin() };
                    if (!isCustomerUser)
                    {
                        system("cls");
                        std::cout << "\n\n";
                        welcome("INCORRECT USERNAME OR PASSWORD");
                        
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