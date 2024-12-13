#include <iostream>
#include <string>
using namespace std;
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
		setUserName("");
		setEmail("");
		setPassword("");
		setPhoneNumber("");
		setAge(0);
		setBalance(0.00);
		setIsActive(true);
	}
	Account(double newBalance) {
		setUserName("");
		setEmail("");
		setPassword("");
		setPhoneNumber("");
		setAge(0);
		setBalance(newBalance);
		setIsActive(true);
	}
	Account(const string& newUserName, const string& newEmail, const string& newPassword, const string& newPhoneNumber, int newAge, double newBalance=0.00) {
		setUserName(newUserName);
		setEmail(newEmail);
		setPassword(newPassword);
		setPhoneNumber(newPhoneNumber);
		setAge(newAge);
		setBalance(newBalance);
		setIsActive(true);
	}
	void setUserName(const string& UserName) {
		userName = UserName;
	}
	void setEmail(const string& Email) {
		email = Email;
	}
	void setPassword(const string& Password) {
		password = Password;
	}
	void setPhoneNumber(const string& PhoneNumber) {
		phoneNumber = PhoneNumber;
	}
	void setAge(int Age) {
		age = Age;
	}
	void setBalance(double Balance) {
		balance = Balance;
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


	void DisplayAccountInfo()const { //read account info
		cout << endl << userName << " Account info: \n"
			<< "Balance= [ " << balance << " ]\n"
			<< "Email : " << email << endl
			<< "Password : " << password << endl
			<< userName << " age is : " << age << endl
			<< "Status: " << (getIsActive() ? "ACTIVE" : "NOT Active");
	}
	//able to withdraw money from the relevant account.
	void withdraw(double amount) {
		if (amount > this->balance|| amount<=0) {
			cout << "\n Withdrawa failed.";
			return;
		}
		setBalance(getBalance() - amount);

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
		cout << endl << amount << " was deposited to your account"
			"\nyour balance now: " << getBalance();

	}

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
		case 5: cout << "\n---------"; break;

		default:
			cout << "\nBad Input, stay with writen range";
			break;
		}
		}
	}

};	
int main() {

	Account a;
	a.updateAccountInfo();
	a.DisplayAccountInfo();

	return 0;
}