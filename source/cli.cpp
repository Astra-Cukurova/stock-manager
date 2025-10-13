#include "cli.hpp"

void CLICommandPattern::CommandPattern() {
	commands["help"] = std::make_unique<HelpCommand>();
	commands["exit"] = std::make_unique<ExitCommand>();
	commands["quit"] = std::make_unique<ExitCommand>();
	commands["enable"] = std::make_unique<EnableCommand>();
	commands["disable"] = std::make_unique<DisableCommand>();
	commands["reset"] = std::make_unique<ResetCommand>();
	commands["clear"] = std::make_unique<ClearCommand>();
}

void CLICommandPattern::ShowPrompt() {
	if (current_mode == "user")
		std::cout << "user >> ";
	else
		std::cout << "admin >> ";
}

void CLICommandPattern::ProcessCommand(const std::string& input) {
	std::stringstream ss(input);
	std::string command_name;
	ss >> command_name;

	if (command_name.empty()) {
		return;
	}

	std::vector<std::string> args;
	std::string arg;
	while (ss >> arg) {
		args.push_back(arg);
	}

	if (commands.count(command_name))
		commands.at(command_name)->Execute(args);
	else
		std::cout << "Unknown command: " << command_name << "\n";
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

bool CLICommandPattern::CheckPassword(std::string_view password) {
	if (password == this->password)
		return true;
	else
		return false;
}
void CLICommandPattern::SetPassword(std::string_view password) {
	this->password = password;
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