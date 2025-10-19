#include "iostream"
#include "fstream"
#include "string"
#ifdef _WIN32
#include "stdafx.h"
#endif

// I CANT FUCKIN BELIEVE EVERYTHING IS O(n^2)
// I AM DUMB

typedef class product{
// private:
public:
	std::string name;
	unsigned long long key;
	long amount;
	float buy_value;
	float sell_value;
	bool full;
	product() :name{}, key{}, amount{}, buy_value{}, sell_value{}, full{} {}
	~product() {}
	//
	//	DO WE REALLY HAVE TO DO THIS
	//
	// void set_name() { std::cout << "Enter product's name:"; std::cin >> name; }
	// void set_amount(long a) { amount = a; }
	// void set_buy_value(float a) { buy_value = a; }
	// void set_sell_value(float a) { sell_value = a; }
	// void set_next(class product *a) { next = a; }
}PRODUCT;

const size_t MARKET_CAP = 10;
const size_t AISLE_SIZE = 30;

int searchProduct(PRODUCT arr[MARKET_CAP][AISLE_SIZE]);
void deleteProduct(PRODUCT arr[MARKET_CAP][AISLE_SIZE]);
void listProducts(PRODUCT arr[MARKET_CAP][AISLE_SIZE]);
void addStock(PRODUCT arr[MARKET_CAP][AISLE_SIZE]);
void initStock(PRODUCT arr[MARKET_CAP][AISLE_SIZE]);
const char *WAREHOUSE = "./DataBaseFile";
size_t productIndex{};
size_t aisle{};

int main(void)
{
	size_t userOp{};
	PRODUCT arr[MARKET_CAP][AISLE_SIZE];
	initStock(arr);
	std::cout << "Enter the operation you want to do\n";
	std::cout << "1- Add product\n";
	std::cout << "2- Delete product\n";
	std::cout << "3- Search product\n";
	std::cout << "4- List products\n";
	while (userOp != 5) {
		std::cin >> userOp;
		switch (userOp) {
		case 1: 
			addStock(arr);
			break;
		case 2:
			deleteProduct(arr);
			break;
		case 3:
			searchProduct(arr);
			break;
		case 4:
			listProducts(arr);
			break;
		}
	}
	return 0;
}

void initStock(PRODUCT arr[MARKET_CAP][AISLE_SIZE]) {
	std::ifstream inFile(WAREHOUSE);
	size_t i{}, j{};
	while (inFile >> arr[aisle][productIndex].name) {
		for (size_t k = 0; k <= arr[i][j].name.size(); k++) {
			if ((arr[i][j].name[k] >= 110 && arr[i][j].name[k] <= 122) 
					|| (arr[i][j].name[k] >= 78 && arr[i][j].name[k] <= 90)) {
				arr[i][j].key += 1;
			}
			arr[i][j].key *= 10;
		}
		arr[aisle][productIndex].full = 1;
		inFile  >> arr[aisle][productIndex].amount 
			>> arr[aisle][productIndex].sell_value 
			>> arr[aisle][productIndex].buy_value;
		productIndex++;
		if (productIndex > AISLE_SIZE) {
			productIndex = 0;
			aisle++;
		}
	}
}

void addStock(PRODUCT arr[MARKET_CAP][AISLE_SIZE])
{
	size_t i{}, j{};
	for (; arr[i][j].full && i < MARKET_CAP; i++) {
		for (; arr[i][j].full && j < AISLE_SIZE; j++) {
		}
	}
	arr[i][j].full = 1;
	std::cout << "Enter the name of the product: ";
	std::cin >> arr[i][j].name;
	for (size_t k = 0; k <= arr[i][j].name.size(); k++) {
		if ((arr[i][j].name[k] >= 110 && arr[i][j].name[k] <= 122) 
				|| (arr[i][j].name[k] >= 78 && arr[i][j].name[k] <= 90)) {
			arr[i][j].key += 1;
		}
		arr[i][j].key *= 10;
	}
	std::cout << "Enter the amount of the product: ";
	std::cin >> arr[i][j].amount;
	std::cout << "Enter the sell value: ";
	std::cin >> arr[i][j].sell_value;
	std::cout << "Enter the buy value: ";
	std::cin >> arr[i][j].buy_value;
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
	size_t i{}, j{};
	unsigned long long dummyKey{};
	std::cout << "Enter product key to delete item: ";
	std::cin >> dummyKey;
	for (; i < MARKET_CAP; i++) {
		for (; j < AISLE_SIZE; j++) {
			if (arr[i][j].key == dummyKey) {
				arr[i][j].full = 0;
			}
		}
	}
}

int searchProduct(PRODUCT arr[MARKET_CAP][AISLE_SIZE])
{
	size_t i{}, j{};
	unsigned long long dummyKey{};
	std::cout << "Enter the product key to search: ";
	std::cin >> dummyKey;
	for (; i < MARKET_CAP; i++) {
		for (; j < AISLE_SIZE; j++) {
			if (arr[i][j].key == dummyKey) {
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

