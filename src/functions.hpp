<<<<<<< HEAD:src/functions.hpp
#ifndef FUNCTIONS_HPP
#define FUNCTIONS_HPP

#include <iostream>
#include "database.hpp"

=======
#ifndef ACCOUNT_H
#define ACCOUNT_H
#include <iostream>
>>>>>>> 86974c8c859305a5681a7cdd10e4ed60ef7dd0d9:source/functions.hpp
class Account {
private:
    static Account* instance;
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
<<<<<<< HEAD:src/functions.hpp
    void BuyProduct(PRODUCT *product);
    void SellProduct(PRODUCT *product);
};

#endif // functions
=======
    void BuyProduct(int count, double new_balance);
    void SellProduct(int count, double new_balance);
};

#endif
>>>>>>> 86974c8c859305a5681a7cdd10e4ed60ef7dd0d9:source/functions.hpp
