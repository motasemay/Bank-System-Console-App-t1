#include "Admin.h"
#include <iostream>
#include <string>

	Admin::Admin() {}

	void Admin::loadAllAccountsFromDatabase() {
		accounts.clear(); 
		ifstream file("usersDatabase.txt");
		if (!file) {
			cout << "\n ERROR: users database, cannot open file to Load accounts data." << endl;
			return;
		}
		string line;
		while (getline(file, line)) {
			stringstream recordLine(line);
			string column;
			string accountIdStr;

			if (getline(recordLine, accountIdStr, ',')) { // not read the empty lines
					int accountId = stoi(accountIdStr); 
					string Role, UserName, Email, Password, PhoneNumber, Age, Balance, IsActiveStr;
					getline(recordLine, Role, ',');
					getline(recordLine, UserName, ',');
					getline(recordLine, Email, ',');
					getline(recordLine, Password, ',');
					getline(recordLine, PhoneNumber, ',');
					getline(recordLine, Age, ',');
					getline(recordLine, Balance, ',');
					getline(recordLine, IsActiveStr, ',');

					bool IsActive = (IsActiveStr == "Active");
					Account account;

					account.setRoleForced(Role);
					account.setUserNameForced(UserName);
					account.setEmailForced(Email);
					account.setPasswordForced(Password);
					account.setPhoneNumberForced(PhoneNumber);
					account.setAgeForced(Age);
					account.setBalanceForced(Balance);
					account.setIsActiveForced(IsActive);
					account.setIdForced(accountId);

					accounts.push_back(account);
			}
		}
		file.close();
	}

	void Admin:: createNewAccount() {
		Account newAccount;
		string newRole;
		string newUserName;
		string newEmail;
		string newPassword;
		string confirmPassword;
		string newPhoneNumber;
		string newAge;
		string newBalance; 
		cout << "\n Creating new Account: \n";
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
			if (!passwordValidation(newPassword)) {
				cout << ", Try Again: ";
				 continue;
			}
			cout << " RE-Enter the password: ";
			getline(cin, confirmPassword);
			if (newPassword == confirmPassword) {
				newAccount.setPassword(newPassword);
				cout << "\n new Account's Password is: " << newAccount.getPassword()<<endl;
				break;
			}
			else {
				cout << "\n the passwords you entered isn't match, try again..";
				continue;
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

	bool Admin::displayInfoForAccount(const string& accountEmail) {
		loadAllAccountsFromDatabase();
		for (int i = 0; i < accounts.size(); i++) {
			if (accounts[i].getEmail() == accountEmail) {
				accounts[i].displayAccountInfo();
				return true;
			}
		}
		cout << "\n Display Account's Info :there is no Account with such an Email";
		return false;
	}

	bool Admin:: deleteAccount(const string& accountEmail) {
		loadAllAccountsFromDatabase();
		for (int i = 0; i < accounts.size(); i++) {
			if (accounts[i].getEmail() == accountEmail) {
				string tempUserName = accounts[i].getUserName();
				accounts[i].deleteFromDatabase();
				accounts.erase(accounts.begin() + i);
				cout << "\n" << tempUserName << " Account's is Deleted\n";
				
				return true;
			}
		}
		cout << "\n Delete :there is no Account with such an Email";
		return false;
	}

	bool Admin::updateAccount(const string& accountEmail) {
		loadAllAccountsFromDatabase();
		for (int i = 0; i < accounts.size(); i++) {
			if (accounts[i].getEmail() == accountEmail) {
				accounts[i].updateAccountInfo();
				cout << "\n" << accounts[i].getUserName() << " Account's info is updated";
				return true;
			}
		}
		cout << "\n Update :there is no Account with such an Email";
		return false;
	}

	bool Admin::withdrawFromAccount(const string& accountEmail) {
		loadAllAccountsFromDatabase();
		double amount; 
		for (int i = 0; i < accounts.size(); i++) {
			if (accounts[i].getEmail() == accountEmail) {
				amount=getValidInput<int>("\n how much you want to withdraw:");
				accounts[i].withdraw(amount);
				//FIXTHIS: cout << "\n" << amount << " is withdrawed from " << accounts[i].getUserName() << "'s Account";
				return true;
			}
		}
		cout << "\n Withdraw from Account :there is no Account with such an Email";
		return false;
	}

	bool Admin::depositToAccount(const string& accountEmail) {
		loadAllAccountsFromDatabase();
		double amount; 
		for (int i = 0; i < accounts.size(); i++) {
			if (accounts[i].getEmail() == accountEmail) {
				amount=getValidInput<int>("\n how much you want to deposit: ");
				accounts[i].deposit(amount);
				return true;
			}
		}
		cout << "\n Deposit to Account :there is no Account with such an Email";
		return false;
	}

	void Admin::displayActiveAccounts() {
		loadAllAccountsFromDatabase();
		int counter = 1;
		cout << "\n Active Accounts: \n{\n ";
		if (accounts.size() != 0) {
			cout << "  " << " NAME ," <<" ID ," << "   EMAIL ,  " << "   BALANCE ,  " << " ROLE , " << "  PHONE NUMBER , " << "  AGE , " << " STATUS  ";
		}
		for (int i = 0; i < accounts.size(); i++) {
			if (accounts[i].getIsActive() == false) continue;
			cout << endl << counter << "." << accounts[i].getUserName() << "  " <<" #"<<accounts[i].getId() << "  " << accounts[i].getEmail() << "  " << accounts[i].getBalance()<< "  " << accounts[i].getRole() << "  " << accounts[i].getPhoneNumber()<<"     "<<accounts[i].getAge() <<"    " << (accounts[i].getIsActive() == true ? "Active" : "INactive");
			counter++;
		}
		cout << " \n}\n";
	}

	void Admin::displayInactiveAccounts() {
		loadAllAccountsFromDatabase();
		int counter = 1;
		cout << "\n Inactive Accounts:\n {\n ";
		if (accounts.size() != 0) {
			cout << "  " << " NAME ," << " ID ," << "   EMAIL ,  " << "   BALANCE ,  " << " ROLE , " << "  PHONE NUMBER , " << "  AGE , " << " STATUS  ";
		}
		for (int i = 0; i < accounts.size(); i++) {
			if (accounts[i].getIsActive() == true) continue;
			cout << endl << counter << "." << accounts[i].getUserName() << "  " <<accounts[i].getEmail() << "  " << accounts[i].getPhoneNumber();
			counter++;
		}
		cout << " \n}\n";
	}

	bool Admin::deactivateAccount(const string& accountEmail) {
		loadAllAccountsFromDatabase();
		for (int i = 0; i < accounts.size(); i++) {
			if (accounts[i].getEmail() == accountEmail) {
				if (accounts[i].getIsActive() == false) {
					cout << "\n" << accounts[i].getUserName() << " Account's is already Dactivated...";
					return true;
				}
				accounts[i].setIsActive(false);
				cout << "\n" << accounts[i].getUserName() << " Account's is deactivated ";
				accounts[i].updateThisInDatabase();
				return true;
			}
		}
		cout << "\n Deactivate Account :there is no Account with such an Email";
		return false;
	}

	bool Admin::activateAccount(const string& accountEmail) {
		loadAllAccountsFromDatabase();
		for (int i = 0; i < accounts.size(); i++) {
			if (accounts[i].getEmail() == accountEmail) {
				if (accounts[i].getIsActive() == true) {
					cout << "\n" << accounts[i].getUserName() << " Account's is already Active..";
					return true;
				}
				accounts[i].setIsActive(true);
				cout << "\n" << accounts[i].getUserName() << " Account's is Aactivated ";
				accounts[i].updateThisInDatabase();
				return true;
			}
		}
		cout << "\n Activate Account :there is no Account with such an Email";
		return false;
	}

	void Admin::adminMenu() {
		int choise = 0;
		while (choise != 11) {
			cout << "\n---------";

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
				<< "\n11. CLOSE This Menu";
			choise = getValidInput<int>("\n choose the operation: ");
			switch (choise) {
			case 1: {
				createNewAccount();
			}break;
			case 2:{
				string searchEmail;
				while (true) {
					cout << "\n Enter the Email for the Account to DISPLAY its Info: ";
					getline(cin, searchEmail);
					if (searchEmail == "stop")break;
					if (!displayInfoForAccount(searchEmail)) {
						cout << ", Try again, or write \"stop\": ";
						continue;
					}
					break;
				}
				
			}break;
			case 3: {
				string searchEmail;
				while (true) {
					cout << "\n Enter the Email for the Account to DELETE: ";
					getline(cin, searchEmail);
					if (searchEmail == "stop")break;
					if (!deleteAccount(searchEmail)) {
						cout << ", Try Again, or write \"stop\" : ";
						continue;
					}
					break;
				}
			}break;
			case 4: {
				string searchEmail;
				while (true) {
					cout << "\n Enter the Email for the Account to UPDATE: ";
					getline(cin, searchEmail);
					if (searchEmail == "stop")break;
					if (!updateAccount(searchEmail)) {
						cout << ", Try Again, or write \"stop\" : ";
						continue;
					}
					break;
				}
			}break;
			case 5: {
				string searchEmail;
				while (true) {
					cout << "\n Enter the Email for the Account to WITHDRAW from: ";
					getline(cin, searchEmail);
					if (searchEmail == "stop")break;
					if (!withdrawFromAccount(searchEmail)) {
						cout << ", Try Again, or write \"stop\" : ";
						continue;
					}
					break;
				}
			}break;
			case 6: {
				string searchEmail;
				while (true) {
					cout << "\n Enter the Email for the Account to DEPOSIT to it: ";
					getline(cin, searchEmail);
					if (searchEmail == "stop")break;
					if (!depositToAccount(searchEmail)) {
						cout << ", Try Again, or write \"stop\" : ";
						continue;
					}
					break;
				}
			}break;
			case 7: {
				displayActiveAccounts();
			}break;
			case 8: {
				displayInactiveAccounts();
			}break;
			case 9: {
				string searchEmail;
				while (true) {
					cout << "\n Enter the Email for the Account to DEACTIVATE it: ";
					getline(cin, searchEmail);
					if (searchEmail == "stop")break;
					if (!deactivateAccount(searchEmail)) {
						cout << ", Try again or write \"stop\": ";
						continue;
					}
					break;
				}
			}break;
			case 10: {
				string searchEmail;
				while (true) {
					cout << "\n Enter the Email for the Account to ACTIVATE it: ";
					getline(cin, searchEmail);
					if (searchEmail == "stop")break;
					if (!activateAccount(searchEmail)) {
						cout << ", Try again or write \"stop\": ";
						continue;
					}
					break;
				}  
			}break;
			case 11: {
				cout << "stoped..\n----------------------------------";
				cout << "\033[2J\033[1;1H";
			}break;
			default: {
				cout << "\nInvalid choice, select a valid option: ";
			}break;
			}
		}
	}
