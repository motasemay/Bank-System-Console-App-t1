#include "SuperAdmin.h"
#include <iostream>
using namespace std;

void SuperAdmin::displayAdminAccounts()
{
	loadAllAccountsFromDatabase();
	int counter = 1;
	cout << "\n ADMINS: \n [ \n";
	if (!accounts.empty()) {
		cout << "         " << " NAME ," << " ID ," << "   EMAIL ,  " << "   ACCOUNT TYPE ,  " << "   BALANCE ,  " << " ROLE , " << "  PHONE NUMBER , " << "  AGE , " << " STATUS  ";
	}
	for (int i = 0; i < accounts.size(); i++) {
		if (accounts[i].getRole() == "admin") {
		cout<<"\nadmin("<<counter<<") : " << accounts[i].getUserName() << "  " << " #" << accounts[i].getId() << "  " << accounts[i].getEmail() << "  " << accounts[i].getAccountTypeName() << "  " << accounts[i].getBalance() << "  " << accounts[i].getRole() << "  " << accounts[i].getPhoneNumber() << "     " << accounts[i].getAge() << "    " << (accounts[i].getIsActive() == true ? "Active" : "INactive");
		counter++;
		}
	}
	cout << " \n]\n";
}

bool SuperAdmin::isAllowedOperation(const string& targetEmail)
{
	if (!doesAccountExist(targetEmail)) {
		cout << "\n Error, there is no account with ( " << targetEmail << " ) email in the system.\n";
		return false;
	}
	for (int i = 0; i < accounts.size(); i++) {
		if (accounts[i].getEmail() == targetEmail) {
			if (accounts[i].getRole() == "branch")continue;
			return accounts[i].getRole() != "superadmin";
		}
	}
	return false;
}

bool SuperAdmin::displayInfoForAccount(const string& accountEmail) {
	loadAllAccountsFromDatabase();
	if (!doesAccountExist(accountEmail)) {
		cout << "\n Error, there is no account with ( " << accountEmail << " ) email in the system.\n";
		return false;
	}
	if (!isAllowedOperation(accountEmail)) {
		cout << "\n Unauthorized Operation, Cannot Apply this operation to a SuperAdmin Account.\n";
		return false;
	}
	for (int i = 0; i < accounts.size(); i++) {
		if (accounts[i].getEmail() == accountEmail) {
			accounts[i].displayAccountInfo();
			return true;
		}
	}
	cout << "\n UnExpected Error Happend!! , (Display Account's Info)\n";
	return false;
}


bool SuperAdmin::deleteAccount(const string& accountEmail) {
	loadAllAccountsFromDatabase();
	if (!doesAccountExist(accountEmail)) {
		cout << "\n Error, there is no account with ( " << accountEmail << " ) email in the system.\n";
		return false;
	}
	if (!isAllowedOperation(accountEmail)) { //ASK : im i need to override just to use the superadmin version of isAllow..
		cout << "\n Unauthorized Operation, Cannot Apply this operation to a SuperAdmin Account.\n";
		return false;
	}
	bool accountFound = false;
	for (int i = 0; i < accounts.size(); i++) {
		if (accounts[i].getEmail() == accountEmail) {
			string mainUserName = accounts[i].getUserName();
			accountFound = true;

			string confirm;
			cout << "\n Are you sure you want to delete " << mainUserName << "'s Account with " << accountEmail << " and all related Account's? (y:Yes, n:No): ";
			getline(cin, confirm);
			if (confirm == "y" || confirm == "Y") {
				for (int j = 0; j < accounts.size(); j++) {
					if (accounts[j].getEmail() == accountEmail) {
						accounts[j].deleteFromDatabase();

						if (accounts[j].getUserName() == mainUserName)
							cout << "\n-" << mainUserName << "'s Account (Main) Deleted successfully\n";
						else
							cout << "\n-" << mainUserName << "'s Related Account Deleted successfully\n";
					}
				}
				accounts.erase(remove_if(accounts.begin(), accounts.end(),
					[&](const Account& acc) { return acc.getEmail() == accountEmail; }),
					accounts.end());
				return true;
			}
			else {
				cout << "\n Deletion Proccess CANCELED.." << endl;
				return false;
			}
		}

	}
	cout << "\n UnExpected Error Happend!! , (Delete Account Operation)\n";
	return false;
}

