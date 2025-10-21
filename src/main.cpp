#include <iostream>
#include "cli.hpp"

int main(void) {
	std::cout << "This is Stock Manager from Astra-Cukurova!\n";

	// for CLI
	CLIShell CLI_Shell;
	CLI_Shell.Run();

	return 0;
}