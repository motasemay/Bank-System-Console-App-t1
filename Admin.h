#ifndef ADMIN_H
#define ADMIN_H

#include "Customer.h"
#include <string>
#include<vector>

class Admin :public Customer {
protected:
	vector<Account> accounts;
public:
	Admin();
	void loadAllAccountsFromDatabase();
	virtual bool isAllowedOperation(const string& targetEmail);
	void createNewAccount();
	virtual bool updateAccountRole(const string& targetEmail, const string& newRole);
	bool displayInfoForAccount(const string& accountPhoneNumber);
	virtual bool deleteAccount(const string& accountPhoneNumber);
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

