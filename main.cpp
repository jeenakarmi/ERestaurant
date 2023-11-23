#include <iostream>
#include <string>
#include <algorithm>
#include <Windows.h>
#include <conio.h>
#include <chrono>
#include <ctime>
#include <filesystem>

#include "Admin.h"
#include "Customer.h"
#include "MenuItem.h"
#include "Order.h"

#include "UIElems.h"

enum class CUSTOMER_CHOICES
{
        OPTION_ZERO,
        DISPLAY_MENU,
        PLACE_ORDER,
        VIEW_ORDER,
        GO_BACK
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


void Border()
{
        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        PCONSOLE_SCREEN_BUFFER_INFO lpScreenInfo = new CONSOLE_SCREEN_BUFFER_INFO();
        GetConsoleScreenBufferInfo(hConsole, lpScreenInfo);
        COORD NewSBSize = lpScreenInfo->dwSize;
        std::cout << NewSBSize.X << '\n';
}

int getUserType()
{
    int user; // kun chai user ho ta vanera rakheko ni...
    char option = 0;
    int opt = option - '0'; // converts char single digit number into int
    while (opt != USER_ADMIN && opt != USER_CUSTOMER && opt != EXIT_PROGRAM) {
        system("cls");
        Title("A Better Solution for All the Users", centerY - 8);
        Title("Select the user type!", centerY - 6);

        MenuItems({"1: ADMIN", "2: CUSTOMER", "3: EXIT"});
        option = _getch();
        opt = option - '0';
    }
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
        else if (opt == EXIT_PROGRAM)
        {
                user = EXIT_PROGRAM;
                break;
        }
        
    }
    return user;
}

void unauthorizedUserMessage()
{
        system("CLS");
        Title("Only authorized people can login!", centerY - 1);
    Sleep(900);
}

bool fileExists(const std::string& name)
{
        if (FILE* file = fopen(name.c_str(), "r"))
        {
                fclose(file);
                return true;
        }
        else return false;
}

std::string initFinancialReport()
{
        // create file for financial report
        auto time = std::chrono::system_clock::now();
        std::time_t curr_time = std::chrono::system_clock::to_time_t(time);
        std::string str_time = std::ctime(&curr_time);
        int spaceIndex1 = str_time.find(' ');
        int spaceIndex2 = str_time.find(' ', spaceIndex1 + 1);
        int spaceIndex3 = str_time.find(' ', spaceIndex2 + 1);
        int spaceIndex4 = str_time.find(' ', spaceIndex3 + 1);

        // extracting individual date and time info from the whole string ( str_time )
        std::string dayStr = str_time.substr(0, spaceIndex1);
        std::string month = str_time.substr(spaceIndex1 + 1, spaceIndex2 - spaceIndex1 - 1);
        std::string dayNum = str_time.substr(spaceIndex2 + 1, spaceIndex3 - spaceIndex2 - 1);
        std::string timeStr = str_time.substr(spaceIndex3 + 1, spaceIndex4 - spaceIndex3 - 1);
        std::string year = str_time.substr(spaceIndex4 + 1, str_time.length() - spaceIndex4 - 2);

        // file path for financial report using the individual part
        std::filesystem::create_directories("./RestaurantData/FinanceReport/" + year + '/' + month);
        std::string report_file_name = "./RestaurantData/FinanceReport/" + year + '/' + month + '/' + dayStr + '_' + dayNum + ".csv";

        if (!fileExists(report_file_name))
        {
                std::ofstream outf;
                outf.open(report_file_name, std::ios::app);
                outf << "SN,Item Name,Item Price,Quantity,Total Price\n";
                outf.close();
        }
        return report_file_name;
}

