#include <iostream>
#include <string>
#include <regex>
#include<fstream>
#include<vector>

using namespace std;

/*
void clearauditfile() {
	ofstream auditfile("audit.txt", ios::out);
	if (auditfile.is_open()) {
		auditfile.close();
	}
	else {
		cout << "\n\n faild to open audit file for clearing it";
	}
}*/

	//fstream auditFile;


class Account {
private:
	string userName;
	string email;
	string password;
	string phoneNumber;
	int age;
	double balance;
	bool isActive;

public:
	Account() {
		userName = "";
		email = "";
		password="";
		phoneNumber="";
		age=0;
		balance = 0.00;
		isActive = true;

	//	auditFile.open("audit.txt", ios::app);
	//	if (!auditFile)
	//		cout << "\n unable to open audit file";
	//	else
	//		auditFile << "\n-Auditting " << getUserName() << " Account is statered.";
	}
	Account(double newBalance) {
		userName = "";
		email = "";
		password = "";
		phoneNumber = "";
		age = 0;
		setBalance(newBalance);
		isActive = true;

		/*auditFile.open("audit.txt", ios::app);
		if (!auditFile)
			cout << "\n unable to open audit file";
		else
			auditFile << "--Auditting " << getUserName() << "'s Account is statered.";
			*/
	}
	Account(const string& newUserName, const string& newEmail, const string& newPassword, const string& newPhoneNumber, int newAge, double newBalance=0.00) {
		setUserName(newUserName);
		setEmail(newEmail);
		setPassword(newPassword);
		setPhoneNumber(newPhoneNumber);
		setAge(newAge);
		setBalance(newBalance);
		setIsActive(true);


	/*	auditFile.open("audit.txt", ios::app);
		if (!auditFile)
			cout << "\n unable to open audit file";
		else
			auditFile << "---Auditting " << getUserName() << "'s Account is statered.";*/
	}
	~Account() {
		
	/*		DisplayAuditFile();
		if (auditFile.is_open()) {
			auditFile << "\n -Audit file is closed for " << getUserName() << " Account.";
			auditFile.close();
		}*/
		//clearAuditFile();
	}
	//using setters for input validaiton
	bool passwordValidation(const string&testPassword) {
		if (testPassword.length() < 8) {
			cout << "\n Invalid Password.";
			return 0;
		}
		return 1;
	}
	bool phoneNumberValidation(const string& testPhoneNumber) {
		const regex phoneNumberRegex = regex("\(?(\\d{3})\\)?[- ]?(\\d{3})[- ]?(\\d{4})");
		if (regex_match(testPhoneNumber, phoneNumberRegex)) {
			return 1;
		}
		else {
			cout << "\n INvalid phone number format";
			return 0;

		}
	}
	void setUserName(const string& UserName) {
		if (UserName == "" || UserName == " "||UserName.length()<3 || UserName.length()>50) {
			cout << "\n Invalid User Name. ";
			return;
		}
		userName = UserName;
	}
	void setEmail(const string& Email) {
		const regex emailRegex = regex(R"(^[a-zA-Z0-9.!#$%&'*+\/=?^_`{|}~-]+@[a-zA-Z0-9-]+(?:\.[a-zA-Z0-9-]+)*$)");
		if (regex_match(Email, emailRegex)) {
			email = Email;
		}
		else {
			cout << "\n Invalid Email format";
		}
	}
	void setPassword(const string& Password) {
		if(passwordValidation(Password))
			password = Password;
	}
	void setPhoneNumber(const string& PhoneNumber) {
		if (phoneNumberValidation(PhoneNumber))
		{
			phoneNumber = PhoneNumber;
			cout << "\nsuck secen";
		}
	
	}
	void setAge(int Age) {
		if (Age > 0 && Age < 130) {
		age = Age;

		}
		else {
			cout << "\n Invalid age";
		}
	}
	void setBalance(double Balance) {
		if (Balance >= 0 && Balance < 1000000) {
		balance = Balance;

		}
		else {
			cout << "\n Invlaid balance value";
		}
	}
	void setIsActive(bool IsActive) {
		isActive = IsActive;
	}

