#ifndef ACCOUNT_H
#define ACCOUNT_H
# include <iostream>
class Account {
private:
    static Account* instance;
    double balance = 0.0;

    Account() = default;
    Account(const Account&) = delete;
    void operator=(const Account&) = delete;

public:
    static Account& GetInstance();
    double GetBalance() const;
    void SetBalance(double newBalance);
    void Withdraw(double amount);
    void Deposit(double amount);
    void BuyProduct(int count, double productPrice);
    void SellProduct(int count, double productPrice);

};

#endif