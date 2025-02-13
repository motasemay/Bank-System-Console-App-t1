#ifndef ACCOUNT_H
#define ACCOUNT_H

#include <iostream>
#include <string>
#include <regex>
#include<fstream>
#include <sstream>
#include<vector>
using namespace std;

class Account {
private:
	int id;
	string role;
	string userName;
	string email;
	string password;
	string phoneNumber;
	string age;
	string balance;
	bool isActive;
	string accountTypeName;
public:
	Account();
	Account(const string& newBalance);
	Account(const string& newUserName, const string& newEmail, const string& newPassword, const string& newPhoneNumber, const string& newAge, const string& newBalance = "0.00", const string& newRole = "customer",const string& newAccountTypeName="Main");
	~Account();

	void saveToDatabase()const;
	void loadFromDatabase(const string& accountId);
	int idGenerator();
	void updateThisInDatabase() const;
	bool doesAccountExist(const string& checkName)const;
	void deleteFromDatabase() const;


	//validation
	template<typename T>
	T getValidInput(const string& text);
	bool userNameValidation(const string& UserName);
	bool emailValidation(const string& Email);
	bool passwordValidation(const string& testPassword);
	bool phoneNumberValidation(const string& phoneNumber);
	bool ageValidation(const string& Age);
	bool balanceValidation(const string& Balance);
	bool roleValidation(const string& Role);
	
	//SETTRS with out validation (for database loading)
	void setIdForced(int Id);
	void setRoleForced(const string& Role);
	void setUserNameForced(const string& UserName);
	void setEmailForced(const string& Email);
	void setPasswordForced(const string& Password);
	void setPhoneNumberForced(const string& PhoneNumber);
	void setAgeForced(const string& Age);
	void setBalanceForced(const string& Balance);
	void setIsActiveForced(bool IsActive);
	void setAccountTypeNameForced(const string& accTypeName);


	//SETTERS
	void setId(int Id);
	void setRole(const string& Role);
	void setUserName(const string& UserName);
	void setEmail(const string& Email);
	void setPassword(const string& Password);
	void setPhoneNumber(const string& PhoneNumber);
	void setAge(const string& Age);
	void setBalance(const string& Balance);
	void setIsActive(bool IsActive);
	void setAccountTypeName(const string& accTypeName);

	//GETTERS
	int getId()const;
	string getRole()const;
	string getUserName()const;
	string getEmail()const;
	string getPassword()const;
	string getPhoneNumber()const;
	string getAge()const;
	string getBalance()const;
	bool getIsActive()const;
	string getAccountTypeName() const;

	void displayAccountInfo();
	void withdraw(double amount);
	void deposit(double amount);
	void updateAccountInfo();

};
#endif 