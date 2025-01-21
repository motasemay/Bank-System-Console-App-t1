#include "Account.h"
#include <iostream>
#include <string>
#include <regex>
#include<fstream>
#include <sstream>
#include<vector>
using namespace std;

int Account::idCounter = 0;  //need to be rechecked start counting id 's

Account::Account() {
	id = idGenerator();
	role = "customer";
	userName = "";
	email = "";
	password = "";
	phoneNumber = "";
	age = "";
	balance = "0.00";
	isActive = true;
	//saveToDatabase();
//	auditFile.open("audit.txt", ios::app);
//	if (!auditFile)
//		cout << "\n unable to open audit file";
//	else
//		auditFile << "\n-Auditting " << getUserName() << " Account is statered.";
}

Account::Account(const string& newBalance) {
	id = idGenerator();
	setRole("customer");
	userName = "";
	email = "";
	password = "";
	phoneNumber = "";
	age = "";
	setBalance(newBalance);
	isActive = true;
	//saveToDatabase();

	/*auditFile.open("audit.txt", ios::app);
	if (!auditFile)
		cout << "\n unable to open audit file";
	else
		auditFile << "--Auditting " << getUserName() << "'s Account is statered.";
		*/
}

Account::Account(const string& newUserName, const string& newEmail, const string& newPassword, const string& newPhoneNumber, const string& newAge, const string& newBalance, const string& newRole) {
	id = idGenerator();
	setRole("customer");
	setUserName(newUserName);
	setEmail(newEmail);
	setPassword(newPassword);
	setPhoneNumber(newPhoneNumber);
	setAge(newAge);
	setBalance(newBalance);
	setIsActive(true);
	//	saveToDatabase();

	/*	auditFile.open("audit.txt", ios::app);
		if (!auditFile)
			cout << "\n unable to open audit file";
		else
			auditFile << "---Auditting " << getUserName() << "'s Account is statered.";*/
}

Account::~Account() {
	/*		DisplayAuditFile();
		if (auditFile.is_open()) {
			auditFile << "\n -Audit file is closed for " << getUserName() << " Account.";
			auditFile.close();
		}*/
		//clearAuditFile();
}

// funciton for database using text files:

//create the user Record
void Account:: saveToDatabase()const {
	ofstream file("usersDatabase.txt", ios::app);
	if (!file) {
		cout << "\n ERROR : users database, Cannot open file to save the user's data..";
		return;
	}
	file << id << "," << role << "," << userName << "," << email << "," << password << "," << phoneNumber << "," << age << "," << balance << "," << (isActive ? "Active" : "Inactive") << "\n";
	file.close();
	cout << "\n Users Database: Account saved successfully..";
}

//load the user data depend on the id in the userDatabase ( clone it to the current account's data members )
void Account:: loadFromDatabase(int accountId) {
	ifstream file("usersDatabase.txt");
	if (!file) {
		cout << "\n ERROR : users database, Cannot open file to load the user data..";
		return;
	}
	string line;
	while (getline(file, line)) {
		stringstream recordLine(line);
		string column;
		int currentId;
		getline(recordLine, column, ',');
		currentId = stoi(column);
		string Role, UserName, Email, Password, PhoneNumber;
		string Age;
		bool IsActive;
		string Balance;

		if (currentId == accountId) {
			getline(recordLine, Role, ',');
			setRole(Role);
			getline(recordLine, UserName, ',');
			setUserName(UserName);
			getline(recordLine, Email, ',');
			setEmail(Email);
			getline(recordLine, Password, ',');
			setPassword(Password);
			getline(recordLine, PhoneNumber, ',');
			setPhoneNumber(PhoneNumber);
			getline(recordLine, column, ',');
			setAge(Age);
			getline(recordLine, column, ',');
			setBalance(Balance);
			getline(recordLine, column, ',');
			IsActive = (column == "Active"); // t or f
			setIsActive(IsActive);
			file.close();
			return;
		}
	}
	file.close();
	cout << "\n Users Database: Account not found..";
}

