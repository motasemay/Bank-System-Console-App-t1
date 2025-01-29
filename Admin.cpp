#include "Admin.h"
#include <iostream>
#include <string>


	Admin::Admin() {}

	//The admin will be able to read, create, updateand delete user's accounts.
	void Admin:: createNewAccount() {
		Account newAccount;
		string newRole;
		string newUserName;
		string newEmail;
		string newPassword;
		string ConfirmPassword;
		string newPhoneNumber;
		string newAge;
		string newBalance; 
		cout << "\n Creating new Account: \n";
		cin.ignore();
		while (true) {
			cout << "\n Enter Account's user name: ";
			getline(cin, newUserName);
			if (!userNameValidation(newUserName))
			{
				cout << ", Try Again:";
				continue;
			}
			newAccount.setUserName(newUserName);
			break;
		}
		cout << "\n new Account's User Name: " << newAccount.getUserName() << endl;

		while (true) {
			cout << "\n Enter Account's Email: ";
			getline(cin, newEmail);
			if (!emailValidation(newEmail)) {
				cout << ", Try Again";
				continue;
			}
			newAccount.setEmail(newEmail);
			break;
		}
		cout << "\n new Account's Email: " << newAccount.getEmail() << endl;

		while (true) {
			cout << "\n Enter Account's Role (customer, admin) : ";
			getline(cin, newRole);
			if (!roleValidation(newRole)) {
				cout << ", Try Again:";
				continue;
			}
			newAccount.setRole(newRole);
			break;
		}
		cout << "\n new Account's Role: " << newAccount.getRole() << endl;

		while (true)
		{
			cout << "\n Enter Accounts' Password: ";
			getline(cin, newPassword);
			if (!passwordValidation(newPassword))
				continue;
			cout << "\n RE-Enter the password: ";
			getline(cin, ConfirmPassword);
			if (newPassword == ConfirmPassword) {
				newAccount.setPassword(newPassword);
				cout << "\n new Account's Password is: " << newAccount.getPassword() << endl;
				break;
			}
			else {
				cout << "\n the passwords you entered isn't match, try again..";
			}
		}

		
		while (true)
		{
			cout << "\n Enter the Accounts Phone Number: ";
			getline(cin, newPhoneNumber);
			if (!phoneNumberValidation(newPhoneNumber)) {
				cout << ", Try Again:";
				continue;
			}
			else
			{
				newAccount.setPhoneNumber(newPhoneNumber);
				cout << "\n new Account's Phone Number: " << newAccount.getPhoneNumber() << endl;
				break;
			}
		}

		while (true) {
			cout << "\n Enter the User's Age: ";
			getline(cin, newAge);
			if (!ageValidation(newAge)) {
				cout << ", Try Again: ";
				continue;
			}
			newAccount.setAge(newAge);
			break;
		}
		cout << "\n new Account's age: " << newAccount.getAge() << endl;

		string test = "";
		while (test != "Y" && test != "y") {
			cout << "\n Enter the Balance you want it to be in the Account's: ";
			cin >> newBalance;
			if (!balanceValidation(newBalance)) {
				cout << ", Try Again:";
				continue;
			}
			cout << "\nCRITICAL OPERATION: \n	are you sure you want " << newAccount.getUserName() << " to have " << newBalance << " in his account? [Y] yes,(other inputs will considered no) : ";
			cin.ignore();
			getline(cin, test);
			if (test == "Y" || test == "y") {
				newAccount.setBalance(newBalance);
			}
		}
		cout << "\n new Account's BALANCE: " << newAccount.getBalance();

		newAccount.setIsActive(true);

		accounts.push_back(newAccount);
		newAccount.saveToDatabase();
		cout << "\n new Account created successfully..\n\n";
	}

	void Admin::displayInfoForAccount(const string& accountEmail) {
		for (int i = 0; i < accounts.size(); i++) {
			if (accounts[i].getEmail() == accountEmail) {
				accounts[i].displayAccountInfo();
				return;
			}
		}
		cout << "\n Display Account's Info :there is no Account with such an Email\n";
	}

	void Admin:: deleteAccount(const string& accountEmail) {
		for (int i = 0; i < accounts.size(); i++) {
			if (accounts[i].getEmail() == accountEmail) {
				string tempUserName = accounts[i].getUserName();
				accounts.erase(accounts.begin() + i);
				cout << "\n" << tempUserName << " Account's is deleted X \n";
				return;
			}
		}
		cout << "\n Delete :there is no Account with such an Email\n";
	}

	void Admin::updateAccount(const string& accountEmail) {
		for (int i = 0; i < accounts.size(); i++) {
			if (accounts[i].getEmail() == accountEmail) {
				accounts[i].updateAccountInfo();
				cout << "\n" << accounts[i].getUserName() << " Account's info is updated";
				return;
			}
		}
		cout << "\n Update :there is no Account with such an Email";
	}

	void Admin::withdrawFromAccount(const string& accountEmail, double amount) {
		for (int i = 0; i < accounts.size(); i++) {
			if (accounts[i].getEmail() == accountEmail) {
				accounts[i].withdraw(amount);
				cout << "\n" << amount << " is withdrawed from " << accounts[i].getUserName() << "'s Account\n";
				return;
			}
		}
		cout << "\n Withdraw from Account :there is no Account with such an Email\n";
	}

	void Admin::depositToAccount(const string& accountEmail, double amount) {
		for (int i = 0; i < accounts.size(); i++) {
			if (accounts[i].getEmail() == accountEmail) {
				accounts[i].deposit(amount);
				cout << "\n" << amount << " is deposited to " << accounts[i].getUserName() << "'s Account\n";
				return;
			}
		}
		cout << "\n Deposit to Account :there is no Account with such an Email\n";
	}

	void Admin::displayActiveAccounts()const {
		int counter = 1;
		cout << "\n Active Accounts: {\n ";
		if (accounts.size() != 0) {
			cout << "  " << " NAME " << "|" << "   ID   " << "|" << "   EMAIL    " << "|" << "  BALANCE  " << "|" << "   ROLE    " << "|" << "      PHONE NUMBER      " << "|" << "   AGE   " << "|" << "  STATUS   ";
		}
		for (int i = 0; i < accounts.size(); i++) {
			if (accounts[i].getIsActive() == false) continue;
			cout << endl << counter << "." << accounts[i].getUserName() << "  " <<" #"<<accounts[i].getId() << "  " << accounts[i].getEmail() << "  " << accounts[i].getBalance()<< "  " << accounts[i].getRole() << "  " << accounts[i].getPhoneNumber()<<"     "<<accounts[i].getAge() <<"    " << (accounts[i].getIsActive() == true ? "Active" : "INactive");
			counter++;
		}
		cout << " }\n";
	}

	void Admin::displayInactiveAccounts()const {
		int counter = 1;
		cout << "\n Inactive Accounts: {\n ";
		if (accounts.size() != 0) {
			cout << "  " << " NAME " << "|" << "   ID   " << "|" << "   EMAIL    " << "|" << "  BALANCE  " << "|" << "   ROLE    " << "|" << "      PHONE NUMBER      " << "|" << "   AGE   " << "|" << "  STATUS   ";
		}
		for (int i = 0; i < accounts.size(); i++) {
			if (accounts[i].getIsActive() == true) continue;
			cout << endl << counter << "." << accounts[i].getUserName() << "  " <<accounts[i].getEmail() << "  " << accounts[i].getPhoneNumber();
			counter++;
		}
		cout << " }\n";
	}

	void Admin::deactivateAccount(const string& accountEmail) {
		for (int i = 0; i < accounts.size(); i++) {
			if (accounts[i].getEmail() == accountEmail) {
				if (accounts[i].getIsActive() == false) {
					cout << "\n" << accounts[i].getUserName() << " Account's is already Dactivated...\n";
					return;
				}
				accounts[i].setIsActive(false);
				cout << "\n" << accounts[i].getUserName() << " Account's is deactivated \n";
				return;
			}
		}
		cout << "\n Deactivate Account :there is no Account with such an Email\n";
	}

	void Admin::activateAccount(const string& accountEmail) {
		for (int i = 0; i < accounts.size(); i++) {
			if (accounts[i].getEmail() == accountEmail) {
				if (accounts[i].getIsActive() == true) {
					cout << "\n" << accounts[i].getUserName() << " Account's is already Active..\n";
					return;
				}
				accounts[i].setIsActive(true);
				cout << "\n" << accounts[i].getUserName() << " Account's is Aactivated \n";
				return;
			}
		}
		cout << "\n Activate Account :there is no Account with such an Email\n";
	}

	void Admin::adminMenu() {
		int choise = 0;
		while (choise != 10) {
			displayActiveAccounts();
			displayInactiveAccounts();
			cout << "\n Admin Menu: "
				<< "\n1.Create A New Account."
				<< "\n2.Display An Account's Info."
				<< "\n3.Delete An Account."
				<< "\n4.Update An Account."
				<< "\n5.Withdraw from An Account."
				<< "\n6.Deposit To An Account."
				<< "\n7.Display Active Accounts."
				<< "\n8.Display InActive Accounts"
				<< "\n9.Deactivate An Account."
				<< "\n10.Activate An Account."
				<< "\n11. CLOSE This Menu"
				<< "\n choose the operation: ";
			cin >> choise;
			switch (choise) {
			case 1: {
				createNewAccount();
			}break;
			case 2:{
				cout << "\n Enter the Email for the Account to DISPLAY its Info: ";
				string searchEmail;
				cin.ignore();
				getline(cin, searchEmail);
				displayInfoForAccount(searchEmail);
			}break;
			case 3: {
				cout << "\n Enter the Email for the Account to DELETE: ";
				string searchEmail;
				cin.ignore();
				getline(cin, searchEmail);
				deleteAccount(searchEmail);
			}break;
			case 4: {
				cout << "\n Enter the Email for the Account to UPDATE: ";
				string searchEmail;
				cin.ignore();
				getline(cin, searchEmail);
				updateAccount(searchEmail);
			}break;
			case 5: {
				cout << "\n Enter the Email for the Account to WITHDRAW from: ";
				string searchEmail;
				int amount = 0;
				cin.ignore();
				getline(cin, searchEmail);
				amount = getValidInput<int>("\n how much you want to withdraw:");
				withdrawFromAccount(searchEmail, amount);
			}break;
			case 6: {
				cout << "\n Enter the Email for the Account to DEPOSIT to it: ";
				string searchEmail;
				int amount = 0;
				cin.ignore();
				getline(cin, searchEmail);
				amount = getValidInput<int>("\n how much you want to deposit: ");
				depositToAccount(searchEmail, amount);
			}break;
			case 7: {
				displayActiveAccounts();
			}break;
			case 8: {
				displayInactiveAccounts();
			}break;
			case 9: {
				cout << "\n Enter the Email for the Account to DEACTIVATE it: ";
				string searchEmail;
				cin.ignore();
				getline(cin, searchEmail);
				deactivateAccount(searchEmail);
			}break;
			case 10: {
				cout << "\n Enter the Email for the Account to ACTIVATE it: ";
				string searchEmail;
				cin.ignore();
				getline(cin, searchEmail);
				activateAccount(searchEmail); }break;

			case 11: {
				cout << "stoped..\n----------------------------------";
			}break;
			default: {
				cout << "\nInvalid choice, select a valid option: ";
				break;
			}
			}
		}
	}
