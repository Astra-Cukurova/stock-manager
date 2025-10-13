#include "commands.hpp"
#include "cli.hpp"

CLICommandPattern& CLI = CLICommandPattern::GetInstance();

void HelpCommand::Execute() {
	std::cout << "Help...\n";
}

void ExitCommand::Execute() {
	std::cout << "Terminating...\n";
	std::exit(0);
}

void EnableCommand::Execute() {
	if (CLI.GetCurrentMode() == "user") {
		std::string pwd;
		std::cout << "Enter password: ";
		std::getline(std::cin, pwd);
		if (pwd == "123") {
			CLI.ChangeModeToAdmin();
		}
		else {
			std::cout << "Invalid password.\n";
		}
	}
	else {
		std::cout << "Mode is already 'admin'.\n";
	}
}

void DisableCommand::Execute() {
	if (CLI.GetCurrentMode() == "admin") {
		std::string pwd;
		std::cout << "Enter password: ";
		std::getline(std::cin, pwd);
		if (pwd == "321") {
			CLI.ChangeModeToUser();
		}
		else {
			std::cout << "Invalid password.\n";
		}
	}
	else {
		std::cout << "Mode is already 'user'.";
	}
}

void ClearCommand::Execute() {
#if defined(_WIN32) || defined(WIN32)
	std::system("cls");
#else
	std::system("clear");
#endif
}