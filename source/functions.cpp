#include "Functions.hpp"

Account* Account::instance = nullptr;

Account& Account::GetInstance() {
    if (instance == nullptr) {
        instance = new Account();
    }
    return *instance;
}

double Account::GetBalance() const {
    return balance;
}

void Account::SetBalance(double new_balance){
    balance = new_balance;
}

void Account::Withdraw(double amount) {
    if (balance - amount >= 0.0) {
        balance -= amount;
    }
}

void Account::Deposit(double amount) {
    balance += amount;
}

void Account::BuyProduct(int count, double product_price) {
    double total = count * product_price;
    if (balance - total >= 0.0) {
        balance -= total;
    }
}

void Account::SellProduct(int count, double product_price) {
    balance += (count * product_price);
}