int main()
{
        SetWindowSizeAndCentre();
        std::string titleStr{ "Erestaurant - A Restaurant Management System" };

        COORD consoleSize = GetWindowSize();
        int consoleWidth = consoleSize.X;
        int consoleHeight = consoleSize.Y;

        int textWidth = titleStr.length();
        int paddingX = (consoleWidth - textWidth) / 2;
        gotoxy(paddingX, centerY - 1);

        for (const auto c : titleStr)
        {
                std::cout << c;
                Sleep(50);
        }
        std::cout << '\n';
        Sleep(1000);

    system("cls");

    std::string report_file_name{ initFinancialReport() };

    bool quit{ false }; // application termination flag
    while (!quit)
    {
        int user{ getUserType() };
        if (user == USER_ADMIN)
        {
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
                bool exit = admin.mainMenuHandler();
            }
        }
        else if (user == USER_CUSTOMER)
        {
                Customer currCustomer;
            while (true)
            {
                char option = 0;
                int opt = option - '0';
                while (opt != static_cast<int>(CUSTOMER_CHOICES::DISPLAY_MENU) && opt != static_cast<int>(CUSTOMER_CHOICES::PLACE_ORDER) && opt != static_cast<int>(CUSTOMER_CHOICES::VIEW_ORDER) && opt != static_cast<int>(CUSTOMER_CHOICES::GO_BACK)) {
                    // prompts out message login or create account
                    system("cls");
                    Title("Welcome To Our Restaurant", centerY - 8);
                    Title("Feel free to look at today's menu!", centerY - 6);
                    MenuItems({ "1: TODAY'S MENU", "2: PLACE ORDER", "3: MY ORDER", "4: GO BACK"});

                    option = _getch();
                    opt = option - '0';
                }
                // can't use switch here due to MenuItem initialization (initialization can't be done inside switch)
                if (opt == static_cast<int>(CUSTOMER_CHOICES::DISPLAY_MENU))
                {
                        system("CLS");
                        MenuItem menu;
                        menu.showMenu();
                        system("pause");
                }
                else if (opt == static_cast<int>(CUSTOMER_CHOICES::PLACE_ORDER))
                {
                        system("CLS");
                        Order currOrder;
                        if (currOrder.placeOrder(&currCustomer))
                        {
                                std::cout << "Orders Placed Successfully!\n";

                                std::remove("temp.txt");
                                system("pause");
                                break;
                        }
                }
                else if (opt == static_cast<int>(CUSTOMER_CHOICES::VIEW_ORDER))
                {
                        system("CLS");
                        if (currCustomer.getUsername() == "")
                        {
                                Title("Log in to view the orders!", centerY - 15);
                                Customer newCustomer;
                                if (newCustomer.validateOrdererLogin())
                                {
                                        currCustomer = newCustomer;
                                        Order myOrder;
                                        bool fileExists = myOrder.displayCustomerOrder(currCustomer); // display order for this customer

                                        // if not all order complete and the file exists then be able to cancel pending orders
                                        if (fileExists)
                                        {
                                                if (!myOrder.isAllOrderComplete(currCustomer))
                                                {
                                                        std::cout << "Cancel Order? (y/N): ";
                                                        char cancel;
                                                        std::cin >> cancel;
                                                        if (std::toupper(cancel) == 'Y')
                                                        {
                                                                myOrder.cancelOrder(currCustomer);
                                                        }
                                                        else
                                                        {

                                                        }
                                                }
                                                else
                                                {
                                                        std::cout << "Checkout? (y/N): ";
                                                        char checkout;
                                                        std::cin >> checkout;
                                                        if (std::toupper(checkout) == 'Y')
                                                        {
                                                                myOrder.payOrderBill(currCustomer, report_file_name);
                                                        }
                                                }
                                        }
                                }
                                else
                                {
                                        system("CLS");
                                        Title("Account does not exist!", centerY - 15);
                                        Title("You can view your orders here after you place them!", centerY - 14);
                                }
                        }
                        else
                        {
                                Order myOrder;
                                bool fileExists = myOrder.displayCustomerOrder(currCustomer); // display order for this customer

                                // if not all order complete and the file exists then be able to cancel pending orders
                                if (fileExists)
                                {
                                        if (!myOrder.isAllOrderComplete(currCustomer))
                                        {
                                                std::cout << "Cancel Order? (y/N): ";
                                                char cancel;
                                                std::cin >> cancel;
                                                if (std::toupper(cancel) == 'Y')
                                                {
                                                        myOrder.cancelOrder(currCustomer);
                                                }
                                        }
                                        else
                                        {
                                                std::cout << "Checkout? (y/N): ";
                                                char checkout;
                                                std::cin >> checkout;
                                                if (std::toupper(checkout) == 'Y')
                                                {
                                                        myOrder.payOrderBill(currCustomer, report_file_name);
                                                }
                                        }
                                }
                        }
                        system("pause");
                }
                else if (opt == static_cast<int>(CUSTOMER_CHOICES::GO_BACK))
                {
                        break;
                }
            }
        }
        else
        {
                quit = true;
        }

    }
    
    return 0;
}