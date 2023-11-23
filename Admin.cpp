#include "Admin.h"
#include <iostream>
#include <fstream>
#include <filesystem>
#include <string>
#include <sstream>
#include <string_view>
#include <conio.h>
#include <cstdio>
#include <errno.h>
#include <ctime>
#include <chrono>

#include "MenuItem.h"
#include "InventoryItem.h"
#include "Order.h"


#include "UIElems.h"

/*void Admin::getAdminData()
{
	std::cout << "\n\n";
	std::cout << "Enter username: ";
	std::cin >> username;
	std::cout << "Enter password: ";
	//admimn password
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
	std::cout << "\n";
}*/

void Admin::getAdminData()
{
    // Get console window size
    COORD consoleSize = GetWindowSize();
    int consoleWidth = consoleSize.X;
    int consoleHeight = consoleSize.Y;

    // Calculate padding for centering
    int paddingX = (consoleWidth - 10) / 2; 

	Title("Admin Login ", centerY - 15); // Center the title
    std::cout << "\n\n";
    std::cout << "Enter username: ";
    std::cin >> username;

    std::cout  << "Enter password: ";
    
    // Admin password input with asterisks for security
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

    std::cout << "\n";
}

bool Admin::validateLogin()
{
	bool isValid{ false }; // flag

	std::ifstream inf;
	inf.open(ADMIN_FILE, std::ios::in);

	Admin currAdmin;
	if (!inf)
	{
		std::cout << "File Could Not Be Opened! filename: " << ADMIN_FILE << '\n';
		return false;
	}

	std::string line;
	while (std::getline(inf, line))
	{
		std::string userNameData; // from file
		std::string passwordData;
		
		int commaIndex1 = line.find(",");

		userNameData = line.substr(0, commaIndex1);
		passwordData = line.substr(commaIndex1 + 1);

		if (username == userNameData && password == passwordData)
		{
			isValid = true;
			break;
		}
	}

	return isValid;
}

std::string Admin::getUserName()
{
	return username;
}

/*bool Admin::displayCustomersWhoOrdered()
{
	Title("Customers Who Ordered", centerY - 15);
	std::cout << "\n\n";
	int count = 0;
	std::string path = "RestaurantData/Orders";
	for (const auto& entry : std::filesystem::directory_iterator(path))
	{
		std::string orderPath = entry.path().string();
		int slashIndex = orderPath.find('\\');
		int dotIndex = orderPath.find('.');
		std::string orderFileName = orderPath.substr(slashIndex + 1, dotIndex - slashIndex - 1);

		// === YETA CHANGE GARNE 
		std::cout << ++count << "\t" << orderFileName << '\n';
	}
	return count > 0;
}*/

bool Admin::displayCustomersWhoOrdered()
{
	std::string path = "RestaurantData/Orders";
	int count = 0;

	COORD consoleSize = GetWindowSize();
	int consoleHeight = consoleSize.Y;
	int titleWidth = 20;

	// Calculating the starting Y position for the list
	int listY = consoleHeight / 2 - 7;

	
	Title("Customers Who Ordered", centerY -15);      // Displaying the title at the centered position

	// Calculating padding for centering the table
	int padding = (consoleSize.X - titleWidth) / 2;

	std::cout << "\n";
	std::cout << std::setw(padding) << ' ';
	std::cout << std::setw(5) << std::left << "SN"
		<< std::setw(titleWidth) << std::left << "Name" << std::endl;

	std::cout << std::setfill(' ') << std::setw(padding - 2) << ' '
		<< std::setw(7) << std::setfill('-')
		<< std::setw(titleWidth) << std::left << '-'
		<< std::endl;

	for (const auto& entry : std::filesystem::directory_iterator(path))
	{
		std::string orderPath = entry.path().string();
		int slashIndex = orderPath.find('\\');
		int dotIndex = orderPath.find('.');
		std::string orderFileName = orderPath.substr(slashIndex + 1, dotIndex - slashIndex - 1);

		// Calculating the Y position for the order filename
		int itemY = listY + count - 4;

		// Calculating the X position for the count and order filename
		int countX = padding;
		int filenameX = padding + 5; // Adjusting the horizontal padding for filenames

		// Setting the cursor position and displaying the count and order filename
		gotoxy(countX, itemY);
		std::cout << count + 1;
		gotoxy(filenameX, itemY);
		std::cout << orderFileName;
		std::cout << "\n";

		++count;
	}

	return count > 0;
}
bool Admin::displayOrdersOfCustomer(int id)
{
	int currIndex = 1;
	std::string orderFilePath;
	std::string path = "RestaurantData/Orders";
	for (const auto& entry : std::filesystem::directory_iterator(path))
	{
		if (currIndex == id)
		{
			orderFilePath = entry.path().string();
			break;
		}
		++currIndex;
	}
	Order cusOrder;
	cusOrder.displayOrderFromFile(orderFilePath);

	std::cout << "Mark order complete/pending? (y/N): ";
	char ch;
	std::cin >> ch;
	bool exit = false;

	if (std::toupper(ch) == 'Y')
	{
		std::cout  << "ID: ";
		int orderItemId;
		std::cin >> orderItemId;
		cusOrder.markItemOrderComplete(orderFilePath, orderItemId);
	}
	else if (std::toupper(ch) == 'N')
	{
		exit = true;
	}
	else
	{
		std::cout << "Invalid input. Please enter 'y' or 'n'." << std::endl;
	}
	return exit;
}