//static int idGenerator() {
	//	fstream readFile("idFile.txt");
	//	if (!readFile) {
	//		cout << "\n idFile, Error: cannot open the file to generate a new id";
	//		return 0;
	//	}
	//	string fileId;
	//	
	//	getline(readFile, fileId);
	//	readFile.close();
	//	
	//	fstream writeFile("idFile.txt");
	//	if (fileId == "") {		
	//		writeFile << 00001;
	//		return 1;
	//	}
	//	else {
	//		getline(writeFile, fileId);
	//		
	//		int newNumId = stoi(fileId);
	//		newNumId++;
	//		writeFile << newNumId;
	//		return newNumId;
	//	}
	//}
int Account:: idGenerator() { // problem: increase the number by 4 each time!!!
	int currentId = 0;
	ifstream inFile("idFile.txt");
	if (!inFile) {
		ofstream wFile("idFile.txt");
		if (!wFile) {
			cout << "\n id File, Error: cannot create this file";
			return -1;
		}
		currentId = 1;
		wFile << currentId;
		wFile.close();
		return currentId;
	}
	//file is exist
	inFile >> currentId;
	inFile.close();
	currentId++;
	//update the id in the file
	ofstream wFile("idFile.txt", ios::out);
	if (!wFile) {
		cout << "\nid File, Error: cannot write to this file";
		return -1;
	}
	wFile << currentId;
	wFile.close();
	return currentId;
}

// after changing the data members of the current object (RAM), this funciton will apply these changes of it in the Database 
void Account:: updateThisInDatabase() const {
	// clone the data base to a vector of strings to search for the current Account Id in it to update
	vector<string> databaseLines;
	ifstream inFile("usersDatabase.txt");
	if (inFile) {
		string line;
		while (getline(inFile, line)) {
			databaseLines.push_back(line); // full userdatabase in the vecotr
		}
		inFile.close();
	}
	else {
		cout << "\n ERROR : users database, Cannot open file to update..";
		return;
	}
	bool isFound = false;
	//edit the record data in the vector(still not changed in the file)
	for (int i = 0; i < databaseLines.size(); ++i) {
		stringstream currentLine(databaseLines[i]);
		string column;
		int currentId;
		getline(currentLine, column, ',');
		currentId = stoi(column);
		cout << "currentI" << currentId;
		if (currentId == this->id) {
			databaseLines[i] = to_string(this->id) + "," + this->role + "," + this->userName + "," + getEmail() + "," + getPassword() + "," + getPhoneNumber() + "," + getAge() + "," + getBalance() + "," + (getIsActive() ? "Active" : "Inactive");
			isFound = true;
			break;
		}
	}
	if (!isFound) {
		cerr << "\nAccount not found in the database for update" << endl;
		return;
	}
	// return the updataed data to the userDatabase file ( edit the file)
	ofstream outFile("usersDatabase.txt", ios::trunc); // Truncate to overwrite
	if (outFile) {
		for (int i = 0; i < databaseLines.size(); i++) {
			outFile << databaseLines[i] << endl;

		}
		outFile.close();
		cout << "\n Users Database: Account updateddd successfully..";
	}
	else {
		cout << "\n ERROR : users database, Cannot open file to update..";
	}
}

bool Account::doesAccountExist(const string& checkName)const {
	ifstream file("usersDatabase.txt");
	if (!file.is_open()) {
		cout << "\n Users Database: Error: cannot open file to check if the user Exists";
		return false;   // doubleCheck HERE
	}
	string line;
	while (getline(file, line)) {
		stringstream currentLine(line); //new librarie
		//this is the record structure: 
		// id,role,name,email,password,phoneNumber,age,balance,isActive
		//8,admin,motasem,motasem@gmail.com,motasem11,0569676250,26,5152,Active
		string columnn;
		getline(currentLine, columnn, ','); //skip id
		getline(currentLine, columnn, ',');  //skip role
		getline(currentLine, columnn, ','); //reach the userName
		if (checkName == columnn)
			return true;
	}
	return false;  //finsh without find
}
//END OF functions for the database

//validation
bool Account:: userNameValidation(const string& UserName) {
	/*	if (UserName == "" || UserName == " " || UserName.length() < 3 || UserName.length() > 50) {
			cout << "\n Invalid User Name. ";
			return false;
		}*/
	regex userNameRegex("^[a-zA-Z_-]{3,50}$");
	if (!regex_match(UserName, userNameRegex)) {
		cout << "\n Regex:  Invalid User Name. ";
		return false;
	}
	if (doesAccountExist(UserName)) {
		cout << "\n this userName already exists";
		return false;
	}
	return true;
}

