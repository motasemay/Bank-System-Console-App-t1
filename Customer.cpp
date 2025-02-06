#include "Customer.h"
#include <iostream>
#include <cstdlib>


using namespace std;

void Customer::addRelatedAccount()
{

}

void Customer :: customerMenu() {
	int choice = 0;
	while (choice != 5) {
		cout << "\n----------------\n" 
			<< "CUSTOMER MENU:\n";
		displayAccountInfo();
			cout<<"\n\noperations: "
			<< "\n1. Deposit money"
			<< "\n2. Withdraw money"
			<< "\n3. Update Accounts' info"
			<< "\n4. View audit file"
			<< "\n5. stop";
		//cin >> stringChoice;
		//try {
		//	choice = stoi(stringChoice);
		//}
		//catch (const invalid_argument& error) {
		//	cout << "\n invalid input, Please enter a number.";
		//	continue;
		//}
		//catch (const out_of_range& error) { 
		//	cout << "\nInput out of range. Please enter a valid number." ;
		//	continue;
		//}
		choice = getValidInput<int>("\n choose operation number: ");
		switch (choice) {
		case 1: {
			double depositAmount;
			depositAmount = getValidInput<double>("\nEnter amount to deposit: ");
			deposit(depositAmount);
			break;
		}
		case 2: {
			double withdrawAmount;
			withdrawAmount = getValidInput<double>("\nEnter amount to withdraw: ");
			withdraw(withdrawAmount);
			break;
			
		}
		case 3: {
			updateAccountInfo();
			break;
		}
		case 4: {
			//DisplayAuditFile();
			break;
		}
		case 5: {
			cout << "\nExiting customer menu.\n";
			//system("CLS");// ASK: isn't recommanded for security perposes	 
			cout << "\033[2J\033[1;1H";
			break;
		}
		default: {
			cout << "\nInvalid choice number, Please select from the menu ";
			break;
		}
		}
	}
}

