#include "Account.h"
#include <iostream>
#include <string>
#include <regex>
#include<fstream>
#include <sstream>
#include<vector>
using namespace std;


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
	file << to_string(getId()) << "," << getRole() << "," << getUserName() << "," << getEmail() << "," << getPassword() << "," << getPhoneNumber() << "," << getAge() << "," << getBalance() << "," << (getIsActive() ? "Active" : "Inactive") << "\n";
	file.close();
	cout << "\n Users Database: Account saved successfully..";
}

//load the user data depend on the id in the userDatabase ( clone it to the current account's data members )
void Account:: loadFromDatabase(const string& accountId) {
	ifstream file("usersDatabase.txt");
	if (!file) {
		cout << "\n ERROR : users database, Cannot open file to load the user data..";
		return;
	}
	string line;
	while (getline(file, line)) {
		stringstream recordLine(line);
		string column;
		string currentId;
		getline(recordLine, column, ',');
		currentId = column;
		string Role, UserName, Email, Password, PhoneNumber;
		string Age;
		bool IsActive;
		string Balance;

		if (currentId == accountId) { //ASK : is it right to use private memebers directly here?
			id = stoi(accountId);
			getline(recordLine, Role, ',');
			//setRole(Role);
			role = Role;
			getline(recordLine, UserName, ',');
			//setUserName(UserName);
			userName = UserName;
			getline(recordLine, Email, ',');
			//setEmail(Email);
			email = Email;
			getline(recordLine, Password, ',');
			//setPassword(Password);
			password = Password;
			getline(recordLine, PhoneNumber, ',');
			//setPhoneNumber(PhoneNumber);
			phoneNumber = PhoneNumber;
			getline(recordLine, Age, ',');
			//setAge(Age);
			age = Age;
			getline(recordLine, Balance, ',');
			//setBalance(Balance);
			balance = Balance;
			getline(recordLine, column, ',');
			isActive = (column == "Active"); 
			//setIsActive(IsActive);
			file.close();
			return;
		}
	}
	file.close();
	cout << "\n Users Database: Account not found..";
}