bool Account::emailValidation(const string& Email) {
	const regex emailRegex = regex(R"(^[a-zA-Z0-9.!#$%&'*+\/=?^_`{|}~-]+@[a-zA-Z0-9-]+(?:\.[a-zA-Z0-9-]+)*$)");
	if (regex_match(Email, emailRegex)) {
		return true;
	}
	cout << "\n Invalid Email value";
	return false;
}

bool Account::passwordValidation(const string& testPassword) {
	if (testPassword.length() < 8) {
		cout << "\n Invalid Password.";
		return 0;
	}
	return 1;
}

bool Account:: phoneNumberValidation(const string& phoneNumber) {
	for (int i = 0; i < phoneNumber.length(); i++) {
		if (!isdigit(phoneNumber[i])) {
			cout << "\nInvalid phone number: must contain only digits";
			return false;
		}
	}
	if (phoneNumber.length() != 10) {
		cout << "\nInvalid phone number: must be exactly 10 digits";
		return false;
	}
	regex phoneRegex("^\\+?[1-9]\\d{1,14}$|^\\d{10}$");
	if (!regex_match(phoneNumber, phoneRegex)) {
		cout << "\nInvalid Phone Number.";
		return false;
	}
	return true;
}

bool Account::ageValidation(const string& Age) {
	regex numericRegex("^[0-9]+$");
	if (!regex_match(Age, numericRegex)) {
		cout << "\nInvalid age, age must be a numeric value.";
		return false;
	}
	int intAge = stoi(Age);
	if (!(intAge > 0 && intAge < 130)) {
		cout << "\n Invalid Age, age must be between 0 and 130";
		return false;
	}
	return true;
}

bool Account::balanceValidation(const string& Balance) {
	double doubleBalance = stod(Balance);
	if (!(doubleBalance >= 0 && doubleBalance < 100000)) {
		cout << "\n Invalid Balance, balance must not exceed 100,000 and must not be negative value";
		return false;
	}
	else {
		return true;
	}
}

//SETTRS
void Account::setRole(const string& Role) {
	role = Role;
}

void Account::setUserName(const string& UserName) {

	if (userNameValidation(UserName)) {
		userName = UserName;
	}
	else {
		cout << "\n cannot SET this as UserName";
		return;
	}
}

void Account::setEmail(const string& Email) {
	if (emailValidation(Email)) {
		email = Email;
	}
	else {
		cout << "\n Invalid Email format";
	}
}

void Account::setPassword(const string& Password) {
	if (passwordValidation(Password))
		password = Password;
}

void Account::setPhoneNumber(const string& PhoneNumber) {
	if (phoneNumberValidation(PhoneNumber))
	{
		phoneNumber = PhoneNumber;
	}
}

void Account::setAge(const string& Age) {
	if (ageValidation(Age)) {
		age = Age;
	}
	else
	{
		cout << "\n Invalid Age";
		return;
	}
}

void Account::setBalance(const string& Balance) {
	if (balanceValidation(Balance))
		balance = Balance;
	else {
		cout << "\n Balance Setter : ERror during setting the new balance";
		return;
	}
}

void Account::setIsActive(bool IsActive) {
	isActive = IsActive;
}

//GETTERS
int Account::getId()const { return id; }
string Account::getRole()const { return role; }
string Account::getUserName()const { return userName; }
string Account::getEmail()const { return email; }
string Account::getPassword()const { return password; }
string Account::getPhoneNumber()const { return phoneNumber; }
string Account::getAge()const { return age; }
string Account::getBalance()const { return balance; }
bool Account::getIsActive()const { return isActive; }

/*void DisplayAuditFile()const {
		ifstream auditFile("audit.txt");
		if (auditFile.is_open()) {
			cout << "\n\n-------------------------------------------------\n the Audit file content: ";
			string auditLine;
			while (getline(auditFile, auditLine))
				cout << "\n" << auditLine;

			cout << "\n--------------------------------------------------";
			auditFile.close();
		}
		else {
			cout << "\n Cannot open audit file....";
		}
	}*/
