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

void Account::SetBalance(double NewBalance){
    balance = NewBalance;
}

void Account::Withdraw(double amount) {
    if (balance - amount >= 0.0) {
        balance -= amount;
    }
}

void Account::Deposit(double amount) {
    balance += amount;
}

void Account::BuyProduct(int count, double ProductPrice) {
    double total = count * ProductPrice;
    if (balance - total >= 0.0) {
        balance -= total;
    }
}

void Account::SellProduct(int count, double ProductPrice) {
    balance += (count * ProductPrice);
}