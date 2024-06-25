#include <random>
#include "Account.h"

using namespace std;

Account::Account(string account_holder, string account_number):
    account_number(move(account_number)), balance(0), name(move(account_holder))
{
    if (this->account_number.empty()) {
        throw invalid_argument("Account number cannot be empty.");
    }

    if (this->account_number.length() != 10) {
        throw invalid_argument("Account number must be 10 characters long.");
    }

    if (this->name.empty()) {
        throw invalid_argument("Account holder name cannot be empty.");
    }
}

void Account::deposit(const double amount) {
    if (amount <= 0) {
        throw invalid_argument("Amount must be greater than 0.");
    }

    this->balance += amount;
}

double Account::withdraw(const double amount) {
    if (amount <= 0) {
        throw invalid_argument("Amount must be greater than 0.");
    }

    if (this->balance < amount) {
        throw invalid_argument("Insufficient balance.");
    }

    this->balance -= amount;

    return amount;
}

double Account::getBalance() const {
    return this->balance;
}

string Account::generate_account_number() {
    string account_number {};
    default_random_engine generator(random_device{}());

    for (int i = 0; i < 10; i++) {
        account_number += to_string(uniform_int_distribution<int>(0, 9)(generator));
    }

    return account_number;
}

string Account::getAccountNumber() const {
    return this->account_number;
}

void Account::transfer(Account &from, Account &to, const double amount) {
    if (amount <= 0) {
        throw invalid_argument("Amount must be greater than 0.");
    }

    if (from.getBalance() < amount) {
        throw invalid_argument("Insufficient balance.");
    }

    from.withdraw(amount);
    to.deposit(amount);
}

string Account::getAccountName() const {
    return this->name;
}
