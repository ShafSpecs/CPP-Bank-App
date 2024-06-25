#include <random>
#include "Account.h"

Account::Account(std::string account_number):
    account_number(std::move(account_number)), balance(0)
{
    if (this->account_number.empty()) {
        throw std::invalid_argument("Account number cannot be empty.");
    }

    if (this->account_number.length() != 10) {
        throw std::invalid_argument("Account number must be 10 characters long.");
    }
}

void Account::deposit(const double amount) {
    if (amount <= 0) {
        throw std::invalid_argument("Amount must be greater than 0.");
    }

    this->balance += amount;
}

double Account::withdraw(const double amount) {
    if (amount <= 0) {
        throw std::invalid_argument("Amount must be greater than 0.");
    }

    if (this->balance < amount) {
        throw std::invalid_argument("Insufficient balance.");
    }

    this->balance -= amount;

    return amount;
}

double Account::getBalance() const {
    return this->balance;
}

std::string Account::generate_account_number() {
    std::string account_number {};
    std::default_random_engine generator(std::random_device{}());

    for (int i = 0; i < 10; i++) {
        account_number += std::to_string(std::uniform_int_distribution<int>(0, 9)(generator));
    }

    return account_number;
}

std::string Account::getAccountNumber() const {
    return this->account_number;
}
