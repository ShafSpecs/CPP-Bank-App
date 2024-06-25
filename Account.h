#ifndef ACCOUNT_H
#define ACCOUNT_H

#include <iostream>

class Account {
public:
    explicit Account(std::string account_holder, std::string account_number);

    static std::string generate_account_number();
    static void transfer(Account &from, Account &to, double amount);

    double withdraw(double amount);
    void deposit(double amount);
    [[nodiscard]] double getBalance() const;
    [[nodiscard]] std::string getAccountNumber() const;
    [[nodiscard]] std::string getAccountName() const;
private:
    std::string account_number;
    double balance;
    std::string name;
};

#endif //ACCOUNT_H