int Account:: idGenerator() { // ASK : increase the number by 4 each time!!!
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
		if (column.empty() || all_of(column.begin(), column.end(), ::isspace)) {
			cout << "\n an empty line skiped";
			continue; // skip empty lines in text file
		}
		currentId = stoi(column);
		if (currentId == this->getId()) {
			databaseLines[i] = to_string(this->getId()) + "," +
				this->getRole() + "," +
				this->getUserName() + "," +
				this->getEmail() + "," +
				this->getPassword() + "," +
				this->getPhoneNumber() + "," +
				this->getAge() + "," +
				this->getBalance() + "," +
				(this->getIsActive() ? "Active" : "Inactive");
			isFound = true;
			break;
		}
	}
	if (!isFound) {
		cout << "\nAccount not found in the database to update it!" << endl;
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

void Account::deleteFromDatabase() const {
	// Similar to updateDatabase, but remove the line instead of modifying it
	vector<string> databaseLines;
	ifstream inFile("usersDatabase.txt");

	if (inFile) {
		string line;
		while (getline(inFile, line)) {
			databaseLines.push_back(line);
		}
		inFile.close();
	}

	// Remove the line corresponding to the account ID
	databaseLines.erase(remove_if(databaseLines.begin(), databaseLines.end(),
		[&](const string& line) {
			stringstream ss(line);
			string idStr;
			getline(ss, idStr, ',');

			return stoi(idStr) == this->id;



		}), databaseLines.end());

	ofstream outFile("usersDatabase.txt", ios::trunc);
	if (outFile) {
		for (const string& line : databaseLines) {
			outFile << line << endl;
		}
		outFile.close();
		cout << "\n Users Database: Account deleted successfully..";
	}
	else {
		cout << "\n ERROR : users database, Cannot open file to delete account..";
	}
}


bool Account::doesAccountExist(const string& checkEmail)const {
	ifstream file("usersDatabase.txt");
	if (!file.is_open()) {
		cout << "\n Users Database: Error: cannot open file to check if the user Exists";
		return false;   
	}
	string line;
	while (getline(file, line)) {
		stringstream currentLine(line);
		//this is the record structure: 
		// id,role,name,email,password,phoneNumber,age,balance,isActive
		//8,admin,motasem,motasem@gmail.com,motasem11,0569676250,26,5152,Active
		string columnn;
		getline(currentLine, columnn, ','); //skip id
		getline(currentLine, columnn, ',');  //skip role
		getline(currentLine, columnn, ','); //skip userName
		getline(currentLine, columnn, ','); //reach the email
		if (checkEmail == columnn)
			return true;
	}
	return false;  //finsh without find
}
//END OF functions for the database
	
//validation
template <typename T>
T Account::getValidInput(const string& text) {
	while (true) {
		cout << text;

		string inputLine;
		getline(cin, inputLine); 

		stringstream ss(inputLine);
		T typeValue;
		char extraChar;


		if (ss >> typeValue && !(ss >> extraChar)) { 
			return typeValue;
		}
		else {
			cout << "\nInvalid input, Please enter a valid value:";
		}
	}
}
template int Account::getValidInput<int>(const string& text);
template double Account::getValidInput<double>(const string& text); // fixing a LINKER error, sometimes need to explictly instantionate the datatype will used with template

bool Account:: userNameValidation(const string& UserName) {
	/*	if (UserName == "" || UserName == " " || UserName.length() < 3 || UserName.length() > 50) {
			cout << "\n Invalid User Name. ";
			return false;
		}*/
	if (UserName.length() == 0) {
		cout << "\n Invaild User Name, Cannot be EMPTY!";
		return false;
	}
	regex userNameRegex("^[a-zA-Z_-]{3,50}$");
	if (!regex_match(UserName, userNameRegex)) {
		cout << "\n Regex:  Invalid User Name. ";
		return false;
	}
	return true;
}

bool Account::emailValidation(const string& Email) {
	if (Email.length() == 0) {
		cout << "\n Invalid Email, cannot be EMPTY!";
		return false;
	}
	const regex emailRegex = regex(R"(^[a-zA-Z0-9.!#$%&'*+\/=?^_`{|}~-]+@[a-zA-Z0-9-]+(?:\.[a-zA-Z0-9-]+)*$)");
	if (!regex_match(Email, emailRegex)) {
		cout << "\n Invalid Email format, must be in this format(e.g., john.doe@example.com)";
		return false;
	}
	if (doesAccountExist(Email)) {
		cout << "\n this Email already exists";
		return false;
	}
	return true;
}

bool Account::passwordValidation(const string& testPassword) {
	if (testPassword.length() == 0) {
		cout << "\n Invalid Password, cannot be EMPTY!";
		return false;
	}
	if (testPassword.length() < 8) {
		cout << "\n Invalid Password, cannot be Less than 8 digits";
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
	if (phoneNumber.length() == 0) {
		cout << "\nInvalid phone number: cannot be empty";
		return false;
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
	if (Age.length() == 0) {
		cout << "\n Invalid Age, cannot be EMPTY!";
		return false;
	}
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
	if (Balance.length() == 0) {
		cout << "\n Invalid Balance Value, Cannot be EMPTY!";
		return false;
	}

	for (int i = 0; i < Balance.length(); i++) {
		if (!(isdigit(Balance[i])||Balance[i] == '.')) {
			cout << "\nInvalid Balance: must contain only digits";
			return false;
		}
	}
	double doubleBalance = stod(Balance);
	
	if (!( doubleBalance >= 0)) {
		cout << "\n Invalid Balance, balance must not be negative value";
		return false;
	}
	return true;

}

bool Account::roleValidation(const string& Role) {
	if (Role.length() == 0) {
		cout << "\nInvalid Role, Cannot Be EMPTY!";
		return false;
	}
	if (!(Role == "admin" || Role == "customer"))
	{
		cout << "\n invalue Role value it must be (customer) or (admin) ";
		return false;
	}
	return true;
}

//SETTRS
void Account::setRole(const string& Role) {
	if (roleValidation(Role))
		role = Role;
	else
		cout << "\n Invalid Role Format";
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
	else
		cout << "\n Invalid Password format";
}

void Account::setPhoneNumber(const string& PhoneNumber) {
	if (phoneNumberValidation(PhoneNumber))
	{
		phoneNumber = PhoneNumber;
	}
	else
		cout << "\n Invalid Phone Number format";
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
	if (balanceValidation(Balance)) {
		balance = Balance;
	}
	else {
		cout << "\n Balance Setter : Error during setting the new balance";
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

/*
void DisplayAuditFile()const {
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
	}
	*/
void Account::displayAccountInfo() { 
/*	
if (auditFile.is_open()) {
		auditFile << "\n- Displayed User Information for " << getUserName();
	}
	else {
		cout << "\n Audit file is not available in DisplayAccountInfo function.";
	}
	*/
	cout << endl<<endl << getUserName() << " Account info: \n"
		<< "ID: #" << getId() << " \n"
		<< "Balance= [ " << getBalance() << " ]\n"
		<< "Email : " << getEmail() << endl
		<< "Password : " << getPassword() << endl
		<< "PhoneNumber is :" << getPhoneNumber() << endl
		<< "age is : " << getAge() << endl
		<< "Status: " << (getIsActive() ? "Active" : "NOT Active");
}

void Account::withdraw(double amount) {
	double doubleBalance = stod(this->getBalance());
	while (true) {
	if (amount > doubleBalance || amount <= 0) {
		cout << "\n Withdrawa failed.";
		return;
	}
	setBalance(to_string(doubleBalance - amount));
	/*	if (auditFile.is_open()) {
			auditFile << "\n- withrawed "<<amount<< " from "<< getUserName();
		}
		else {
			cout << "\n Audit file is not available in withdraw function." << endl;
		}*/
	cout << endl << amount << " is withdrew from account"
		"\nAccount balance now: " << getBalance();
	updateThisInDatabase(); //FIXTHIS: abort() is called 
	break;
	}
}

void Account::deposit(double amount) {
	if (amount <= 0) {
		cout << "\n deposit failed.";
		return;
	}
	else if (amount > 100000) {
		cout << "\n deposit failed, you have to visit the bank to deposit 100,000 or more.";
		return;
	}
	double oldBalance = stod(getBalance());
	double newBalance = oldBalance + amount;
	setBalance(to_string(newBalance));
	/*	if (auditFile.is_open()) {
			auditFile << "\n- deposited " << amount << " to " << getUserName() <<" 's Account.";
		}
		else {
			cout << "\n Audit file is not available in withdraw function." << endl;
		}*/
	cout << endl << amount << " was deposited to the account"
		"\nAccount balance now: " << getBalance();
	cout << "\n deposit funciton getId(): :" << getId();
	updateThisInDatabase();

}

void Account::updateAccountInfo() {
	cout << "\033[2J\033[1;1H";
	int operationNumber = 0;
	while (operationNumber != 5) {
		displayAccountInfo();
		cout << "\n -------------------------"
			"\n UPDATE ACCOUNT'S INFO PANEL: "
			<< "\n1. Update User Name."
			<< "\n2. Update Email. "
			<< "\n3. Update Password."
			<< "\n4. Update Phone Number."
			<< "\n5. Close this Panel. "
			;
		operationNumber = getValidInput<int>("\nupdate operation: ");
		switch (operationNumber)
		{
		case 1: {
			string newUserName = "";
			while (true) {
			cout << "\n please enter the new user name : ";
			getline(cin, newUserName);
			if (!userNameValidation(newUserName)){
				cout << ", Try Again:";
				continue;
			}
			this->setUserName(newUserName);
			string newValue = getUserName();
			if (newValue != newUserName) cout << "\nUpdating User Name failed";
			else cout << "\n User Name is Updated.\n";
			updateThisInDatabase(); 
			break;
			}
		}break;
		case 2: {
			string newEmail = "";
			while (true) {
				cout << "\n please enter the new email: ";
				getline(cin, newEmail);
				if (!emailValidation(newEmail)) {
					cout << ", Try Again";
					continue;
				}
				this->setEmail(newEmail);
				string newValue = getEmail();
				if (newValue != newEmail) cout << "\nUpdating Email failed";
				else cout << "\n Email is Updated\n";
				updateThisInDatabase();
				break;
			}
		}break;
		case 3: {
			string newPassword = "";
			string confirmPassword;
			while (true) {

				cout << "\n please enter the new passwrod : ";
				getline(cin, newPassword);
				if (!passwordValidation(newPassword)) {
					cout << ", Try Again:";
					continue;
				}
				cout << " Re Enter the password: ";
				getline(cin, confirmPassword);
				if (newPassword == confirmPassword) {
					this->setPassword(newPassword);
					cout << "\n new Account's Password is: " << this->getPassword()<<endl;
					break;
				}
				else {
					cout << "\n the passwords you entered isn't match, try again..";
					continue;
				}
				updateThisInDatabase();
			} 
		}break;
		case 4: {
			string newPhoneNumber = "";
			while (true) {
				cout << "\n please enter the new phone number : ";
				getline(cin, newPhoneNumber);
				if (!phoneNumberValidation(newPhoneNumber)) {
					cout << ", Try Again:";
					continue;
				}
				this->setPhoneNumber(newPhoneNumber);
				string newValue = getPhoneNumber();
				if (newValue != newPhoneNumber) cout << "\nUpdating Phone Number failed";
				else cout << "\n Phone Number is Updated.\n";
				updateThisInDatabase();
				break;
			}
		}break;
		case 5: {
			cout << "\033[2J\033[1;1H";
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