	string getUserName()const {	return userName;}
	string getEmail()const {return email;}
	string getPassword()const {return password;}
	string getPhoneNumber()const {return phoneNumber;}
	int getAge()const {return age;}
	double getBalance()const {return balance;}
	bool getIsActive()const {return isActive;}

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
	void DisplayAccountInfo() { //read account info
	/*	if (auditFile.is_open()) { 
			auditFile << "\n- Displayed User Information for " << getUserName();
		}
		else {
			cout << "\n Audit file is not available in DisplayAccountInfo function.";
		}
		*/
		cout << endl << getUserName() << " Account info: \n"
			<< "Balance= [ " << getBalance() << " ]\n"
			<< "Email : " << getEmail() << endl
			<< "Password : " << getPassword() << endl
			<< "PhoneNumber is :" << getPhoneNumber() << endl
			<< userName << " age is : " << getAge() << endl
			<< "Status: " << (getIsActive() ? "ACTIVE" : "NOT Active");
	}
	//able to withdraw money from the relevant account.
	void withdraw(double amount) {
		if (amount > this->getBalance() || amount <= 0) {
			cout << "\n Withdrawa failed.";
			return;
		}
		setBalance(getBalance() - amount);

	/*	if (auditFile.is_open()) {
			auditFile << "\n- withrawed "<<amount<< " from "<< getUserName();
		}
		else {
			cout << "\n Audit file is not available in withdraw function." << endl;
		}*/
		cout <<endl<<amount<<" is withdrew from your account"
			"\nyour balance now: " << getBalance();
	}
	//to deposit money to the relevant account.
	void deposit(double amount) {
		if (amount <= 0) {
			cout << "\n deposit failed.";
			return;
		}
		else if (amount > 50000) {
			cout << "\n deposit failed, you have to visit the bank do deposit that much of money.";
			return;
		}

		setBalance(getBalance() + amount);
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
	void updateAccountInfo() {

		int operationNumber = 0;
		while (operationNumber != 5) {

		cout << "\n UPDATE ACCOUNT'S INFO PANEL: "
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
			string newValue= getUserName();
			if (newValue != newUserName) cout << "\nUpdating User Name failed";
			else cout << "\n User Name is Updated.";
		} break;
		case 2: {
			string newEmail = "";
			cout << "\n please enter the new email: ";
			cin.ignore();
			getline(cin, newEmail);
			setEmail(newEmail);
			string newValue = getEmail();
			if (newValue != newEmail) cout << "\nUpdating Email failed";
			else cout << "\n Email is Updated";
		}break;
		case 3: {
			string newPassword = "";
			cout << "\n please enter the new passwrod : ";
			cin.ignore();
			getline(cin, newPassword);
			setPassword(newPassword);
			string newValue = getPassword();
			if (newValue != newPassword) cout << "\nUpdating Password failed";
			else
				cout << "\n Password is Updated.";
		}break;
		case 4: {
			string newPhoneNumber = "";
			cout << "\n please enter the new phone number : ";
			cin.ignore();
			getline(cin, newPhoneNumber);
			setPhoneNumber(newPhoneNumber);
			string newValue = getPhoneNumber();
			if (newValue != newPhoneNumber) cout << "\nUpdating Phone Number failed";
			else cout << "\n Phone Number is Updated.";
		}break;
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


};
class Customer : public Account{
public:
		void customerMenu() {
		int choice = 0;
		while (choice != 6) {
			cout << "\nCUSTOMER MENU:"
				<< "\n1. Display Account's Info"
				<< "\n2. Deposit money"
				<< "\n3. Withdraw money"
				<< "\n4. Update Accounts' info"
				<< "\n5. View audit file"
				<< "\n6. stop"
				<< "\nChoose an option: ";

			cin >> choice;

			switch (choice) {
			case 1: {
				DisplayAccountInfo();
				break;
			}
			case 2: {
				double depositAmount;
				cout << "\nEnter amount to deposit: ";
				cin >> depositAmount;
				deposit(depositAmount);
				break;
			}
			case 3: {
				double withdrawAmount;
				cout << "\nEnter amount to withdraw: ";
				cin >> withdrawAmount;
				withdraw(withdrawAmount);
				break;
			}
			case 4: {
				updateAccountInfo();
				break;
			}
			case 5: {
				//DisplayAuditFile();
				break;
			}
			case 6: {
				cout << "\nExiting customer menu.\n";
				break;
			}
			default: {
				cout << "\nInvalid choice, select a valid option: ";
				break;
			}
			}
		}
	}
};


class Admin :public Customer {

private:
	vector<Account> accounts;

public:
	Admin() {
		
	}


	//The admin will be able to read, create, updateand delete user's accounts.

	void createNewAccount() {

		Account newAccount;

		string newUserName;
		string newEmail;
		string newPassword;
		string ConfirmPassword;
		string newPhoneNumber;
		int newAge;
		double newBalance;
		cout << "\n Creating new Account: "
			<< "\n Enter Account's user name: ";
		cin.ignore();
		getline(cin, newUserName);
		newAccount.setUserName(newUserName);

		cout << "\n Enter Account's Email: ";
		getline(cin, newEmail);
		newAccount.setEmail(newEmail);


		while (true)
		{
			cout << "\n Enter Accounts' Password: ";
			cin.ignore();
			getline(cin, newPassword);

			if (!passwordValidation(newPassword))
				continue;

			cout << "\n RE-Enter the password: ";
			cin.ignore();
			getline(cin, ConfirmPassword);
			if (newPassword == ConfirmPassword) {
				newAccount.setPassword(newPassword);
				break;
			}
			else {
				cout << "\n the passwords you entered isn't match, try again..";
			}
		}
		while (true)
		{

		cout << "\n Enter the Accounts Phone Number: ";
		cin.ignore();
		getline(cin, newPhoneNumber);

		if (!phoneNumberValidation(newPhoneNumber))
			continue;
		newAccount.setPhoneNumber(newPhoneNumber);
	
		}

		cout << "\n Enter the User's Age: ";
		cin >> newAge;
		newAccount.setAge(newAge);

		char test = '0';
		while (test != 'Y' && test != 'y') {
			cout << "\n Enter the Balance you want it to be in the Account's: ";
			cin >> newBalance;

			cout << "\nCRITICAL OPERATION: \n	are you sure you want " << getUserName() << " to have " << newBalance << " in his account ? [Y] yes, [N] no, other inputs will considered NO";
			cin >> test;

			if (test == 'Y' || test == 'y') {
				newAccount.setBalance(newBalance);
			}
		}

		newAccount.setIsActive(true);

		accounts.push_back(newAccount);
		cout << "\n new Account created successfully..";

	}

	void deleteAccount(const string& accountPhoneNumber) {
		for (int i = 0; i < accounts.size(); i++) {
			if (accounts[i].getPhoneNumber() == accountPhoneNumber) {
				string tempUserName = accounts[i].getUserName();
				accounts.erase(accounts.begin() + i);
				cout << "\n" << tempUserName << " Account's is deleted X ";
				return;
			}
		}
		cout << "\n Delete :there is no Account with such a phone number";
	}
	void updateAccount(const string& accountPhoneNumber) {
		for (int i = 0; i < accounts.size(); i++) {
			if (accounts[i].getPhoneNumber() == accountPhoneNumber) {
				accounts[i].updateAccountInfo();
				cout << "\n" << accounts[i].getUserName() << " Account's info is updated";
				return;
			}
		}
		cout << "\n Update :there is no Account with such a phone number";

	}

	//The admin will be able to withdraw money from the relevant account.

	void withdrawFromAccount(const string& accountPhoneNumber, double amount) {
		for (int i = 0; i < accounts.size(); i++) {
			if (accounts[i].getPhoneNumber() == accountPhoneNumber) {
				accounts[i].withdraw(amount);
				cout << "\n" << amount << " is withdrawed from " << accounts[i].getUserName() << "'s Account";
				return;
			}
		}
		cout << "\n Withdraw from Account :there is no Account with such a phone number";


	}

	//The admin will be able to deposit money to the relevant account.

	void depositToAccount(const string& accountPhoneNumber, double amount) {
		for (int i = 0; i < accounts.size(); i++) {
			if (accounts[i].getPhoneNumber() == accountPhoneNumber) {
				accounts[i].deposit(amount);
				cout << "\n" << amount << " is deposited to " << accounts[i].getUserName() << "'s Account";
				return;
			}
		}
		cout << "\n Deposit to Account :there is no Account with such a phone number";

	}

	//The admin can view a list of all active accounts.

	void displayActiveAccounts()const {
		int counter = 1;
		cout << "\n Active Accounts: [ ";
		for (int i = 0; i < accounts.size(); i++) {
			if (accounts[i].getIsActive() == false) continue;
			cout << endl << counter << "." << accounts[i].getUserName() << "  " << accounts[i].getPhoneNumber();
			counter++;

		}
	}
	void displayInactiveAccounts()const {
		int counter = 1;
		cout << "\n Inactive Accounts: [ ";
		for (int i = 0; i < accounts.size(); i++) {
			if (accounts[i].getIsActive() == true) continue;
			cout << endl << counter << "." << accounts[i].getUserName() << "  " << accounts[i].getPhoneNumber();
			counter++;

		}
	}



	//The admin can activate/ deactivate accounts.

	void deactivateAccount(const string& accountPhoneNumber) {
		for (int i = 0; i < accounts.size(); i++) {
			if (accounts[i].getPhoneNumber() == accountPhoneNumber) {
				if (accounts[i].getIsActive() == false) {
					cout << "\n" << accounts[i].getUserName() << " Account's is already Dactivated...";
					return;
				}
				accounts[i].setIsActive(false);
				cout << "\n" << accounts[i].getUserName() << " Account's is deactivated ";
				return;
			}
		}
		cout << "\n Deactivate Account :there is no Account with such a phone number";
	}
	void activateAccount(const string& accountPhoneNumber) {
		for (int i = 0; i < accounts.size(); i++) {
			if (accounts[i].getPhoneNumber() == accountPhoneNumber) {
				if (accounts[i].getIsActive() == true) {
					cout << "\n" << accounts[i].getUserName() << " Account's is already Active..";
					return;
				}
				accounts[i].setIsActive(true);
				cout << "\n" << accounts[i].getUserName() << " Account's is Aactivated ";
				return;
			}
		}
		cout << "\n Activate Account :there is no Account with such a phone number";
	}

	void adminMenu() {
		int choise = 0;
		while (choise != 10) {

			cout << "\n Admin Menu: "
				<< "\n 1.Create A New Account."
				<< "\n 2.Delete An Account."
				<< "\n 3.Update An Account."
				<< "]n 4.Withdraw from An Account."
				<< "\n5.Deposit To An Account."
				<< "\n6.Display Active Accounts."
				<< "\n7.Display InActive Accounts"
				<< "\n8.Deactivate An Account."
				<< "\n9.Activate An Account."
				<< "\n10. CLOSE This Menu"
				<<"\n choose the operation: ";
			cin >> choise;
			switch (choise) {
			case 1: {
				createNewAccount();
			}break;
			case 2: {
				cout << "\n Enter the phone number for the Account to DELETE: ";
				string searchPhoneNumber;


				cin.ignore();
				getline(cin, searchPhoneNumber);
				deleteAccount(searchPhoneNumber);

			}break;
			case 3: {
				cout << "\n Enter the phone number for the Account to UPDATE: ";
				string searchPhoneNumber;
				cin.ignore();
				getline(cin, searchPhoneNumber);
				updateAccount(searchPhoneNumber);

			}break;
			case 4: {
				cout << "\n Enter the phone number for the Account to WITHDRAW from: ";
				string searchPhoneNumber;
				int amount = 0;
				cin.ignore();
				getline(cin, searchPhoneNumber);
				cout << "\n how much you want to withdraw: ";
				cin >> amount;
				withdrawFromAccount(searchPhoneNumber, amount);

			}break;
			case 5: {
				cout << "\n Enter the phone number for the Account to DEPOSIT to it: ";
				string searchPhoneNumber;
				int amount = 0;
				cin.ignore();
				getline(cin, searchPhoneNumber);
				cout << "\n how much you want to deposit: ";
				cin >> amount;
				depositToAccount(searchPhoneNumber, amount);

			}break;
			case 6: {
				displayActiveAccounts();
			}break;
			case 7: {
				displayInactiveAccounts();
			}break;
			case 8: {
				cout << "\n Enter the phone number for the Account to DEACTIVATE it: ";
				string searchPhoneNumber;
				cin.ignore();
				getline(cin, searchPhoneNumber);
				//deactivateAccount(searchPhoneNumber);
			}break;
			case 9: {
				cout << "\n Enter the phone number for the Account to ACTIVATE it: ";
				string searchPhoneNumber;
				cin.ignore();
				getline(cin, searchPhoneNumber);
				activateAccount(searchPhoneNumber); }break;

			case 10: {
				cout << "stoped..\n----------------------------------";

			}break;


			default: {
				cout << "\nInvalid choice, select a valid option: ";
				break;
			}



			}
		}
	}};
	
int main() {
	


	
	Admin a;
	a.setUserName("adminmane");
	cout << a.getUserName() << endl;
	a.adminMenu();


	return 0;
}