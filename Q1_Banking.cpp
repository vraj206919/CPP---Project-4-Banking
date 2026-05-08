#include <iostream>

using namespace std;

class BankAccount {
protected:
	int accountNumber;
	string accountHolderName;

private:
	double balance;

public:
	BankAccount(int accNo, string name, double bal) {
		accountNumber = accNo;
		accountHolderName = name;
		balance = bal;
	}

	virtual ~BankAccount() {}

	int getAccountNumber() const {
		return accountNumber;
	}

	virtual void deposit(double amount) {
		if (amount > 0) {
			balance += amount;
			cout << "Deposit Successful!\n";
		} else {
			cout << "Invalid Deposit Amount!\n";
		}
	}

	virtual void withdraw(double amount) {
		if (amount > 0 && amount <= balance) {
			balance -= amount;
			cout << "Withdrawal Successful!\n";
		} else {
			cout << "Insufficient Balance!\n";
		}
	}

	double getBalance() const {
		return balance;
	}

protected:
	void setBalance(double bal) {
		balance = bal;
	}

public:
	virtual double calculateInterest() {
		return 0;
	}

	virtual void displayAccountInfo() {
		cout << "\n====================================\n";
		cout << "Account Number : " << accountNumber << endl;
		cout << "Account Holder : " << accountHolderName << endl;
		cout << "Current Balance: $" << balance << endl;
	}
};

class SavingsAccount : public BankAccount {
private:
	double interestRate;

public:
	SavingsAccount(int accNo, string name, double bal, double rate)
		: BankAccount(accNo, name, bal) {
		interestRate = rate;
	}

	double calculateInterest() override {
		return getBalance() * interestRate / 100;
	}

	void displayAccountInfo() override {
		BankAccount::displayAccountInfo();
		cout << "Account Type   : Savings Account\n";
		cout << "Interest Rate  : " << interestRate << "%\n";
		cout << "Interest Amount: $" << calculateInterest() << endl;
	}
};

class CheckingAccount : public BankAccount {
private:
	double overdraftLimit;

public:
	CheckingAccount(int accNo, string name, double bal, double limit)
		: BankAccount(accNo, name, bal) {
		overdraftLimit = limit;
	}

	bool checkOverdraft(double amount) {
		return amount <= (getBalance() + overdraftLimit);
	}

	void withdraw(double amount) override {
		if (checkOverdraft(amount)) {
			setBalance(getBalance() - amount);
			cout << "Withdrawal Successful!\n";
		} else {
			cout << "Overdraft Limit Exceeded!\n";
		}
	}

	void displayAccountInfo() override {
		BankAccount::displayAccountInfo();
		cout << "Account Type   : Checking Account\n";
		cout << "Overdraft Limit: $" << overdraftLimit << endl;
	}
};

class FixedDepositAccount : public BankAccount {
private:
	int term;
	double interestRate;

public:
	FixedDepositAccount(int accNo, string name,
	                    double bal, int t, double rate)
		: BankAccount(accNo, name, bal) {
		term = t;
		interestRate = rate;
	}

	double calculateInterest() override {
		return (getBalance() * interestRate * term) / (100 * 12);
	}

	void displayAccountInfo() override {
		BankAccount::displayAccountInfo();
		cout << "Account Type   : Fixed Deposit Account\n";
		cout << "Term           : " << term << " months\n";
		cout << "Interest Rate  : " << interestRate << "%\n";
		cout << "Interest Amount: $" << calculateInterest() << endl;
	}
};

int main() {

	const int MAX_ACCOUNTS = 100;

	BankAccount* accounts[MAX_ACCOUNTS];

	int totalAccounts = 0;

	int choice;

	do {
		cout << "\n=== BANKING SYSTEM ===\n";
		cout << "1. Create Savings Account\n";
		cout << "2. Create Checking Account\n";
		cout << "3. Create Fixed Deposit Account\n";
		cout << "4. Deposit Money\n";
		cout << "5. Withdraw Money\n";
		cout << "6. Display All Accounts\n";
		cout << "7. Exit\n";
		cout << "Enter Choice: ";
		cin >> choice;

		switch (choice) {

		case 1: {
			int accNo;
			string name;
			double balance, rate;

			cout << "Enter Account Number: ";
			cin >> accNo;

			cin.ignore();

			cout << "Enter Account Holder Name: ";
			getline(cin, name);

			cout << "Enter Initial Balance: ";
			cin >> balance;

			cout << "Enter Interest Rate (%): ";
			cin >> rate;

			accounts[totalAccounts] =
			    new SavingsAccount(accNo, name, balance, rate);

			totalAccounts++;

			cout << "Savings Account Created Successfully!\n";
			break;
		}

		case 2: {
			int accNo;
			string name;
			double balance, limit;

			cout << "Enter Account Number: ";
			cin >> accNo;

			cin.ignore();

			cout << "Enter Account Holder Name: ";
			getline(cin, name);

			cout << "Enter Initial Balance: ";
			cin >> balance;

			cout << "Enter Overdraft Limit: ";
			cin >> limit;

			accounts[totalAccounts] =
			    new CheckingAccount(accNo, name, balance, limit);

			totalAccounts++;

			cout << "Checking Account Created Successfully!\n";
			break;
		}

		case 3: {
			int accNo, term;
			string name;
			double balance, rate;

			cout << "Enter Account Number: ";
			cin >> accNo;

			cin.ignore();

			cout << "Enter Account Holder Name: ";
			getline(cin, name);

			cout << "Enter Initial Balance: ";
			cin >> balance;

			cout << "Enter Term (months): ";
			cin >> term;

			cout << "Enter Interest Rate (%): ";
			cin >> rate;

			accounts[totalAccounts] =
			    new FixedDepositAccount(accNo, name, balance, term, rate);

			totalAccounts++;

			cout << "Fixed Deposit Account Created Successfully!\n";
			break;
		}

		case 4: {
			int accNo;
			double amount;

			cout << "Enter Account Number: ";
			cin >> accNo;

			cout << "Enter Deposit Amount: ";
			cin >> amount;

			bool found = false;

			for (int i = 0; i < totalAccounts; i++) {
				if (accNo == accounts[i]->getAccountNumber()) {
					found = true;
					accounts[i]->deposit(amount);
					break;
				}
			}

			if (!found)
				cout << "Account Not Found!\n";

			break;
		}

		case 5: {
			int accNo;
			double amount;

			cout << "Enter Account Number: ";
			cin >> accNo;

			cout << "Enter Withdrawal Amount: ";
			cin >> amount;

			bool found = false;

			for (int i = 0; i < totalAccounts; i++) {
				if (accNo == accounts[i]->getAccountNumber()) {
					found = true;
					accounts[i]->withdraw(amount);
					break;
				}
			}

			if (!found)
				cout << "Account Not Found!\n";

			break;
		}

		case 6: {
			if (totalAccounts == 0) {
				cout << "No Accounts Available!\n";
			} else {
				for (int i = 0; i < totalAccounts; i++) {
					accounts[i]->displayAccountInfo();
				}
			}
			break;
		}

		case 7:
			cout << "Thank You for Using Banking System!\n";
			break;

		default:
			cout << "Invalid Choice!\n";
		}

	} while (choice != 7);

	for (int i = 0; i < totalAccounts; i++) {
		delete accounts[i];
	}

	return 0;
}