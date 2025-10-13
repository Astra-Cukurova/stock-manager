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
			CLI.ChangeModeToAdmin();
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
	// For windows
	std::system("cls");
}

void CLICommandPattern::CommandPattern() {
	commands["help"] = std::make_unique<HelpCommand>();
	commands["exit"] = std::make_unique<ExitCommand>();
	commands["quit"] = std::make_unique<ExitCommand>();
	commands["enable"] = std::make_unique<EnableCommand>();
	commands["disable"] = std::make_unique<DisableCommand>();
	commands["clear"] = std::make_unique<ClearCommand>();
}

void CLICommandPattern::ShowPrompt() {
	if (current_mode == "user") {
		std::cout << "user >> ";
	}
	else {
		std::cout << "admin >> ";
	}
}

void CLICommandPattern::ProcessCommand(const std::string& input) {
	std::stringstream ss(input);
	std::string command_name;
	ss >> command_name;

	if (command_name.empty()) {
		return;
	}

	if (commands.count(command_name)) {
		commands.at(command_name)->Execute();
	}
	else {
		std::cout << "Unknown command: " << command_name << "\n";
	}
}

void CLICommandPattern::Run() {
	this->CommandPattern();
	std::string input;
	while (true) {
		this->ShowPrompt();
		std::getline(std::cin, input);
		this->ProcessCommand(input);
	}
}

std::string_view CLICommandPattern::GetCurrentMode() {
	return this->current_mode;
}

void CLICommandPattern::ChangeModeToUser() {
	this->current_mode = "user";
}

void CLICommandPattern::ChangeModeToAdmin() {
	this->current_mode = "admin";
}