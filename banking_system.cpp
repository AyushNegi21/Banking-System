#include <iostream>
#include <vector>
#include <string>
#include <limits>

using namespace std;

class BankAccount {
private:
    string accountHolder;
    int accountNumber;
    double balance;

public:
    BankAccount(string name, int accNum) {
        accountHolder = name;
        accountNumber = accNum;
        balance = 0.0;
    }

    void deposit(double amount) {
        if (amount > 0) {
            balance += amount;
            cout << "Deposited ₹" << amount << " successfully.\n";
        } else {
            cout << "Invalid deposit amount.\n";
        }
    }

    void withdraw(double amount) {
        if (amount <= balance && amount > 0) {
            balance -= amount;
            cout << "Withdrawn ₹" << amount << " successfully.\n";
        } else if (amount > balance) {
            cout << "Insufficient funds. Your current balance is ₹" << balance << ".\n";
        } else {
            cout << "Invalid withdrawal amount.\n";
        }
    }

    void displayBalance() const {
        cout << "Account Holder: " << accountHolder << "\n";
        cout << "Account Number: " << accountNumber << "\n";
        cout << "Current Balance: ₹" << balance << "\n";
    }

    int getAccountNumber() const {
        return accountNumber;
    }
};

vector<BankAccount> accounts;

BankAccount* findAccount(int accNum) {
    for (auto& acc : accounts) {
        if (acc.getAccountNumber() == accNum)
            return &acc;
    }
    return nullptr;
}

void clearInput() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

int generateAccountNumber() {
    int base = 1000;
    while (findAccount(base)) {
        base++;
    }
    return base;
}

void createAccount() {
    string name;
    int accNum;

    cout << "Enter account holder name: ";
    clearInput();
    getline(cin, name);

    accNum = generateAccountNumber();
    cout << "Suggested account number: " << accNum << "\n";
    cout << "Do you want to use this account number? (y/n): ";
    char choice;
    cin >> choice;

    if (tolower(choice) != 'y') {
        cout << "Enter your desired account number: ";
        while (!(cin >> accNum)) {
            cout << "Invalid input. Enter numeric account number: ";
            clearInput();
        }

        if (findAccount(accNum)) {
            cout << "Account number already exists!\n";
            return;
        }
    }

    BankAccount newAcc(name, accNum);
    accounts.push_back(newAcc);
    cout << "Account created successfully with Account Number: " << accNum << "\n";
}

void accountMenu() {
    int accNum;
    cout << "Enter your account number: ";
    while (!(cin >> accNum)) {
        cout << "Invalid input. Enter numeric account number: ";
        clearInput();
    }

    BankAccount* acc = findAccount(accNum);
    if (!acc) {
        cout << "Account not found!\n";
        return;
    }

    int choice;
    do {
        cout << "\n--- Account Menu ---\n";
        cout << "1. Deposit\n2. Withdraw\n3. Display Balance\n4. Exit to Main Menu\n";
        cout << "Enter your choice: ";
        while (!(cin >> choice)) {
            cout << "Invalid input. Enter a number between 1 and 4: ";
            clearInput();
        }

        double amount;
        switch (choice) {
            case 1:
                cout << "Enter amount to deposit: ₹";
                while (!(cin >> amount)) {
                    cout << "Invalid input. Enter a valid amount: ₹";
                    clearInput();
                }
                acc->deposit(amount);
                break;
            case 2:
                cout << "Enter amount to withdraw: ₹";
                while (!(cin >> amount)) {
                    cout << "Invalid input. Enter a valid amount: ₹";
                    clearInput();
                }
                acc->withdraw(amount);
                break;
            case 3:
                acc->displayBalance();
                break;
            case 4:
                cout << "Returning to main menu...\n";
                break;
            default:
                cout << "Invalid choice.\n";
        }
    } while (choice != 4);
}

int main() {
    int choice;
    do {
        cout << "\n=== BANK MANAGEMENT SYSTEM ===\n";
        cout << "1. Create Account\n2. Access Account\n3. Exit\n";
        cout << "Enter your choice: ";
        while (!(cin >> choice)) {
            cout << "Invalid input. Enter a number between 1 and 3: ";
            clearInput();
        }

        switch (choice) {
            case 1:
                createAccount();
                break;
            case 2:
                accountMenu();
                break;
            case 3:
                cout << "Thank you for using our bank system.\n";
                break;
            default:
                cout << "Invalid choice. Try again.\n";
        }
    } while (choice != 3);

    return 0;
}