void Account::DisplayAccountInfo() { //read account info
/*	if (auditFile.is_open()) {
		auditFile << "\n- Displayed User Information for " << getUserName();
	}
	else {
		cout << "\n Audit file is not available in DisplayAccountInfo function.";
	}
	*/
	cout << endl<<endl << getUserName() << " Account info: \n"
		<<"ID: #"<<getId()<<" \n"
		<< "Balance= [ " << getBalance() << " ]\n"
		<< "Email : " << getEmail() << endl
		<< "Password : " << getPassword() << endl
		<< "PhoneNumber is :" << getPhoneNumber() << endl
		<< "age is : " << getAge() << endl
		<< "Status: " << (getIsActive() ? "Active" : "NOT Active")
		<<"\n----------------\n";
}

//able to withdraw money from the relevant account.
void Account::withdraw(double amount) {
	double doubleBalance = stod(this->getBalance());
	if (amount > doubleBalance || amount <= 0) {
		cout << "\n Withdrawa failed.";
		return;
	}
	setBalance(to_string(doubleBalance - amount));
	updateThisInDatabase();

	/*	if (auditFile.is_open()) {
			auditFile << "\n- withrawed "<<amount<< " from "<< getUserName();
		}
		else {
			cout << "\n Audit file is not available in withdraw function." << endl;
		}*/
	cout << endl << amount << " is withdrew from your account"
		"\nyour balance now: " << getBalance();
}

//to deposit money to the relevant account.
void Account::deposit(double amount) {
	if (amount <= 0) {
		cout << "\n deposit failed.";
		return;
	}
	else if (amount > 50000) {
		cout << "\n deposit failed, you have to visit the bank do deposit that much of money.";
		return;
	}
	setBalance(to_string(stod(getBalance()) + amount));
	updateThisInDatabase();

	/*	if (auditFile.is_open()) {
			auditFile << "\n- deposited " << amount << " to " << getUserName() <<" 's Account.";
		}
		else {
			cout << "\n Audit file is not available in withdraw function." << endl;
		}*/
	cout << endl << amount << " was deposited to your account"
		"\nyour balance now: " << getBalance();

}

//can update account info (i.e. email, phoneâ¦)
void Account::updateAccountInfo() {
	int operationNumber = 0;
	while (operationNumber != 5) {
		DisplayAccountInfo();
		cout << " UPDATE ACCOUNT'S INFO PANEL: "
			<< "\n please choose what operation you want to apply by number: "
			<< "\n1. Update User Name."
			<< "\n2. Update Email. "
			<< "\n3. Update Password."
			<< "\n4. Update Phone Number."
			<< "\n5. Close this Panel. "
			;
		cout << "\n operation: ";
		cin >> operationNumber;
		switch (operationNumber)
		{
		case 1: {
			string newUserName = "";
			cout << "\n please enter the new user name : ";
			cin.ignore();
			getline(cin, newUserName);
			setUserName(newUserName);
			updateThisInDatabase();
			string newValue = getUserName();
			if (newValue != newUserName) cout << "\nUpdating User Name failed";
			else cout << "\n User Name is Updated.";
		}
			  break;
		case 2: {
			string newEmail = "";
			cout << "\n please enter the new email: ";
			cin.ignore();
			getline(cin, newEmail);
			setEmail(newEmail);
			updateThisInDatabase();
			string newValue = getEmail();
			if (newValue != newEmail) cout << "\nUpdating Email failed";
			else cout << "\n Email is Updated";
		}
			  break;
		case 3: {
			string newPassword = "";
			cout << "\n please enter the new passwrod : ";
			cin.ignore();
			getline(cin, newPassword);
			setPassword(newPassword);
			updateThisInDatabase();
			string newValue = getPassword();
			if (newValue != newPassword) cout << "\nUpdating Password failed";
			else
				cout << "\n Password is Updated.";
		}
			  break;
		case 4: {
			string newPhoneNumber = "";
			cout << "\n please enter the new phone number : ";
			cin.ignore();
			getline(cin, newPhoneNumber);
			setPhoneNumber(newPhoneNumber);
			updateThisInDatabase();
			string newValue = getPhoneNumber();
			if (newValue != newPhoneNumber) cout << "\nUpdating Phone Number failed";
			else cout << "\n Phone Number is Updated.";
		}
			  break;
		case 5: {
			cout << "\n---------";
			/*if (auditFile.is_open()) {
				auditFile << "\n- updatting" << getUserName() << " Informations .";
			}
			else {
				cout << "\n Audit file is not available in updateAccountInfo function." << endl;
			}*/
		}
			  break;
		default:
			cout << "\nBad Input, stay with written range";
			break;
		}
	}
}