#include <iostream>
#include "cli.hpp"

int main(void) {
	std::cout << "This is Stock Manager from Astra-Cukurova!\n";
	CLICommandPattern& cli = CLICommandPattern::GetInstance();
	cli.Run();
	return 0;
}