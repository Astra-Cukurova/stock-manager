#include "database.hpp"
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <cstring>

const size_t ABC = 26;
const char* WAREHOUSE = "./database.db";
Product arr[ABC][ABC];
Product *iterator{};
Product null_end;

void InitStock() {
	std::memset(arr, 0, 26 * 26 * sizeof(Product));
	std::ifstream in_file(WAREHOUSE);
	std::string dummy_name;
	long dummy_amount;
	float dummy_buy;
	float dummy_sell;
	while (in_file >> dummy_name >> dummy_amount >> dummy_buy >> dummy_sell) {
		if (!arr[dummy_name[0]][dummy_name[1]].exists()) {
			arr[dummy_name[0]][dummy_name[1]].SetName(dummy_name);
			arr[dummy_name[0]][dummy_name[1]].SetAmount(dummy_amount);
			arr[dummy_name[0]][dummy_name[1]].SetBuyValue(dummy_buy);
			arr[dummy_name[0]][dummy_name[1]].SetSellValue(dummy_sell);
			arr[dummy_name[0]][dummy_name[1]].SetStock(1);
			arr[dummy_name[0]][dummy_name[1]].SetNext(&null_end);
		} else {
			while (iterator->GetNext()) {
				iterator = iterator->GetNext();
			}
			iterator->SetNext(new Product);
			iterator = iterator->GetNext;
			iterator->SetName(dummy_name);
			iterator->SetAmount(dummy_amount);
			iterator->SetBuyValue(dummy_buy);
			iterator->SetSellValue(dummy_sell);
			iterator->SetStock(1);
		}
	}
}

void UpdateStockAmount(std::string dummy_name, long amount_change)
{
}

void DeleteProduct(std::string dummy_name)
{
}

void AddStock(std::string dummy_name, long amount, float buy_value, float sell_value)
{
}

Product *SearchProduct(std::string dummy_name);
{
}
