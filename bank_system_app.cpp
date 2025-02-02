#include <iostream>
#include <string>
#include "Account.h"
#include "Customer.h"
#include "Admin.h"
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
}*/

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
class Bank {
public:
	bool authenticateUser() {
		cout<<"\n------ LOG IN------\n";
		string Email, Password;
		cout << "\n Enter your Email: ";
		getline(cin, Email);
		cout << "\n Enter your Passrwod:";
		getline(cin, Password);

		ifstream file("usersDatabase.txt");
		if (!file) {
			cout << "\n Error: usersDatabase, cannot find the file for authentication.";
			return false;
		}
		string Role = "none";
		string line;
		string storedId, storedRole, storedUserName, storedEmail, storedPassword, storedPhoneNumber, storedAge, storedBalance, storedIsActive;
		while (getline(file, line)) {
			stringstream recordLine(line);

			getline(recordLine, storedId, ',');
			getline(recordLine, storedRole, ',');
			getline(recordLine, storedUserName, ',');
			getline(recordLine, storedEmail, ',');
			getline(recordLine, storedPassword, ',');
			getline(recordLine, storedPhoneNumber, ',');
			getline(recordLine, storedAge, ','); 
			getline(recordLine, storedBalance, ',');
			getline(recordLine, storedIsActive, ',');

			if (Email == storedEmail&&Password==storedPassword) {
				Role = storedRole;
				file.close();
				break;
			}
		}
		if (Role == "none") {
			cout << "\n Invalid Email or Password.";
			file.close();
			return false;
		}

		if (Role == "customer"||Role=="Customer") {
			Customer loginCustomer;
			loginCustomer.loadFromDatabase(storedId);
			loginCustomer.customerMenu();
			return true;
		}
		else if (Role == "admin" || Role == "Admin") {
			Admin loginAdmin;
			loginAdmin.loadFromDatabase(storedId);
			loginAdmin.adminMenu();
			return true;
		}
		else {
			cout << "\n Invalid Authentication Token, you are not allowed to Enter The Bank System.";
			return false;
		}
	}
};
int main() {
	Bank B1;
	B1.authenticateUser();

	return 0;
}