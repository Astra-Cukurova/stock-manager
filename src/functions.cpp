#include "functions.hpp"

double Account::GetBalance() const {
    return this->balance;
}

void Account::SetBalance(double new_balance){
    this->balance = new_balance;
}

void Account::Withdraw(double amount) {
    if (this->balance - amount >= 0.0) {
        this->balance -= amount;
    }
}

void Account::Deposit(double amount) {
    this->balance += amount;
}

void Account::BuyProduct(int count, double product_price) {
    double total = count * product_price;
    if (this->balance - total >= 0.0) {
        this->balance -= total;
    }
}

void Account::SellProduct(int count, double product_price) {
    this->balance += (count * product_price);
}
