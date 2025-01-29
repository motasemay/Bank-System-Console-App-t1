#ifndef ADMIN_H
#define ADMIN_H

#include "Customer.h"
#include <string>
#include<vector>

class Admin :public Customer {
private:
	vector<Account> accounts;
public:
	Admin();
	void createNewAccount();
	void displayInfoForAccount(const string& accountPhoneNumber);
	void deleteAccount(const string& accountPhoneNumber);
	void updateAccount(const string& accountPhoneNumber);
	void withdrawFromAccount(const string& accountPhoneNumber, double amount);
	void depositToAccount(const string& accountPhoneNumber, double amount);
	void displayActiveAccounts()const;
	void displayInactiveAccounts()const;
	void deactivateAccount(const string& accountPhoneNumber);
	void activateAccount(const string& accountPhoneNumber);
	void adminMenu();
};


#endif 

