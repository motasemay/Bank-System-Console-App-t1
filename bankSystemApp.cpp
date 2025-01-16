#include <iostream>
#include <string>
#include <regex>
#include<fstream>
#include <sstream>

#include<vector>

using namespace std;

/*	if (auditfile.is_open()) {

void clearauditfile() {
	ofstream auditfile("audit.txt", ios::out);
		auditfile.close();
	}
	else {
		cout << "\n\n faild to open audit file for clearing it";
	}
}*/

	//fstream auditFile;

/*

void deleteFromDatabase() const {
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
	databaseLines.erase(std::remove_if(databaseLines.begin(), databaseLines.end(),
		[&](const string& line) {
			stringstream ss(line);
			string idStr;
			getline(ss, idStr, ',');

				return stoi(idStr) == this->id;
			


		}), databaseLines.end());




	ofstream outFile("usersDatabase.txt", ios::out | ios::trunc);
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
*/
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
	double balance;
	bool isActive;

public:
	Account() {
		id = idGenerator();
		role = "customer";
		userName = "";
		email = "";
		password="";
		phoneNumber="";
		age="";
		balance = 0.00;
		isActive = true;

		//saveToDatabase();
	//	auditFile.open("audit.txt", ios::app);
	//	if (!auditFile)
	//		cout << "\n unable to open audit file";
	//	else
	//		auditFile << "\n-Auditting " << getUserName() << " Account is statered.";
	}


	Account(double newBalance) {
		
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
	Account(const string& newUserName, const string& newEmail, const string& newPassword, const string& newPhoneNumber, const string& newAge, double newBalance=0.00,const string& newRole="customer") {
		
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
	~Account() {
		
	/*		DisplayAuditFile();
		if (auditFile.is_open()) {
			auditFile << "\n -Audit file is closed for " << getUserName() << " Account.";
			auditFile.close();
		}*/
		//clearAuditFile();
	}






	
	// funciton for database using text files






	//create the user Record
	void saveToDatabase()const {
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
	void loadFromDatabase(int accountId) {
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
			

			string Role,UserName,Email,Password,PhoneNumber;
			string Age;
			bool IsActive;
			double Balance;
			

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
				Balance = stod(column);
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
	int idGenerator() { // problem: increase the number by 4 each time!!!
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
		ofstream wFile("idFile.txt",ios::out);
		if (!wFile) {
			cout << "\nid File, Error: cannot write to this file";
			return -1; 
		}
		wFile << currentId;
		wFile.close();

		return currentId;
	}

	// after changing the data members of the current object (RAM), this funciton will apply these changes of it in the Database 
	void updateThisInDatabase() const {

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
			databaseLines[i] = to_string(this->id) + "," + this->role + "," + this->userName + "," + getEmail() + "," + getPassword() + "," + getPhoneNumber() + "," +getAge() + "," + to_string(getBalance()) + "," + (getIsActive() ? "Active" : "Inactive");
			isFound = true;
				break;
			}
		}
		if (!isFound) {
			cerr << "\nAccount not found in the database for update" << endl;
			return;
		}

		// return the updataed data to the userDatabase file ( edit the file)
		ofstream outFile("usersDatabase.txt",ios::trunc); // Truncate to overwrite
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



	bool doesAccountExist(const string& checkName)const {
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


	//using setters for input validaiton
	bool userNameValidation(const string& UserName) {
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
	bool emailValidation(const string& Email) {
		const regex emailRegex = regex(R"(^[a-zA-Z0-9.!#$%&'*+\/=?^_`{|}~-]+@[a-zA-Z0-9-]+(?:\.[a-zA-Z0-9-]+)*$)");
		if (regex_match(Email, emailRegex)) {
			return true;
		}
		cout << "\n Invalid Email value";
		return false;
	}
	bool passwordValidation(const string& testPassword) {
		if (testPassword.length() < 8) {
			cout << "\n Invalid Password.";
			return 0;
		}
		return 1;
	}
	bool phoneNumberValidation(const string& phoneNumber) {
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

	void setRole(const string& Role) {
		role = Role;
	}


	void setUserName(const string& UserName) {

		if (userNameValidation(UserName)) {

				userName = UserName;
		}
		else {
			cout << "\n cannot SET this as UserName";
			return;
		}

	}
	void setEmail(const string& Email) {
		if (emailValidation(Email)) {
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
		}
	
	}
	bool ageValidation(const string& Age) {
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
	void setAge(const string& Age) {
		
		if (ageValidation(Age)) {
			age = Age;
		}
		else
		{
			cout << "\n Invalid Age";
			return;
		}
	}
	bool setBalance(double Balance) {
		if (Balance >= 0 && Balance < 100000) {
		balance = Balance;
		return true;
		}
		else {
			cout << "\n Invlaid balance value";
			return false;
		}
	}
	void setIsActive(bool IsActive) {
		isActive = IsActive;
	}



	int getId()const { return id; }
	string getRole()const { return role; }
	string getUserName()const {	return userName;}
	string getEmail()const {return email;}
	string getPassword()const {return password;}
	string getPhoneNumber()const {return phoneNumber;}
	string getAge()const {return age;}
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


		updateThisInDatabase();


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

			updateThisInDatabase();

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

			updateThisInDatabase();

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

			updateThisInDatabase();

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

			updateThisInDatabase();

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

int Account::idCounter = 0;  // start counting id 's


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


/*

	void deleteAccount(const string& accountPhoneNumber) {
		// Find account by phone number and delete from the database
		ifstream file("usersDatabase.txt");

		if (!file) {
			 cout << "\n ERROR : users database, Cannot open file to delete account..";
			 return;
		}


		vector<string> remainingLines;
		string line;
		bool accountFound = false;


		while (getline(file, line)) {
			stringstream currentLine(line);
			string column;

			// Extract phone number for comparison
			for (int i = 0; i < 5; ++i) { // Skip to phone number column
				getline(currentLine, column, ',');
			}
			if (column == accountPhoneNumber) {
				accountFound = true;
				cout << "\n Account deleted successfully..";
				Account tempAccount;
				stringstream idStream(line);
				getline(idStream, column, ',');
				int deletingId = stoi(column);
				tempAccount.loadFromDatabase(deletingId);
				tempAccount.deleteFromDatabase();

			}
			else {
				remainingLines.push_back(line);
			}
		}
		file.close();


		if (!accountFound) {
			cout << "\n Delete :there is no Account with such a phone number";
			return;
		}
		ofstream updatedFile("usersDatabase.txt", ios::trunc);
		if (updatedFile.is_open()) {
			for (const string& updatedLine : remainingLines) {
				updatedFile << updatedLine << endl;

			}
			updatedFile.close();
		}



	}




	void updateAccount(const string& accountPhoneNumber) {

		 ifstream file("usersDatabase.txt");
		if (!file) {
			cout << "\n ERROR: users database, Cannot open file to update account..";
			return;
		}


		vector<string> updatedLines;
		string line;
		bool accountFound = false;

		while (getline(file, line)) {
			stringstream currentLine(line);
			string column;


			for (int i = 0; i < 5; ++i) {
				getline(currentLine, column, ',');
			}


			if (column == accountPhoneNumber) {

				stringstream idStream(line);
				getline(idStream, column, ',');
				int currentId = stoi(column);
				Account targetAccount;

				targetAccount.loadFromDatabase(currentId); // Load the account data
				targetAccount.updateAccountInfo();   // Allow the user to update fields

				targetAccount.updateDatabase();          // Update the database


				accountFound = true;
			}
			else {
				updatedLines.push_back(line);
			}

		}

		file.close();

		if (!accountFound) {
			cout << "\n Update :there is no Account with such a phone number";
			return;
		}
		ofstream updatedFile("usersDatabase.txt", ios::trunc);
		if (updatedFile.is_open()) {
			for (const string& updatedLine : updatedLines) {
				updatedFile << updatedLine << endl;

			}
			updatedFile.close();
		}

	}



*/
class Admin :public Customer {

private:
	vector<Account> accounts;

public:
	Admin() {
		
	}


	//The admin will be able to read, create, updateand delete user's accounts.

	void createNewAccount() {

		Account newAccount;
		string newRole;
		string newUserName;
		string newEmail;
		string newPassword;
		string ConfirmPassword;
		string newPhoneNumber;
		string newAge;
		double newBalance;
		cout << "\n Creating new Account: \n";
		/*
		cin.ignore();
		while (true) {
		cout	<< "\n Enter Account's user name: ";
		getline(cin, newUserName);

		if (!userNameValidation(newUserName))
		{
			cout << ", Try Again:";
			continue;
		}
		newAccount.setUserName(newUserName);
		break;
		}
		cout << "\n new Account's User Name: " << newAccount.getUserName()<<endl;

		while (true) {
		cout << "\n Enter Account's Email: ";
		getline(cin, newEmail);
		if (!emailValidation(newEmail)) {
			cout << ", Try Again";
			continue;
		}
		newAccount.setEmail(newEmail);
		break;
		}
		cout << "\n new Account's Email: " << newAccount.getEmail()<<endl;

		while (true) {
		cout << "\n Enter Account's Role (customer, admin) : ";
		cin >> newRole;
		if (!(newRole == "admin" || newRole == "customer"))
		{
			cout << "\n invalue Role value it must be (customer) or (admin), try again..";
			continue;
		}
		newAccount.setRole(newRole);
		break;
		}
		cout << "\n new Account's Role: " << newAccount.getRole() << endl;


		cin.ignore();
		while (true)
		{
			cout << "\n Enter Accounts' Password: ";
			getline(cin, newPassword);

			if (!passwordValidation(newPassword))
				continue;

			cout << "\n RE-Enter the password: ";
			getline(cin, ConfirmPassword);
			if (newPassword == ConfirmPassword) {
				newAccount.setPassword(newPassword);
				cout << "\n new Account's Password is: " << newAccount.getPassword()<<endl;
				break;
			}
			else {
				cout << "\n the passwords you entered isn't match, try again..";
			}
		}
		cin.ignore();
		while (true)
		{
		cout << "\n Enter the Accounts Phone Number: ";
		
		getline(cin, newPhoneNumber);
		if (!phoneNumberValidation(newPhoneNumber)) {
			cout << ", Try Again:";
			continue;
		}
		else
		{
			newAccount.setPhoneNumber(newPhoneNumber);
			cout << "\n new Account's Phone Number: " << newAccount.getPhoneNumber()<<endl;
			break;

		}
	
		}
		*/

		while (true) {

		cout << "\n Enter the User's Age: ";
		cin >> newAge;
		if (!ageValidation(newAge)) {
			cout << ", Try Again: ";
			continue;
		}
		newAccount.setAge(newAge);
		break;
		}
		cout << "\n new Account's age: " << newAccount.getAge()<<endl;


		string test = "";
		while (test != "Y" && test != "y") {
			cout << "\n Enter the Balance you want it to be in the Account's: ";
			cin >> newBalance;

			cout << "\nCRITICAL OPERATION: \n	are you sure you want " << newAccount.getUserName() << " to have " << newBalance << " in his account ? [Y] yes, [N] no, (other inputs will considered no) : ";
			cin.ignore();
			cin >> test;

			if (test == "Y" || test == "y") {
				newAccount.setBalance(newBalance);
				cout << "\n new Account's BALANCE: " << newAccount.getBalance();

				if (!newAccount.setBalance(newBalance)) {

					cout << "\nerror in setting the new balance.......";
					return;
				}
			}
			else
			{
				cout << "\n\n\n\n=====================";
			}

			
		}

		newAccount.setIsActive(true);

		accounts.push_back(newAccount);

		newAccount.saveToDatabase();

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
				<< "\n1.Create A New Account."
				<< "\n2.Delete An Account."
				<< "\n3.Update An Account."
				<< "\n4.Withdraw from An Account."
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
	Admin m;
	m.adminMenu();
	Customer customer;
	customer.loadFromDatabase(186); // Assuming account ID 19 exists

	cout << "\nCustomer balance before deposit: " << customer.getBalance() << endl;
	customer.deposit(100);
	cout << "\nCustomer balance after deposit: " << customer.getBalance() << endl;
	
	// Re-load from the database to verify the change
	Customer customer2; // A new object to test loading from the file
	customer2.loadFromDatabase(186);
	cout << "\nCustomer balance after reloading from database: " << customer2.getBalance() << endl; // Should show updated balance

	return 0;
}