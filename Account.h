#ifndef ACCOUNT_H
#define ACCOUNT_H

#include <iostream>

class Account {
public:
    explicit Account(std::string account_number);

    static std::string generate_account_number();

    double withdraw(double amount);
    void deposit(double amount);
    [[nodiscard]] double getBalance() const;
    [[nodiscard]] std::string getAccountNumber() const;
private:
    std::string account_number;
    double balance;
};

#endif //ACCOUNT_H
