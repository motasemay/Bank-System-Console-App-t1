#ifndef CUSTOMER_H
#define CUSTOMER_H

#include <iostream>
#include <string>
#include <regex>
#include<fstream>
#include <sstream>
#include<vector>
#include "Account.h"

class Customer : public Account {
	vector<Account> customerAccounts;
public:
	void addRelatedAccount();
	void customerMenu();
	void loadRelatedAccounts(const string& customerEmail);
};	

#endif 