void Admin::displayDiscountReqests()
{
	std::ifstream customerFile(CUSTOMER_FILE);

	std::string line;
	int count = 0;
	while (std::getline(customerFile, line))
	{
		int commaIndex1 = line.find(',');
		std::string cusUserName = line.substr(0, commaIndex1);
		std::string requestFilePath{ "RestaurantData/DiscountRequests/" + cusUserName + ".txt" };

		std::ifstream requestFile(requestFilePath);

		if (requestFile)
		{
			std::cout << ++count << '\t' << cusUserName << '\n';
		}

		requestFile.close();
	}

	customerFile.close();
}

void Admin::displayRegularCustomers()
{
	std::ifstream customerFile(CUSTOMER_FILE);

	std::string line;
	int count = 0;
	std::cout << "SN\t" << "Name\n";
	while (std::getline(customerFile, line))
	{
		int commaIndex1 = line.find(',');
		int commaIndex2 = line.find(',', commaIndex1 + 1);
		int commaIndex3 = line.find(',', commaIndex2 + 1);
		int commaIndex4 = line.find(',', commaIndex3 + 1);

		std::string customerName = line.substr(0, commaIndex1);
		bool isRegular = (line.substr(commaIndex4 + 1)) == "true" ? true : false;

		if (isRegular)
		{
			std::cout << ++count << '\t' << customerName << '\n';
		}
	}

	customerFile.close();
}

void Admin::approveRequest(int id)
{
	// create seperate file for seperate customer
}

void Admin::denyRequest(int id)
{
	std::string path;
	std::ifstream customerFile(CUSTOMER_FILE);

	std::string line;
	int count = 0;
	while (std::getline(customerFile, line))
	{
		int commaIndex1 = line.find(',');
		std::string cusUserName = line.substr(0, commaIndex1);
		std::string requestFilePath{ "RestaurantData/DiscountRequests/" + cusUserName + ".txt" };

		std::ifstream requestFile(requestFilePath);

		if (requestFile && ++count == id)
		{
			path = requestFilePath;
			break;
		}
		requestFile.close();
	}

	std::remove(path.c_str());
	customerFile.close();
}

