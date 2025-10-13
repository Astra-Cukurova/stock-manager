#include <iostream>
#include "cli.hpp"

int main(void) {
	std::cout << "This is Stock Manager from Astra-Cukurova!\n";

	// for CLI
	CLICommandPattern& CLI = CLICommandPattern::GetInstance();
	CLI.Run();

	return 0;
}