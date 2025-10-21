#include "Functions.hpp"
#include "../src/database.hpp"

Account* Account::instance = nullptr;

Account& Account::GetInstance() {
    if (this->instance == nullptr) {
        this->instance = new Account();
    }
    return *(this->instance);
}

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

void Account::BuyProduct(PRODUCT *product) {
    double total = product->amount * product->buy_value;
    if (this->balance - total >= 0.0) {
        this->balance -= total;
    }
}

void Account::SellProduct(PRODUCT *product) {
    this->balance += (product->amount * product->sell_value);
}