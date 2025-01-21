#include "Customer.h"
#include <iostream>


using namespace std;

void Customer :: customerMenu() {
	int choice = 0;
	while (choice != 6) {
		DisplayAccountInfo();
		cout << "\nCUSTOMER MENU:"
			<< "\n1. Display Account's Info"
			<< "\n2. Deposit money"
			<< "\n3. Withdraw money"
			<< "\n4. Update Accounts' info"
			<< "\n5. View audit file"
			<< "\n6. stop"
			<< "\nChoose an option: ";
		cin >> choice;
		switch (choice) {
		case 1: {
			DisplayAccountInfo();
			break;
		}
		case 2: {
			double depositAmount;
			cout << "\nEnter amount to deposit: ";
			cin >> depositAmount;
			deposit(depositAmount);
			break;
		}
		case 3: {
			double withdrawAmount;
			cout << "\nEnter amount to withdraw: ";
			cin >> withdrawAmount;
			withdraw(withdrawAmount);
			break;
		}
		case 4: {
			updateAccountInfo();
			break;
		}
		case 5: {
			//DisplayAuditFile();
			break;
		}
		case 6: {
			cout << "\nExiting customer menu.\n";
			break;
		}
		default: {
			cout << "\nInvalid choice, select a valid option: ";
			break;
		}
		}
	}
}

