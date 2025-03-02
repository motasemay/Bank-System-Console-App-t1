#include "Bank.h"
#include "Customer.h"
#include "Admin.h"
#include "SuperAdmin.h"
#include <iostream>
#include <string>
#include <regex>
#include<fstream>
#include <sstream>
#include<vector>
using namespace std;
//just for test branches
bool Bank::authenticateUser() {
	const int maxAttempts = 5;
	while (true)
	{
		int loginAttempts = 0;
		while (loginAttempts < maxAttempts) {
			cout << "\n\n------ LOG IN------\n";
			string Email = "", Password = "";
			while (true) {
				cout << "\n Enter your Email: ";
				getline(cin, Email);
				if (Email.size() == 0) {
					cout << "\n Cannot Submit an Empty Email, try Again:";
					continue;
				}
				break;
			}
			while (true) {
				cout << "\n Enter your Passrwod: ";
				getline(cin, Password);
				if (Password.size() == 0) {
					cout << "\n Cannot Submit an Empty Password, try Again:";
					continue;
				}
				break;
			}
			ifstream file("usersDatabase.txt");
			if (!file) {
				cout << "\n Error: usersDatabase, cannot find the file for authentication.";
				return false;
			}
			string Role = "none";
			bool wrongPassword = false;
			string line;
			string storedId, storedRole, storedUserName, storedEmail, storedPassword, storedPhoneNumber, storedAge, storedBalance, storedIsActive;
			while (getline(file, line)) {
				stringstream recordLine(line);
				getline(recordLine, storedId, ',');
				getline(recordLine, storedRole, ',');
				getline(recordLine, storedUserName, ',');
				getline(recordLine, storedEmail, ',');
				getline(recordLine, storedPassword, ',');
				getline(recordLine, storedPhoneNumber, ',');
				getline(recordLine, storedAge, ',');
				getline(recordLine, storedBalance, ',');
				getline(recordLine, storedIsActive, ',');
				if (Email == storedEmail) {
					if (Password == storedPassword) {
						Role = storedRole;
						file.close();
						break;
					}
					else {
						wrongPassword = true;
						file.close();
						break;
					}
				}
			}
			if (wrongPassword) {
				cout << "\033[2J\033[1;1H";
				cout << "\n Wrong Password, Try Again:  (remeining Attempts:" << maxAttempts - loginAttempts - 1 << ").";
				file.close();
				loginAttempts++;
				continue;
			}
			else if (Role == "none") {
				cout << "\033[2J\033[1;1H";
				cout << "\n Invalid Email, Try Again:  (remeining Attempts:" << maxAttempts - loginAttempts - 1 << ").";
				file.close();
				loginAttempts++;
				continue;
			}

			if (Role == "customer" || Role == "Customer") {
				cout << "\033[2J\033[1;1H";
				cout << "\n LogIn successfully.";
				Customer loginCustomer;
				loginCustomer.loadFromDatabase(storedId);
				loginCustomer.loadRelatedAccounts(storedEmail);
				loginCustomer.customerMenu();
				loginAttempts = 0;
				continue;
			}
			else if (Role == "admin" || Role == "Admin") {
				cout << "\033[2J\033[1;1H";
				cout << "\n LogIn successfully (Admin).";
				Admin loginAdmin;
				loginAdmin.loadFromDatabase(storedId);
				loginAdmin.loadRelatedAccounts(storedEmail);
				loginAdmin.loadAllAccountsFromDatabase();
				loginAdmin.adminMenu();
				loginAttempts = 0;
				continue;
			}
			else if (Role == "superadmin") {
				cout << "\033[2J\033[1;1H";
				cout << "\n LogIn successfully (Super Admin).";
				SuperAdmin loginSuperAdmin;
				loginSuperAdmin.loadFromDatabase(storedId);
				loginSuperAdmin.loadRelatedAccounts(storedEmail);
				loginSuperAdmin.loadAllAccountsFromDatabase();
				loginSuperAdmin.superAdminMenu();
				loginAttempts = 0;
				continue;
			}
			else {
				cout << "\033[2J\033[1;1H";
				cout << "\n Invalid Authentication Token, you are not allowed to Enter The Bank System.";
				continue;
			}
		}
		cout << "\033[2J\033[1;1H";
		cout << "\n you are BLOKED!, To many attempts." << endl;
		return false;
	}
}
