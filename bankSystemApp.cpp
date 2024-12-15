#include <iostream>
#include <string>
#include <regex>
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
		userName = "";
		email = "";
		password="";
		phoneNumber="";
		age=0;
		balance = 0.00;
		isActive = true;
	}
	Account(double newBalance) {
		userName = "";
		email = "";
		password = "";
		phoneNumber = "";
		age = 0;
		setBalance(newBalance);
		isActive = true;
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

	//using setters for input validaiton

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
		if (Password.length() < 8) {
			cout << "\n Invalid Password.";
			return;
		}
		password = Password;
	}
	void setPhoneNumber(const string& PhoneNumber) {
		const regex phoneNumberRegex = regex("\\(?(\\d{3})\\)?[- ]?(\\d{3})[- ]?(\\d{4})");
		if (regex_match(PhoneNumber, phoneNumberRegex)) {
			phoneNumber = PhoneNumber;
		}
		cout << "\n INvalid phone number format";	
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


	void DisplayAccountInfo()const { //read account info
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
		case 5: cout << "\n---------"; break;

		default:
			cout << "\nBad Input, stay with written range";
			break;
		}
		}
	}


};	
class Customer : public Account{

};
int main() {

	Account a;
	a.setUserName("mot");
	a.setEmail("est@e@sxample.com");
	a.DisplayAccountInfo();

	return 0;
}