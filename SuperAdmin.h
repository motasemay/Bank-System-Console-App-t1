#ifndef SUPERADMIN_H
#define SUPERADMIN_H

#include "Admin.h"

class SuperAdmin: public Admin {
public:
	void displayAdminAccounts();
	void displaySuperAdminAccounts();
	bool updateAccountRole(const string& targetEmail, const string& newRole)override;
	bool isAllowedOperation(const string& targetEmail)override;
	bool deleteAccount(const string& accountPhoneNumber)override;
	void superAdminMenu();

};
#endif
