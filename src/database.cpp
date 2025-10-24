#include "database.hpp"
#include <iostream>
#include <fstream>

const char* WAREHOUSE = "./database.db";
size_t productIndex{};
size_t aisle{};

void initStock(PRODUCT arr[MARKET_CAP][AISLE_SIZE]) {
    std::ifstream inFile(WAREHOUSE);
    size_t i{}, j{};
    while (inFile >> arr[aisle][productIndex].name) {
        for (size_t k = 0; k <= arr[aisle][productIndex].name.size(); k++) {
            if ((arr[aisle][productIndex].name[k] >= 110 && arr[aisle][productIndex].name[k] <= 122)
                || (arr[aisle][productIndex].name[k] >= 78 && arr[aisle][productIndex].name[k] <= 90)) {
                arr[aisle][productIndex].key += 1;
            }
            arr[aisle][productIndex].key *= 10;
        }
        
        arr[aisle][productIndex].full = 1;
        inFile >> arr[aisle][productIndex].amount
            >> arr[aisle][productIndex].sell_value
            >> arr[aisle][productIndex].buy_value;
        
        productIndex++;
        if (productIndex >= AISLE_SIZE) {
            productIndex = 0;
            aisle++;
            if (aisle >= MARKET_CAP) break;
        }
    }
}

void addStock(PRODUCT arr[MARKET_CAP][AISLE_SIZE])
{
    if (aisle >= MARKET_CAP) {
        std::cout << "Warehouse is full!" << std::endl;
        return;
    }

    arr[aisle][productIndex].full = 1;
    std::cout << "Enter the name of the product: ";
    std::cin >> arr[aisle][productIndex].name;

    arr[aisle][productIndex].key = 0;
    for (size_t k = 0; k <= arr[aisle][productIndex].name.size(); k++) {
        if ((arr[aisle][productIndex].name[k] >= 110 && arr[aisle][productIndex].name[k] <= 122)
            || (arr[aisle][productIndex].name[k] >= 78 && arr[aisle][productIndex].name[k] <= 90)) {
            arr[aisle][productIndex].key += 1;
        }
        arr[aisle][productIndex].key *= 10;
    }

    std::cout << "Enter the amount of the product: ";
    std::cin >> arr[aisle][productIndex].amount;
    std::cout << "Enter the sell value: ";
    std::cin >> arr[aisle][productIndex].sell_value;
    std::cout << "Enter the buy value: ";
    std::cin >> arr[aisle][productIndex].buy_value;

    productIndex++;
    if (productIndex >= AISLE_SIZE) {
        productIndex = 0;
        aisle++;
    }
}

void listProducts(PRODUCT arr[MARKET_CAP][AISLE_SIZE])
{
    for (size_t i = 0; i < MARKET_CAP; i++) {
        for (size_t j = 0; j < AISLE_SIZE; j++) {
            if (arr[i][j].full) {
                std::cout << arr[i][j].key << '\t' << arr[i][j].name << '\n';
            }
        }
    }
}

void deleteProduct(PRODUCT arr[MARKET_CAP][AISLE_SIZE])
{
    unsigned long long dummyKey{};
    std::cout << "Enter product key to delete item: ";
    std::cin >> dummyKey;
    
    for (size_t i = 0; i < MARKET_CAP; i++) {
        for (size_t j = 0; j < AISLE_SIZE; j++) {
            if (arr[i][j].full && arr[i][j].key == dummyKey) {
                arr[i][j].full = 0;
                arr[i][j].name = "";
                arr[i][j].key = 0;
                arr[i][j].amount = 0;
                std::cout << "Product deleted.\n";
                return; 
            }
        }
    }
    std::cout << "Product not found.\n";
}

int searchProduct(PRODUCT arr[MARKET_CAP][AISLE_SIZE])
{
    unsigned long long dummyKey{};
    std::cout << "Enter the product key to search: ";
    std::cin >> dummyKey;

    for (size_t i = 0; i < MARKET_CAP; i++) {
        for (size_t j = 0; j < AISLE_SIZE; j++) {
            if (arr[i][j].full && arr[i][j].key == dummyKey) {
                std::cout << "Name: " << arr[i][j].name << '\n'
                    << "Amount: " << arr[i][j].amount << '\n'
                    << "Sell Value: " << arr[i][j].sell_value << '\n'
                    << "Buy Value: " << arr[i][j].buy_value << '\n';
                return 0;
            }
        }
    }
    std::cout << "Your item does not exist.\n";
    return 1;
}