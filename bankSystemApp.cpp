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
	Account(const string& newUserName, const string& newEmail, const string& newPassword, const string& newPhoneNumber, int newAge, double newBalance) {
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
	string getUserName()const {
		return userName;
	}
	string getEmail()const {
		return email;
	}
	string getPassword()const {
		return password;
	}
	string getPhoneNumber()const {
		return phoneNumber;
	}
	int getAge()const {
		return age;
	}
	double getBalance()const {
		return balance;
	}
	bool getIsActive()const {
		return isActive;
	}
	void DisplayAccountInfo()const {
		cout << endl << userName << " Account info: \n"
			<< "Balance= [ " << balance << " ]\n"
			<< "Email : " << email << endl
			<< "Password : " << password << endl
			<< userName << " age is : " << age << endl
			<< "Status: " << (isActive) ? "ACTIVE" : "NOT Active";
	}
};
int main() {
	cout << "test committing";
	return 0;
}