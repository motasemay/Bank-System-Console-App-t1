#include <iostream>
#include <string>
#include "Account.h"
#include "Customer.h"
#include "Admin.h"
#include "Bank.h"
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
int main() {

	Bank B1;
	B1.authenticateUser();

	return 0;
}