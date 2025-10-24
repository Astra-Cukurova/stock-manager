#ifndef DATABASE_HPP
#define DATABASE_HPP

#include <string>
#include <cstddef>

typedef class product {
public:
    std::string name;
    unsigned long long key;
    long amount;
    float buy_value;
    float sell_value;
    bool full;
    product() :name{}, key{}, amount{}, buy_value{}, sell_value{}, full{} {}
    ~product() {}
} PRODUCT;

const size_t MARKET_CAP = 10;
const size_t AISLE_SIZE = 30;

extern const char* WAREHOUSE;
extern size_t productIndex;
extern size_t aisle;

int searchProduct(PRODUCT arr[MARKET_CAP][AISLE_SIZE]);
void deleteProduct(PRODUCT arr[MARKET_CAP][AISLE_SIZE]);
void listProducts(PRODUCT arr[MARKET_CAP][AISLE_SIZE]);
void addStock(PRODUCT arr[MARKET_CAP][AISLE_SIZE]);
void initStock(PRODUCT arr[MARKET_CAP][AISLE_SIZE]);

#endif