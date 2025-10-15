#include <iostream>
#include <memory>
#include <sstream>
#include <cstdlib>
#include "cli.hpp"

#ifdef _WIN32
#include <conio.h> // For windows terminal configuration
#else
#include <termios.h> // For Linux terminal configuration, Settings
#include <unistd.h>  // For Linux terminal configuration, STDIN_FILENO

void setEchoMode(bool enable) {
	struct termios tty;
	tcgetattr(STDIN_FILENO, &tty);
	if (!enable) {
		tty.c_lflag &= ~ECHO; // Turn off Echo
	}
	else {
		tty.c_lflag |= ECHO;  // Turn on Echo
	}
	tcsetattr(STDIN_FILENO, TCSANOW, &tty);
}
#endif

// For CLICore
bool CLICore::GetStatusFlag() {
	return this->status_flag;
}
UserMode CLICore::GetUserMode() {
	return this->user_mode;
}
HashedPassword CLICore::GetHashedPassoword() {
	return this->hashed_password;
}
void CLICore::SetStatusFlag(bool status_flag) {
	this->status_flag = status_flag;
}
void CLICore::SetUserMode(UserMode user_mode) {
	this->user_mode = user_mode;
}
void CLICore::SetHashedPassword(HashedPassword hashed_password) {
	this->hashed_password = hashed_password;
}
void CLICore::CLICoreInit() {
	this->status_flag = true;
	this->user_mode = USER;
	this->hashed_password = { "","" };
}

// For CLIShell
void CLIShell::ShowPrompt() {
	if (this->cli_core.GetUserMode() == USER)
		std::cout << "user >> ";
	else
		std::cout << "admin >> ";
}
void CLIShell::ProcessCommand(const std::string& input) {
	std::stringstream ss(input);
	std::string command;
	ss >> command;
	if (command.empty()) {
		return;
	}
	std::vector<std::string> args;
	std::string arg;
	while (ss >> arg) {
		args.push_back(arg);
	}
	this->Navigator(command, args);
}
void CLIShell::Run() {
	this->cli_core.CLICoreInit();
	std::string input;
	while (this->cli_core.GetStatusFlag()) {
		this->ShowPrompt();
		std::getline(std::cin, input);
		this->ProcessCommand(input);
	}
}
void CLIShell::Navigator(const std::string& command, const std::vector<std::string>& args) {
	if (command == "help") {
		this->HelpFunc();
	}
	else if (command == "quit" || command == "exit") {
		this->ExitFunc();
	}
	else if (command == "clear") {
		this->ClearFunc();
	}
	else if (command == "enable") {
		this->EnableFunc(args);
	}
	else if (command == "disable") {
		this->DisableFunc();
	}
	else if (command == "password") {
		this->PasswordFunc(args);
	}
	else std::cout << "Unknown command: " << command << "\n";
}
std::string CLIShell::HiddenInput(const std::string& input_message) {
	std::string input;
	char ch;
	std::cout << input_message;

#ifdef _WIN32
	while ((ch = _getch()) != '\r') { // '\r' Enter key (Carriage Return)

		if (ch == '\b') { // '\b' Backspace key
			if (!input.empty()) {
				input.pop_back(); // Delete last char of the string
				std::cout << "\b \b";
			}
		}
		else {
			input.push_back(ch); // Add char to the password
			std::cout << '*';
		}
	}
#else
	setEchoMode(false);
	while ((ch = getchar()) != '\n') {
		if (ch == 127 || ch == 8) { // 127 (Backspace ASCII) or 8 (CTRL+H ASCII) 
			if (!input.empty()) {
				input.pop_back();
				std::cout << "\b \b" << std::flush;
			}
		}
		else {
			input.push_back(ch);
			std::cout << '*' << std::flush;
		}
	}
	setEchoMode(true);
#endif
	std::cout << std::endl;
	return input;
}
void CLIShell::HelpFunc() {
	std::cout << "Help function called.\n";
}
void CLIShell::ClearFunc() {
#ifdef _WIN32
	std::system("cls");
#else
	std::system("clear");
#endif
}
void CLIShell::ExitFunc() {
	std::cout << "Exit funciton called.\n";
	this->cli_core.SetStatusFlag(false);
}
void CLIShell::EnableFunc(const std::vector<std::string>& args) {
	if (this->cli_core.GetUserMode() == USER) {
		if (this->cli_core.GetHashedPassoword().hash.empty()) {
			this->cli_core.SetUserMode(ADMIN);
			return;
		}
		std::string input;
		if (!args.empty()) {
			input = args[0];
		}
		else {
			input = HiddenInput("Enter the password: ");
		}
		if (verify_password(input, this->cli_core.GetHashedPassoword())) {
			this->cli_core.SetUserMode(ADMIN);
		}
		else {
			std::cout << "Invalid password.\n";
		}
	}
	else {
		std::cout << "Mode is already 'admin'.\n";
	}
}
void CLIShell::DisableFunc() {
	if (this->cli_core.GetUserMode() == ADMIN)
		this->cli_core.SetUserMode(USER);
	else
		std::cout << "Mode is already 'user'.\n";
}
void CLIShell::PasswordFunc(const std::vector<std::string>& args) {
	if (this->cli_core.GetUserMode() == ADMIN) {
		std::string password;
		if (!args.empty()) {
			password = args[0];
		}
		else {
			std::cout << "Enter new password: ";
			std::getline(std::cin, password);
		}
		try {
			HashedPassword hashed_password = create_password_hash(password);
			this->cli_core.SetHashedPassword(hashed_password);
		}
		catch (const std::exception& e) {
			std::cerr << "Error: " << e.what() << std::endl;
			return;
		}
			std::cout << "Password changed.\n";
	}
	else {
		std::cout << "Unauthorized access.\n";
	}
}