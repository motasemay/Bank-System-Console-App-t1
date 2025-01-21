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
	static int idCounter;
	int id;
	string role;
	string userName;
	string email;
	string password;
	string phoneNumber;
	string age;
	string balance;
	bool isActive;
public:
	Account();
	Account(const string& newBalance);
	Account(const string& newUserName, const string& newEmail, const string& newPassword, const string& newPhoneNumber, const string& newAge, const string& newBalance = "0.00", const string& newRole = "customer");
	~Account();

	void saveToDatabase()const;
	void loadFromDatabase(int accountId);
	int idGenerator();
	void updateThisInDatabase() const;
	bool doesAccountExist(const string& checkName)const;

	//validation
	bool userNameValidation(const string& UserName);
	bool emailValidation(const string& Email);
	bool passwordValidation(const string& testPassword);
	bool phoneNumberValidation(const string& phoneNumber);
	bool ageValidation(const string& Age);
	bool balanceValidation(const string& Balance);
	
	//SETTERS
	void setRole(const string& Role);
	void setUserName(const string& UserName);
	void setEmail(const string& Email);
	void setPassword(const string& Password);
	void setPhoneNumber(const string& PhoneNumber);
	void setAge(const string& Age);
	void setBalance(const string& Balance);
	void setIsActive(bool IsActive);

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

	void DisplayAccountInfo();
	void withdraw(double amount);
	void deposit(double amount);
	void updateAccountInfo();
};
#endif 