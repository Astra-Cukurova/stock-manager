#include "iostream"
#include "fstream"
#include "string"
#ifdef _WIN32
#include "stdafx.h"
#endif

typedef enum color{
	BLACK = 0,
	RED = 1
} COLOR;

int product_number = 0; // will increment this as we go

typedef class product{
private:
	std::string type;
	long sell_value;
	long buy_value;
	long amount;
public:
	~product() {};
	void set_type(void) { std::cin >> type; }
	void set_sell_value(long a) { sell_value = a; }
	void set_buy_value(long a) { buy_value = a; }
	void set_amount(long a) { amount = a; }
} PRODUCT;

typedef class handle{
private:
	std::string product_name;
	long prod_num;
	PRODUCT *prod;
	class handle *left;
	class handle *right;
	COLOR node_color;
public:
	handle() :  product_name{}, 
		prod_num{product_number}, 
		prod{NULL}, 
		left{NULL}, right{NULL}, 
		node_color{BLACK} {}
	void set_name(void) { std::cin >> product_name; }
	void set_node_color(COLOR a) { node_color = a; }
	void set_prod(PRODUCT *a) { prod = a; }
	void set_left(class handle *a) { left = a; }
	void set_right(class handle *a) { right = a; }
	void set_prod_num(long a) { prod_num = a; }
} HANDLE;


const char *WAREHOUSE = "./DataBaseFile";
HANDLE *head = NULL;
HANDLE *anchor = NULL;
HANDLE *hook = NULL;


// a dummy main just to compile
// i cant believe that in 2025
// we are still using a language
// which needs an entrypoint 
// oh fuck my life
int main(void)
{
	return 0;
}

// int deleteProduct(PRODUCT *example_prod) { ;}
// PRODUCT *searchProduct() { ;}
// not sure whether we should search by prod_num or name
// i guess we could just have cli function list to list them all

int addProduct(std::string name)
{
	// Can add different function to change amount and market price
	// No need to overbloat this one
	if (!head) {
		head = new HANDLE;
		HANDLE endPoint;
		endPoint.set_node_color(BLACK);
		head->set_left(&endPoint);
		head->set_right(&endPoint);
		head->set_name();
	} else {
		//
	}
	return 0;
}

int createTree()
{
	std::ifstream inFile(WAREHOUSE);
	return 0;
}

int dumpTree()
{
	// go through all nodes 
	// and write an updated list of the products 
	// at shutdown
	std::ofstream outFile(WAREHOUSE);
	return 0;
}
