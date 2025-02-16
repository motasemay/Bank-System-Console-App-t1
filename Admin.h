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
	void loadAllAccountsFromDatabase();
	bool isAllowedOperation(const string& targetEmail);
	void createNewAccount();
	bool displayInfoForAccount(const string& accountPhoneNumber);
	bool deleteAccount(const string& accountPhoneNumber);
	bool updateAccount(const string& accountPhoneNumber);
	bool withdrawFromAccount(const string& accountPhoneNumber);
	bool depositToAccount(const string& accountPhoneNumber);
	void displayActiveAccounts();
	void displayInactiveAccounts();
	bool deactivateAccount(const string& accountPhoneNumber);
	bool activateAccount(const string& accountPhoneNumber);
	void adminMenu();
};


#endif 