void Admin::viewFinanceReport()
{
	// finance report functions here
	system("CLS");
	int consoleWidth = GetWindowSize().X;

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

	std::string report_file_name = "./RestaurantData/FinanceReport/" + year + '/' + month + '/' + dayStr + '_' + dayNum + ".csv";

	std::ifstream inf;
	inf.open(report_file_name);
	if (!inf.is_open())
	{
		std::string errorMsg = "The report doesn't exist!!\n";
		int paddingError = (consoleWidth - errorMsg.length()) / 2;
		std::cout << std::setw(paddingError) << errorMsg;
	}
	else
	{
		// centers the table
		std::stringstream tableHeadingStream;
		tableHeadingStream << std::setw(10) << std::left << "SN"
			<< std::setw(20) << std::left << "Item Name"
			<< std::setw(10) << std::left << "Price"
			<< std::setw(10) << std::left << "Quantity"
			<< std::setw(15) << std::left << "Total Price"
			<< '\n';
		std::string tableHeading = tableHeadingStream.str();
		int padding = (consoleWidth - tableHeading.length()) / 2;
		std::cout << std::setw(padding) << ' ';
		std::cout << tableHeading;

		// for line
		std::stringstream seperatorStream;
		seperatorStream << '-' << std::setfill('-') << std::setw(tableHeading.length()) << '-' << std::endl;
		std::string seperator = seperatorStream.str();
		std::cout << std::setfill(' ') << std::setw(padding - 2) << ' ' << seperator;
		std::cout << std::setfill(' ');

		float totalSale = 0.0f;
		int reportLineNum = 0;
		while (!inf.eof())
		{
			std::string line;
			if (std::getline(inf, line))
			{
				// skip first line containing headings
				if (reportLineNum == 0)
				{
					++reportLineNum;
					continue;
				}
				// indices of commas
				int reportCommaIndex1 = line.find(',');
				int reportCommaIndex2 = line.find(',', reportCommaIndex1 + 1);
				int reportCommaIndex3 = line.find(',', reportCommaIndex2 + 1);
				int reportCommaIndex4 = line.find(',', reportCommaIndex3 + 1);

				// individual data from report line
				int reportSN = std::stoi(line.substr(0, reportCommaIndex1));
				std::string reportItemName = line.substr(reportCommaIndex1 + 1, reportCommaIndex2 - reportCommaIndex1 - 1);
				float reportItemPrice = std::stof(line.substr(reportCommaIndex2 + 1, reportCommaIndex3 - reportCommaIndex2 - 1));
				int reportItemQuantity = std::stoi(line.substr(reportCommaIndex3 + 1, reportCommaIndex4 - reportCommaIndex3 - 1));
				float reportItemTotalPrice = std::stof(line.substr(reportCommaIndex4 + 1, line.length() - reportCommaIndex4 - 1));

				totalSale += reportItemTotalPrice;

				std::cout << std::setw(padding) << ' '
					<< std::setw(10) << std::left << reportLineNum++
					<< std::setw(20) << std::left << reportItemName
					<< std::setw(10) << std::left << reportItemPrice
					<< std::setw(10) << std::left << reportItemQuantity
					<< std::setw(15) << std::left << reportItemTotalPrice
					<< '\n';
			}
		}
		std::cout << std::setfill(' ') << std::setw(padding - 2) << ' ' << seperator;
		std::cout << std::setfill(' ');
		std::stringstream totalStringStream;
		totalStringStream << "Total Sales: Rs." << totalSale;
		std::string totalSaleStr = totalStringStream.str();
		std::cout << std::setw((consoleWidth - totalSaleStr.length()) / 2) << ' ' << totalSaleStr << "\n\n";
	}
}

bool Admin::mainMenuHandler()
{
	bool exit{ false };

	while (!exit)
	{
		char option = 0;
		int opt = option - '0';
		while (opt != DISPLAY_ORDERS && opt != DISPLAY_MENU && opt != INVENTORY && opt != REPORT_TODAY && opt != EXIT_MENU ) {
			system("cls");
			Title("ADMIN PAGE", centerY - 4);
			std::cout << "\n\n";
			MenuItems({ "1: DISPLAY ORDER", "2: DISPLAY MENU", "3: INVENTORY","4: TODAY'S REPORT", "5: EXIT"});
			option = _getch();
			opt = option - '0';
		}

		if (opt == DISPLAY_ORDERS)
		{
			system("cls");
			if (displayCustomersWhoOrdered())
			{
				
				std::cout << "\n\t\t\t\t\t" << "ID: ";
				int id;
				std::cin >> id;
				bool exit = false;
				while (!exit)
				{
					system("cls");
					exit = displayOrdersOfCustomer(id);
				}
			}
			else
			{
				std::cout << "No order files available!\n";
			}
			system("pause");
			// display orders
		}
		else if (opt == DISPLAY_MENU)
		{
			system("cls");

			// DISPLAY MENU
			MenuItem menu;
			menu.showMenu();
			system("pause");
		}
		else if (opt == INVENTORY)
		{
			system("cls");

			//Inventory 
			InventoryItem inventory;
			//inventory.showInventory();
			inventory.menuHandler();
			/*std::cout << "\nDo you want to update inventory?(y/N): ";
			char updateInput;
			std::cin >> updateInput;
			if (std::toupper(updateInput) == 'Y')
			{
				InventoryItem newItem;
				newItem.inputData();
				inventory.updateInventory(newItem);
				std::cout << "\n\nItem has been added succesfully...\n";
				system("cls");
			}
			else
			{
				system("cls");
				system("cls");
				continue;
			}*/
		}
		else if (opt == REPORT_TODAY)
		{
			viewFinanceReport();
			system("pause");
		}
		else if (opt == EXIT_MENU)
		{
			system("cls");
			system("cls");

			
			break;
		}
		else
		{
			std::cout << "Please choose valid input!\n";
		}
	}
	return exit;
}