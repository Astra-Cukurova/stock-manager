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
bool CLICore::GetStatusFlag() const {
	return this->status_flag;
}
UserMode CLICore::GetUserMode() const {
	return this->user_mode;
}
const HashedPassword& CLICore::GetHashedPassword() const {
	return this->hashed_password;
}
void CLICore::SetStatusFlag(bool status_flag) {
	this->status_flag = status_flag;
}
void CLICore::SetUserMode(UserMode user_mode) {
	this->user_mode = user_mode;
}
void CLICore::SetHashedPassword(const HashedPassword& hashed_password) {
	this->hashed_password = hashed_password;
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
	std::string input;
	while (this->cli_core.GetStatusFlag()) {
		this->ShowPrompt();
		std::getline(std::cin, input);
		this->ProcessCommand(input);
	}
}

CLIShell::CLIShell() {
    command_map["help"]     = [this](const auto& args) { HelpFunc(args); };
    command_map["clear"]    = [this](const auto& args) { ClearFunc(args); };
    command_map["exit"]     = [this](const auto& args) { ExitFunc(args); };
    command_map["quit"]     = [this](const auto& args) { ExitFunc(args); };
    command_map["q"]        = [this](const auto& args) { ExitFunc(args); };
    command_map["enable"]   = [this](const auto& args) { EnableFunc(args); };
    command_map["disable"]  = [this](const auto& args) { DisableFunc(args); };
    command_map["password"] = [this](const auto& args) { PasswordFunc(args); };
}

void CLIShell::Navigator(const std::string& command, const std::vector<std::string>& args) {
    auto it = command_map.find(command);
    if (it != command_map.end()) {
        it->second(args); // Eşleşen fonksiyonu çağır
    } else {
        std::cout << "Unknown command: " << command << "\n";
    }
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

bool CLIShell::ValidateCommand(const std::vector<std::string>& args, 
                               UserMode required_mode, 
                               size_t max_args, 
                               const std::string& command_name, 
                               const std::string& help_text) {
    // Authentication Check
    if (required_mode != BOTH && cli_core.GetUserMode() != required_mode) {
    	std::cout << "Unauthorized access.\n";
    	return false;
	}
    // Argument Size Check
    if (args.size() > max_args) {
        std::cout << "Error: Too many arguments. Use '" << command_name << " -h' for help.\n";
        return false;
    }
    // Help (-h) Check
    if (!args.empty() && args[0] == "-h") {
        std::cout << help_text << std::endl;
        return false;
    }
    return true;
}

void CLIShell::PrintInvalidArgumentError(const std::string& command_name) {
    std::cout << "Error: '" << command_name << "' command does not take any arguments.\n"
              << "Use '" << command_name << " -h' for help.\n";
}

void CLIShell::HelpFunc(const std::vector<std::string>& args) {
	std::string help_message =
	"  'help'     - Prints the available commands for current user mode.\n";
	
	if (!ValidateCommand(args, BOTH, 1, "help", help_message)) return;

	// If ValidateCommand passed and args is NOT empty, it's an invalid argument.
    if (!args.empty()) {
        PrintInvalidArgumentError("help");
        return;
    }

	std::string message_both = "\n"
	"'help'\n"
	"'clear'\n"
	"'exit'/'quit'/'q'\n"
	"'enable'\n";
	std::string message_admin =
	"'disable'\n"
	"'password'\n";
	std::cout << message_both;

	// If the user mode is ADMIN
	if (this->cli_core.GetUserMode() == ADMIN) std::cout << message_admin;

	std::cout << "For more information, '<command> -h'\n\n";
}
void CLIShell::ClearFunc(const std::vector<std::string>& args) {
	std::string help_message = "\n"
	"  'clear'     - Clears the terminal.\n";
	
	if (!ValidateCommand(args, BOTH, 1, "clear", help_message)) return;

	// If ValidateCommand passed and args is NOT empty, it's an invalid argument.
    if (!args.empty()) {
        PrintInvalidArgumentError("clear");
        return;
    }

#ifdef _WIN32
	std::system("cls");
#else
	std::system("clear");
#endif
}

void CLIShell::ExitFunc(const std::vector<std::string>& args) {
	std::string help_message = "\n"
	"  'exit'     - Terminates the program.\n"
	"  'quit'     - Terminates the program.\n"
	"  'q'        - Terminates the program.\n";
	
	if (!ValidateCommand(args, BOTH, 1, "exit", help_message)) return;

	// If ValidateCommand passed and args is NOT empty, it's an invalid argument.
    if (!args.empty()) {
        PrintInvalidArgumentError("exit/quit/q");
        return;
    }
	this->cli_core.SetStatusFlag(false);
}

void CLIShell::EnableFunc(const std::vector<std::string>& args) {
    // Help message for the 'enable' command.
    std::string help_message = "\n"
        "  'enable'              - Prompts for a password to enter admin mode.\n"
        "  'enable <password>'     - Tries to enter admin mode with the given password.";

    // Perform pre-checks: authorization, argument count, and help flag.
    if (!ValidateCommand(args, USER, 1, "enable", help_message)) {
        return;
    }

    // Check if a password has been set for the system.
    bool is_password_set = !this->cli_core.GetHashedPassword().hash.empty();

    if (is_password_set) {
        std::string input;
        if (args.empty())
			input = HiddenInput("Enter the password: ");
        else
			input = args[0];

        // Verify the provided password.
        if (verify_password(input, this->cli_core.GetHashedPassword())) {
            this->cli_core.SetUserMode(ADMIN);
            std::cout << "Admin mode enabled.\n";
        } else {
            std::cout << "Invalid password.\n";
        }
    } else { // No password is set
        if (args.empty()) {
            // Correct usage: Allow entering admin mode with 'enable' if no password is set.
            this->cli_core.SetUserMode(ADMIN);
            std::cout << "Admin mode enabled. No password is set.\n";
            std::cout << "It is recommended to set a password using the 'password' command.\n";
        } else {
            // Incorrect usage: User provided an argument when no password is set.
            std::cout << "Error: No password has been set. "
                      << "To enter admin mode, type 'enable' without arguments.\n";
        }
    }
}

void CLIShell::DisableFunc(const std::vector<std::string>& args) {
	std::string help_message = "\n"
	"  'disable'         - Sets the user mode to 'user'.\n";
	
	if (!ValidateCommand(args, ADMIN, 1, "disable", help_message)) return;

	// If ValidateCommand passed and args is NOT empty, it's an invalid argument.
    if (!args.empty()) {
        PrintInvalidArgumentError("disable");
        return;
    }

	// Setting the user mode
	this->cli_core.SetUserMode(USER);
}

void CLIShell::PasswordFunc(const std::vector<std::string>& args) {
	std::string help_message = "\n"
	"  'password'                - Prompts for a new password interactively.\n"
	"  'password <new_password>' - Sets the password directly.\n";

	if (!ValidateCommand(args, ADMIN, 1, "password", help_message)) return;

    // Setting the password
    std::string password;
    if (args.empty()) {
        std::cout << "Enter new password: ";
        std::getline(std::cin, password);
    } else {
        password = args[0];
    }
    // Forbid empty input
    if (password.empty()) {
        std::cout << "Error: Password cannot be empty.\n";
        return;
    }
    // Set the hashed password
    try {
        HashedPassword hashed_password = create_password_hash(password);
        this->cli_core.SetHashedPassword(hashed_password);
        std::cout << "Password changed successfully.\n";
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }
}