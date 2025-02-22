#include "Customer.h"
#include <iostream>
#include <cstdlib>


using namespace std;

void Customer::addRelatedAccount() {
	cout << "\033[2J\033[1;1H";
	string newAccountTypeName;
	cout << "\n Creating a Relative Account: ";
	cout << "\nEnter Account Type Name: ";
	getline(cin, newAccountTypeName);
	if (newAccountTypeName.empty()) {
		cout << "\nAccount type name cannot be empty. Try Again." << endl;
		while (newAccountTypeName.empty()) {
			cout << "\nEnter Account Type Name: ";
			getline(cin, newAccountTypeName);
		}
	}


	Account newAccount;
	newAccount.setEmailForced(this->getEmail());
	newAccount.setRoleForced("branch");
	newAccount.setAccountTypeName(newAccountTypeName);
	newAccount.setBalance("0.00");
	customerAccounts.push_back(newAccount);
	newAccount.saveToDatabase(); 
	cout << "\nAccount added successfully!" << endl;
}

void Customer::displayCustomerRelatedAccounts()const {
	if (!customerAccounts.empty()) {
		cout << "\n" << getUserName() << " Accounts:" << endl;
		for (int i = 0; i < customerAccounts.size(); ++i) {
			cout << i + 1 << ". " << customerAccounts[i].getAccountTypeName()
				<< " (Current Balance: " << customerAccounts[i].getBalance() << ")" << endl;
		}
	}
	else {
		cout << "\nYou have no accounts yet. Please add an account first." << endl;
	}
}

void Customer :: customerMenu() {
	int choice = 0;
	while (choice != 6) {
		cout << "\n----------------\n" 
			<< "CUSTOMER MENU:\n";
		displayAccountInfo();
		displayCustomerRelatedAccounts();
		int accountIndex = -1;
			cout<<"\nOperations: "
			<< "\n1. Deposit money"
			<< "\n2. Withdraw money"
			<< "\n3. Add New Relative Account"
			<< "\n4. Update Accounts' info"
			<< "\n5. View audit file"
			<< "\n6. Log Out";
		
		choice = getValidInput<int>("\n choose operation number: ");
		switch (choice) {
		case 1: {
			displayCustomerRelatedAccounts();
				while (accountIndex < 0 || accountIndex >= customerAccounts.size()) {
					accountIndex = getValidInput<int>("\nSelect account (enter number): ") - 1;
					if (accountIndex < 0 || accountIndex >= customerAccounts.size()) {
						cout << "\nInvalid account selection. Please try again." << endl;
					}
				}

				double depositAmount;
				depositAmount = getValidInput<double>("\nEnter amount to deposit: ");
				customerAccounts[accountIndex].deposit(depositAmount);
			break;
		}
		case 2: {
			displayCustomerRelatedAccounts();
				while (accountIndex < 0 || accountIndex >= customerAccounts.size()) {
					accountIndex = getValidInput<int>("\nSelect account (enter number): ") - 1;
					if (accountIndex < 0 || accountIndex >= customerAccounts.size()) {
						cout << "\nInvalid account selection. Please try again." << endl;
					}
				}
				double withdrawAmount;
				withdrawAmount = getValidInput<double>("\nEnter amount to withdraw: ");
				customerAccounts[accountIndex].withdraw(withdrawAmount);
			break;
		}
		case 3: {
			addRelatedAccount();
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
			cout << "\Logged Out...\n";
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

void Customer::loadRelatedAccounts(const string& customerEmail) {
	customerAccounts.clear();
	ifstream file("usersDatabase.txt");
	if (!file) {
		cout << "\n ERROR: users database, cannot open file to load related accounts." << endl;
		return;
	}

	vector<Account> allAccounts;
	string line;
	while (getline(file, line)) {
		stringstream recordLine(line);
		string column;
		string accountIdStr;

		if (getline(recordLine, accountIdStr, ',')) {
			Account account;
			account.loadFromDatabase(accountIdStr); 
			allAccounts.push_back(account);
		}
	}
	file.close(); 

	for (const auto& account : allAccounts) {
		if (account.getEmail() == customerEmail) {
			customerAccounts.push_back(account);
		}
	}
	if (customerAccounts.empty()) {
		cout << "\nNo related accounts found for this email." << endl; 
	}
}