bool SuperAdmin::updateAccount(const string& accountEmail)
{
	loadAllAccountsFromDatabase();
	if (!doesAccountExist(accountEmail)) {
		cout << "\n Error, there is no account with ( " << accountEmail << " ) email in the system.\n";
		return false;
	}
	if (!isAllowedOperation(accountEmail)) {
		cout << "\n Unauthorized Operation, Cannot Apply this operation to a SuperAdmin Account.\n";
		return false;
	}
	for (int i = 0; i < accounts.size(); i++) {
		if (accounts[i].getEmail() == accountEmail) {
			accounts[i].updateAccountInfo();
			cout << "\n" << accounts[i].getUserName() << " Account's info is updated";
			return true;
		}
	}
	cout << "\n UnExpected Error Happend!! , (Update Account Operation)\n";
	return false;
}

bool SuperAdmin::withdrawFromAccount(const string& accountEmail)
{
	loadAllAccountsFromDatabase();
	if (!doesAccountExist(accountEmail)) {
		cout << "\n Error, there is no account with ( " << accountEmail << " ) email in the system.\n";
		return false;
	}
	if (!isAllowedOperation(accountEmail)) {
		cout << "\n Unauthorized Operation, Cannot Apply this operation to an Admin Account.\n";
		return false;
	}
	double amount;
	for (int i = 0; i < accounts.size(); i++) {
		if (accounts[i].getEmail() == accountEmail) {
			amount = getValidInput<double>("\n how much you want to withdraw:");
			accounts[i].withdraw(amount);
			//FIXTHIS: cout << "\n" << amount << " is withdrawed from " << accounts[i].getUserName() << "'s Account";
			return true;
		}
	}
	cout << "\n UnExpected Error Happend!! , (Withdraw From An Account Operation)\n";
	return false;
}

bool SuperAdmin::depositToAccount(const string& accountEmail) {
	loadAllAccountsFromDatabase(); //ASK , can i use this from admin?
	if (!doesAccountExist(accountEmail)) {
		cout << "\n Error, there is no account with ( " << accountEmail << " ) email in the system.\n";
		return false;
	}
	if (!isAllowedOperation(accountEmail)) {
		cout << "\n Unauthorized Operation, Cannot Apply this operation to a SuperAdmin Account.\n";
		return false;
	}
	double amount;
	for (int i = 0; i < accounts.size(); i++) {
		if (accounts[i].getEmail() == accountEmail) {
			amount = getValidInput<double>("\n how much you want to deposit: ");
			accounts[i].deposit(amount);
			return true;
		}
	}
	cout << "\n UnExpected Error Happend!! , (Depost to An Account Operation)\n";
	return false;
}

bool SuperAdmin::deactivateAccount(const string& accountEmail) {
	loadAllAccountsFromDatabase();
	if (!doesAccountExist(accountEmail)) {
		cout << "\n Error, there is no account with ( " << accountEmail << " ) email in the system.\n";
		return false;
	}
	if (!isAllowedOperation(accountEmail)) {
		cout << "\n Unauthorized Operation, Cannot Apply this operation to a SuperAdmin Account.\n";
		return false;
	}
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
	cout << "\n UnExpected Error Happend!! , (DeActivate An Account Operation)\n";
	return false;
}

bool SuperAdmin::activateAccount(const string& accountEmail) {
	loadAllAccountsFromDatabase();
	if (!doesAccountExist(accountEmail)) {
		cout << "\n Error, there is no account with ( " << accountEmail << " ) email in the system.\n";
		return false;
	}
	if (!isAllowedOperation(accountEmail)) {
		cout << "\n Unauthorized Operation, Cannot Apply this operation to a SuperAdmin Account.\n";
		return false;
	}
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
	cout << "\n UnExpected Error Happend!! , (Activate An Account Operation)\n";
	return false;
}

