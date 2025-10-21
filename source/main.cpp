#include <iostream>
#include <string>
#include <fstream>
#include "cli.hpp"
#include "../src/database.hpp"
#include "functions.cpp"

#ifdef _WIN32
#include <stdfax.h>
#endif

int main(void) {
	std::cout << "This is Stock Manager from Astra-Cukurova!\n";

	
	// for CLI
	CLICommandPattern& CLI = CLICommandPattern::GetInstance();
	CLI.Run();

	return 0;
}