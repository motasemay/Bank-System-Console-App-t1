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
	virtual bool displayInfoForAccount(const string& accountPhoneNumber);
	virtual bool deleteAccount(const string& accountPhoneNumber);
	virtual bool updateAccount(const string& accountPhoneNumber);
	virtual bool withdrawFromAccount(const string& accountPhoneNumber);
	virtual bool depositToAccount(const string& accountPhoneNumber);
	void displayActiveAccounts();
	void displayInactiveAccounts();
	virtual bool deactivateAccount(const string& accountPhoneNumber);
	virtual bool activateAccount(const string& accountPhoneNumber);
	void adminMenu();
};


#endif 

