#include <iostream>
#include <string>
#include <fstream>
#include "cli.hpp"
#include "database.hpp"
#include "functions.cpp"

int main(void) {
	std::cout << "This is Stock Manager from Astra-Cukurova!\n";

	
	// for CLI
	CLIShell CLI_Shell;
	CLI_Shell.Run();

	return 0;
}