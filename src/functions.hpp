#ifndef FUNCTIONS_HPP
#define FUNCTIONS_HPP

#include <iostream>
#include "database.hpp"

class Account {
private:
    double balance = 0.0;

    Account() = default;
    Account(const Account&) = delete;
    void operator=(const Account&) = delete;
public:
	static Account& GetInstance() {
		static Account instance;
		return instance;
	}
    double GetBalance() const;
    void SetBalance(double new_balance);
    void Withdraw(double amount);
    void Deposit(double amount);
    void BuyProduct(PRODUCT *product);
    void SellProduct(PRODUCT *product);
};

#endif // functions