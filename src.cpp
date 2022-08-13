//OF NOTE THE DATABASE FILE SERVES AS A LOG OF ALL ITEMS THAT HAVE BEEN PUT ONTO STORE SHELVES OVER TIME IT IS MANTAINED IN ORDER TO KEEP TRACK OF TOTAL MONEY SPENT ALL LIVE PRODUCTS ARE LOCATED IN THE VECTORS


#include "src.h"
#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <string>
#define _USE_MATH_DEFINES 
#include <cmath>
#include <vector>
#include <cstdlib>

#define KEY_LEFT 75
#define KEY_RIGHT 77
std::vector<std::string> itemNameList;
std::vector<std::string> itemIDList;
std::vector<double> itemCostList;

class createUser { 
private:
	std::string defaultKey = "password";
public:
	bool isEmployee;

	createUser(bool isEmp) {
		isEmployee = isEmp;
		
	}
	bool CheckIsEmployee() {
		std::cout << "Please Enter the Employee Password" << std::endl;
		std::string passGuess;
		std::cin >> passGuess;
		for (int i = 0; i < 5; i++) {
			if (passGuess == defaultKey) {
				return true;
			}
			else if(i < 4) {
				std::cout << "Incorrect " << i << " More Tries Until The Program shuts down" << std::endl;
			}
			else {
				exit(0);
			}
		}
	}
	bool getIsEmployee(bool isEmployee) {
		return isEmployee;
	}

};
class shopperMenu {
public:
	std::ofstream inFile;
	double price;
	double taxRate = 1.0625;
	bool valid;
	std::string itemName;
	shopperMenu() {
		price = 0;
		itemName = "";
	}
	void test() {
		std::cout << itemIDList[0];
	}
	void init() {
		int index = 0;
		
		std::ifstream readFile("Database.txt");
		while (readFile) {
			itemNameList.push_back("");
			itemCostList.push_back(0);
			itemIDList.push_back("");
			readFile >> itemNameList[index] >> itemCostList[index] >> itemIDList[index];
			index++;
		}
		
	}
	void saveData(std::vector<std::string> id, std::vector<std::string> name, std::vector<double> cost) {
		std::ofstream file;
		file.open("Database.txt", std::ios::app);
		for (int i = 0; i < id.size(); i++) {
			file << id[i];
		}
		file << "\n";
		for (int i = 0; i < cost.size(); i++) {
			file << cost[i];
		}
		file << "\n";
		for (int i = 0; i < name.size(); i++) {
			file << name[i];
		}
		file << "\n";
		file.close();
	}
	double findCost(std::string item) {
		int index;
		
		std::vector<std::string>::iterator itr = std::find(itemNameList.begin(), itemNameList.end(), item);

		if (itr != itemNameList.cend()) {
			index = std::distance(itemNameList.begin(), itr);
			valid = true;
			return itemCostList[index]*(taxRate);
			
		}
		else{
			
			return NULL;
			valid = false;
		}
	}
	void makePurchase() {
		double cost = 0;
		std::string item;
		
		std::cout << "Enter the name of the item you would like to purchase" << std::endl;
		std::cin >> item;
		try {
			
			cost = findCost(item);
			if (valid == true) {
				std::cout << "That will be: " << roundf(findCost(item) * 100) / 100 << std::endl;
				std::cout << "Thanks for your purchase!" << std::endl;
				std::vector<std::string>::iterator itr = std::find(itemNameList.begin(), itemNameList.end(), item);


				
			}
			
			else {
				throw (cost);
			}
		}
		catch (double myCost) {
			std::cout << "Item does not exist try again?(y/n)";
			char c;
			std::cin >> c;
			if (c == 'y') makePurchase();
			else exit(0);

		}

	}

	
	void addNewItem() {
		std::string item;
		int count = 0;


		std::string itemName;
		double itemCost;
		std::string itemId;


		std::cout << "Enter the following values to create a new item\n1.Item Name\n2.Item Cost\n3.Item ID\n";

		std::cin >> itemName;

		std::locale loc;
		for (int i = 0; i < itemName.length(); ++i)
			itemName[i] = tolower(itemName[i]);
		while (true) {
			std::cin >> itemCost;
			try {
				if (std::cin.fail()) {
					throw "error";
				}
				if (itemCost > 0) {

					break;
				}
			}
			catch (char* error) {
				std::cout << error << std::endl;
				break;
			}
		}
		
		

		std::cin >> itemId;
		inFile.open("Database.txt", std::ios::app);
		inFile << itemName << " " << itemCost << " " << itemId << std::endl;
		inFile.close();

		itemNameList.push_back(itemName);
		itemIDList.push_back(itemId);
		itemCostList.push_back(itemCost);
		std::cout << std::endl;


	}

};
class employeeMenu:shopperMenu {
	
private:
	std::string itemId;
public:
	
	employeeMenu() {
		itemId = "";
		price = 0;
		taxRate = 0;
		itemName = "";
}
	
	void test() {
		std::cout << itemIDList[0];
	}
	
	
	void removeItem() {
		int index;
		
		int linecount = 0;
		
		std::string potItemId;
		std::cout << "Please enter the id of the item you would like to remove: " << std::endl;
		std::cin >> potItemId;
		std::string line;
		std::vector<std::string>::iterator itr = std::find(itemIDList.begin(), itemIDList.end(), potItemId);

		if (itr != itemIDList.cend()) {

			index = std::distance(itemIDList.begin(), itr);
			
			
			
			itemNameList.erase(std::next(itemNameList.begin(), index));
			itemCostList.erase(std::next(itemCostList.begin(), index));
			itemIDList.erase(std::next(itemIDList.begin(), index));


			
		}
		else {
			std::cout << "Item not found\n";


		}
		
	}

};

src::src()
{	
	
	shopperMenu s;
	employeeMenu e;
	s.init();
	
	createUser user(false);
	
	char c;
	do {
		std::cout << "Are you an Employee (y/n)" << std::endl;
		std::cin >> c;

		if (c == 'y') {
			if (user.CheckIsEmployee()) {
				std::cout<<"Employee Menu!" << std::endl; //open the Employee menu
				std::cout << "Would you like to \n1. Remove an item: \n2. Add an item\n3.exit\n";
				int input;
				std::cin >> input;
				if (input == 1) {
					e.removeItem();
				}
				else if (input == 2) {
					s.addNewItem();
				}
				else if (input == 3) {
					exit(0);
				}
				else {
					std::cout << "bad input" << std::endl;
					break;
				}
			}

		}
		else if (c == 'n') {
			std::cout << "Shopper Menu!" << std::endl; //open the Shopper menu
			std::cout << "Would you like to \n1. Purchase an item\n2.Exit" << std::endl;
			int input;
			std::cin >> input;
			if (input == 1) {
				s.makePurchase();
			}
			else if (input == 2) {
				exit(0);
			}
			else {
				std::cout << "bad input" << std::endl;
				break;
			}
			
		}
		else {
			continue;
		}
	}
		while (c != 'y' || c != 'n');
	
		
	}
