#include <algorithm>
#include <iostream>
#include <vector>
#include <random>

#include "Account.h"

using namespace std;

int main() {
    vector<Account> accounts{};

    cout << "Welcome to Arthropos Bank! What do you want to do today?\n";
    cout << "1. Open an account\n";
    cout << "2. Close an account\n";
    cout << "3. Deposit money\n";
    cout << "4. Withdraw money\n";
    cout << "5. Transfer money\n";
    cout << "6. Check balance\n";
    cout << "7. Exit" << endl;

    while (true) {
        cout << "\n>> ";

        if (int choice; cin >> choice) {
            switch (choice) {
                case 1: {
                    cout << endl << "Opening an account...\n";

                    cout << "Enter account holder name: ";
                    string account_holder {};
                    cin >> account_holder;

                    const string account_number = Account::generate_account_number();

                    try {
                        Account account(account_holder, account_number);
                        accounts.emplace_back(account);
                    } catch (const invalid_argument &e) {
                        cerr << e.what() << endl;
                    }

                    cout << "New account opened with account number: " << account_number << "!\n";
                    break;
                }
                case 2: {
                    cout << endl << "Closing account...\n";
                    cout << "Enter account number: ";

                    string account_number;
                    cin >> account_number;

                    if (accounts.empty()) {
                        cerr << "No accounts to close.\n";
                        goto break_main_loop;
                    }

                    if (auto it = find_if(accounts.begin(), accounts.end(), [&account_number](const Account &account) -> bool {
                        return account.getAccountNumber() == account_number;
                    }); it != accounts.end()) {
                        accounts.erase(it);
                        cout << "Account with account number " << account_number << " closed.\n";
                    } else {
                        cerr << "Account with account number " << account_number << " not found.\n";
                    }
                    break;
                }
                case 3: {
                    cout << endl << "Depositing money...\n";

                    cout << "Enter account number to deposit in: ";
                    string account_number {};
                    cin >> account_number;

                    if (auto it = find_if(accounts.begin(), accounts.end(), [&account_number](const Account &account) -> bool {
                        return account.getAccountNumber() == account_number;
                    }); it != accounts.end()) {
                        cout << "Account holder: " << it->getAccountName() << endl;
                        cout << "Enter amount to deposit: ";
                        double amount {};
                        cin >> amount;

                        try {
                            it->deposit(amount);
                            cout << "Deposited $" << amount << " into account " << account_number << ".\n";
                        } catch (const invalid_argument &e) {
                            cerr << e.what() << endl;
                        }
                    } else {
                        cerr << "Account with account number " << account_number << " not found.\n";
                    }
                    break;
                }
                case 4: {
                    cout << endl << "Withdrawing money...\n";

                    cout << "Enter account number to withdraw from: ";

                    string account_number;
                    cin >> account_number;

                    if (auto it = find_if(accounts.begin(), accounts.end(), [&account_number](const Account &account) -> bool {
                        return account.getAccountNumber() == account_number;
                    }); it != accounts.end()) {
                        cout << "Account holder: " << it->getAccountName() << endl;
                        cout << "Enter amount to withdraw: ";
                        double amount;
                        cin >> amount;

                        try {
                            const double withdrawn = it->withdraw(amount);
                            cout << "Withdrew $" << withdrawn << " from account " << account_number << ".\n";
                        } catch (const invalid_argument &e) {
                            cerr << e.what() << endl;
                        }
                    } else {
                        cerr << "Account with account number " << account_number << " not found.\n";
                    }
                    break;
                }
                case 5: {
                    cout << endl << "Transferring money...\n";

                    cout << "Enter account number to transfer from: ";
                    string from_account_number {};
                    cin >> from_account_number;

                    if (auto from_account = find_if(accounts.begin(), accounts.end(), [&from_account_number](const Account &account) {
                        return account.getAccountNumber() == from_account_number;
                    }); from_account != accounts.end()) {
                        cout << "Enter account holder: " << from_account->getAccountName() << endl << endl;
                        cout << "Enter account number to transfer to: ";
                        string to_account_number {};
                        cin >> to_account_number;

                        if (auto to_account = find_if(accounts.begin(), accounts.end(), [&to_account_number](const Account &account) {
                            return account.getAccountNumber() == to_account_number;
                        }); to_account != accounts.end()) {
                            cout << "Beneficiary account holder: " << to_account->getAccountName() << endl << endl;
                            cout << "Enter amount to transfer: ";
                            double amount {};
                            cin >> amount;

                            try {
                                from_account->withdraw(amount);
                                to_account->deposit(amount);

                                cout << "Transferred $" << amount << " from account " << from_account_number << " to account " << to_account_number << ".\n";
                            } catch (const invalid_argument &e) {
                                cerr << e.what() << endl;
                            }
                        } else {
                            cerr << "Recepient's account with account number " << to_account_number << " not found.\n";
                        }
                    } else {
                        cerr << "Sender's account with account number " << from_account_number << " not found.\n";
                    }
                    break;
                }
                case 6: {
                    cout << endl << "Checking balance...\n";

                    cout << "Enter account number to check balance: ";
                    string account_number;
                    cin >> account_number;

                    if (auto it = find_if(accounts.begin(), accounts.end(), [&account_number](const Account &account) {
                        return account.getAccountNumber() == account_number;
                    }); it != accounts.end()) {
                        cout << "\nAccount holder: " << it->getAccountName() << endl;
                        cout << "Balance of account " << account_number << " is $" << it->getBalance() << ".\n";
                    }
                    else {
                        cerr << "Account with account number " << account_number << " not found.\n";
                    }
                    break;
                }
                case 7:
                    cout << "Exiting...\n";
                    goto break_main_loop;
                default:
                    cerr << "Invalid choice. Exiting...\n";
                    goto break_main_loop;
            }
        } else {
        invalid_input:
            cerr << "Invalid input. Exiting...\n";

        break_main_loop:
            break;
        }
    }

    return 0;
}
