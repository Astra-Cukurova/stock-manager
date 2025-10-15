#include "iostream"
#include "fstream"
#include "string"

typedef class product{
private:
	std::string type;
	long sell_value;
	long buy_value;
	long amount;
public:
	void set_type(void) { cin >> type; }
	void sell_value(long a) { sell_value = a; }
	void buy_value(long a) { buy_value = a; }
	void set_amount(long a) { amount = a; }
} PRODUCT;

typedef class handle{
private:
	std::string product_name;
	long prod_num;
	class handle *left;
	class handle *right;
	Product *prod;
	COLOR node_color;
public:
	void set_name(void) { std::cin >> product_name; }
} HANDLE;

typedef enum color{
	BLACK;
	RED;
} COLOR;

const char *WAREHOUSE = "./DataBaseFile";
HANDLE *head = NULL;
HANDLE *anchor = NULL;
HANDLE *hook = NULL;

int deleteProduct(PRODUCT *example_prod) { ;}
PRODUCT *searchProduct() { ;}
// not sure whether we should search by prod_num or name
// i guess we could just have cli function list to list them all

int addProduct(std::string name)
{
	// Can add different function to change amount and market price
	// No need to overbloat this one
	if (!head) {
		head = new HANDLE;
		head->set_name;
	} else {
		//
	}
}

int createTree()
{
	// read from DataBaseFile at startup and create the tree
	//
	// possible optimization place but not now
	std::ifstream inFile(WAREHOUSE);
}

int dumpTree()
{
	// go through all nodes 
	// and write an updated list of the products 
	// at shutdown
	std::ofstream outFile(WAREHOUSE);
}
