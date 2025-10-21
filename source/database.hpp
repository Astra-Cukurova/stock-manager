// SEARCH FOR TODOS TO UNDERSTAND WHAT TO DO
// 
// CTRL-F TODO
#include "iostream"
#include "fstream"
#include "string"

#ifdef _WIN32
#include "stdafx.h"
#endif

typedef class product{
public:
	std::string name;
	unsigned long long key;
	long amount;
	float buy_value;
	float sell_value;
	bool full;
	product() :name{}, key{}, amount{}, buy_value{}, sell_value{}, full{} {}
	~product() {}
}PRODUCT;

const size_t MARKET_CAP = 26;
const size_t AISLE_SIZE = 26;
const char *WAREHOUSE = "./DataBaseFile";
size_t productIndex{};
size_t aisle{};
PRODUCT arr[MARKET_CAP][AISLE_SIZE];

PRODUCT *SearchProduct();
void DeleteProduct(long long key);
void ChangeProductAmount(long long key);
void ListProducts();
int AddStock();
void InitStock();

// static Account& GetInstance();
// double GetBalance() const;
// void SetBalance(double new_balance);
// void Withdraw(double amount);
// void Deposit(double amount);
// void BuyProduct(int count, double new_balance);
// void SellProduct(int count, double new_balance);

void initStock() {
	memset(arr, 0, sizeof(PRODUCT) * 26 * 26);
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

void addStock() {
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
	// TODO: actually get user account
	USER_ACCOUNT.SetBalance(USER_ACCOUNT.GetBalance() - arr[i][j].amount * arr[i][j].buy_value);
}

void listProducts() {
	for (size_t i = 0; i < MARKET_CAP; i++) {
		for (size_t j = 0; j < AISLE_SIZE; j++) {
			if (arr[i][j].full) {
				std::cout << arr[i][j].key << '\t' << arr[i][j].name << '\n';
			}
		}
	}
}

void deleteProduct(long long id) {
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
	USER_ACCOUNT.SetBalance(USER_ACCOUNT.GetBalance() - (arr[i][j].amount * arr[i][j].sell_value);
}

int searchProduct(long long id) {
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

int ChangeProductAmount(long long id) {
	int i{}, j{};
	int dummy_amount{};
	while (arr[i][j].key != id && i < MARKET_CAP) {
		j = 0;
		while (arr[i][j].key != id && j < AISLE_SIZE) {
			j++;
		}
		i++;
	}
	if (!arr[i][j].full) {
		std::cout << "Couldn't find the product" << std::endl;
		return 1;
	}
	std::cout << "Enter the change in the product you chose" << std::endl;
	std::cin >> dummy_amount;
	if (arr[i][j].amount < (-dummy_amount)) {
		std::cout << "There isn't even enough of it :(";
		return 1;
	}
	arr[i][j].amount += dummy_amount;
	if (dummy_amount > 0) {
		USER_ACCOUNT.SetBalance(USER_ACCOUNT.GetBalance() + dummy_amount * arr[i][j].buy_value);
	} else {
		USER_ACCOUNT.SetBalance(USER_ACCOUNT.GetBalance() + dummy_amount * arr[i][j].sell_value);
	}
	return 0;
}