void SuperAdmin::displaySuperAdminAccounts()
{
	loadAllAccountsFromDatabase();
	int counter = 1;
	cout << "\n Super Admins: \n [ \n";
	if (!accounts.empty()) {
		cout << "             " << " NAME ," << " ID ," << "   EMAIL ,  " << "   ACCOUNT TYPE ,  " << "   BALANCE ,  " << " ROLE , " << "  PHONE NUMBER , " << "  AGE , " << " STATUS  ";
	}
	for (int i = 0; i < accounts.size(); i++) {
		if (accounts[i].getRole() == "superadmin") {
		cout<<"\nSuperAdmin("<<counter<<") : " << accounts[i].getUserName() << "  " << " #" << accounts[i].getId() << "  " << accounts[i].getEmail() << "  " << accounts[i].getAccountTypeName() << "  " << accounts[i].getBalance() << "  " << accounts[i].getRole() << "  " << accounts[i].getPhoneNumber() << "     " << accounts[i].getAge() << "    " << (accounts[i].getIsActive() == true ? "Active" : "INactive");
		counter++;
		}
	}
	cout << " \n].\n";
}

bool SuperAdmin::updateAccountRole(const string& targetEmail, const string& newRole) {
	loadAllAccountsFromDatabase();
	if (!doesAccountExist(targetEmail)) {
		cout << "\n Error, there is no account with ( " << targetEmail << " ) email in the system.\n";
		return false;
	}
	if (!isAllowedOperation(targetEmail)) {
		cout << "\n Unauthorized Operation, Cannot Apply this operation to a SuperAdmin Account.\n";
		return false;
	}
	if (newRole == "superadmin") {
		string confirm = "";
		cout << "\n WARINING!!\n\n Very Critical Operation!\n\n - Giving a SuperAdmin Role to an Account Will give him a Full Authorizaion to all system aspects,"
			<< "\n and you cannot take this Role from him next\n Are You Sure You Want to Continue? (Y/N) : ";
		getline(cin, confirm);
		if (!(confirm == "Y" || confirm == "y")) {
			cout << "\n Canceled Operation\n";
			return false;
		}
	}
	if (!roleValidation(newRole)) {
		cout << "\n Unauthorized Operation, There is such a Role in the System!\n";
		return false;
	}
	for (int i = 0; i < accounts.size(); i++) {
		if (accounts[i].getEmail() == targetEmail) {
			if (accounts[i].getRole() == "branch")continue;
			if (accounts[i].getRole() == newRole) {
				cout << "\n account is already a " << newRole << "!\n";
				return true;
			}
			if (accounts[i].getRole() == "customer"||accounts[i].getRole()=="admin") {
				string confirm = "";
				cout << "\n Critical Operation:\nAre You Sure you Want to give " << accounts[i].getUserName() << "'s Account\n"
					<< "A " << newRole << " Role? (write Y or y to confirm) : ";
				getline(cin, confirm);
				if (confirm == "y" || confirm == "Y") {
					accounts[i].setRoleForced(newRole);
					accounts[i].updateThisInDatabase();
					cout << endl << accounts[i].getUserName() << "'s Account with [" << accounts[i].getId() << "] id and [ " << accounts[i].getEmail() << " ] email \n"
						<< " is Now a " << newRole << "..\n";
					return true;
				}
				else {
					cout << "\n Operation Canceled.\n";
					return false;
				}
			}
		}
	}
	cout << "\n UnExpected Error Happend!!, (Update Account's Role Operation)\n";
	return false;
}

