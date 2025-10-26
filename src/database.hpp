#ifndef DATABASE_HPP
#define DATABASE_HPP

#include <string>

typedef class product {
private:
    std::string name;
    long amount;
    float buy_value;
    float sell_value;
    bool full;
public:
    product() :name{}, amount{}, buy_value{}, sell_value{}, full{} {}
    ~product() {}
} Product;

const size_t MARKET_CAP = 26;
const size_t AISLE_SIZE = 26;

// the previous array i passed as an
// argument will now be global dont worry about it
//
// and also we dont need key just need the name
// i will hash it with the string

int SearchProduct(std::string dummy_name);
void DeleteProduct(std::string dummy_name);
void UpdateStockAmount(std::string dummy_name,
		long amount_change)
void AddStock(std::string dummy_name,
		long amount,
		float buy_value,
		float sell_value);
void InitStock();

#endif