void SuperAdmin::superAdminMenu()
{
	int choise = -1;
	while (choise != 14) {
		cout << "\n - - - - - - - -";
	displayAdminAccounts();
	displayActiveAccounts();
	displayInactiveAccounts();
		cout << "\n - - - - - - - -";
		cout<<"\n Super Admin's Menu : "
			<<"\n1.Updata An Account's Role."
			<<"\n2.Display SuperAdmin's Accounts."
			<<"\n3.Display Admin's Accounts."
			<<"\n  ----"
			<< "\n4.Create A New Account."
			<< "\n5.Display An Account's Info."
			<< "\n6.Delete An Account."
			<< "\n7.Update An Account."
			<< "\n8.Withdraw from An Account."
			<< "\n9.Deposit To An Account."
			<< "\n10.Display Active Accounts."
			<< "\n11.Display InActive Accounts"
			<< "\n12.Deactivate An Account."
			<< "\n13.Activate An Account."
			<< "\n14.Log Out.";

		choise = getValidInput<int>("\n choose the operation: ");
		switch (choise) {
		case 1: {
			string searchEmail,Role;
			while (true) {
				cout << "\n Enter the Email for the Account to Change it's Role: ";
				getline(cin, searchEmail);
				if (searchEmail == "stop") {
					cout << "\033[2J\033[1;1H";
					break;
				}
				cout << "\n Enter the Role you Want to give it: (\"customer\", \"admin\", \"superadmin\"): ";
				getline(cin, Role);
				if (!updateAccountRole(searchEmail, Role)) {
					cout << ", Try again or write \"stop\": ";
					continue;
				}
				break;
			}
		}break;
		case 2: {
			displaySuperAdminAccounts();
		}break;
		case 3: {
			displayAdminAccounts();
		}break;
		case 4: {
			createNewAccount();

		}break;
		case 5: {
			string searchEmail;
			while (true) {
				cout << "\n Enter the Email for the Account to DISPLAY its Info: ";
				getline(cin, searchEmail);
				if (searchEmail == "stop") {
					break;
				}
				if (!displayInfoForAccount(searchEmail)) {
					cout << ", Try again, or write \"stop\": ";
					continue;
				}
				break;
			}
		}break;
		case 6: {
			string searchEmail;
			while (true) {
				cout << "\n Enter the Email for the Account to DELETE: ";
				getline(cin, searchEmail);
				if (searchEmail == "stop") {
					cout << "\033[2J\033[1;1H";
					break;
				}
				if (!deleteAccount(searchEmail)) {
					cout << ", Try Again, or write \"stop\" : ";
					continue;
				}
				break;
			}
		}break;
		case 7: {
			string searchEmail;
			while (true) {
				cout << "\n Enter the Email for the Account to UPDATE: ";
				getline(cin, searchEmail);
				if (searchEmail == "stop") {
					cout << "\033[2J\033[1;1H";
					break;
				}
				if (!updateAccount(searchEmail)) {
					cout << ", Try Again, or write \"stop\" : ";
					continue;
				}
				break;
			}
		}break;
		case 8: {
			string searchEmail;
			while (true) {
				cout << "\n Enter the Email for the Account to WITHDRAW from: ";
				getline(cin, searchEmail);
				if (searchEmail == "stop") {
					cout << "\033[2J\033[1;1H";
					break;
				}
				if (!withdrawFromAccount(searchEmail)) {
					cout << ", Try Again, or write \"stop\" : ";
					continue;
				}
				break;
			}
		}break;
		case 9: {	
			string searchEmail;
			while (true) {
				cout << "\n Enter the Email for the Account to DEPOSIT to it: ";
				getline(cin, searchEmail);
				if (searchEmail == "stop") {
					cout << "\033[2J\033[1;1H";
					break;
				}
				if (!depositToAccount(searchEmail)) {
					cout << ", Try Again, or write \"stop\" : ";
					continue;
				}
				break;
			}
		}break;
		case 10: {
			displayActiveAccounts();
		}break;
		case 11: {
			displayInactiveAccounts();
		}break;
		case 12: {
			string searchEmail;
			while (true) {
				cout << "\n Enter the Email for the Account to DEACTIVATE it: ";
				getline(cin, searchEmail);
				if (searchEmail == "stop") {
					cout << "\033[2J\033[1;1H";
					break;
				}
				if (!deactivateAccount(searchEmail)) {
					cout << ", Try again or write \"stop\": ";
					continue;
				}
				break;
			}
		}break;
		case 13: {
			string searchEmail;
			while (true) {
				cout << "\n Enter the Email for the Account to ACTIVATE it: ";
				getline(cin, searchEmail);
				if (searchEmail == "stop") {
					cout << "\033[2J\033[1;1H";
					break;
				}
				if (!activateAccount(searchEmail)) {
					cout << ", Try again or write \"stop\": ";
					continue;
				}
				break;
			}
		}break;
		case 14: {
			cout << "Logged Out..\n----------------------------------";
			cout << "\033[2J\033[1;1H";
		}break;
		default: {
			cout << "\nInvalid choice, select a valid option: ";
		}break;
		}
	}
}
