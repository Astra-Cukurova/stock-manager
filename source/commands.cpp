#include "commands.hpp"
#include "cli.hpp"
#include "password_hasher.hpp"

#ifdef _WIN32
	#include <conio.h> // For windows password input
#else
	#include <termios.h> // For Linux password input, terminal settings
	#include <unistd.h>  // For Linux password input, STDIN_FILENO

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

CLICommandPattern& CLI = CLICommandPattern::GetInstance();

std::string InputPassword() {
	std::string pwd;
	char ch;
	std::cout << "Enter password: ";

#ifdef _WIN32
	while ((ch = _getch()) != '\r') { // '\r' Enter key (Carriage Return)

		if (ch == '\b') { // '\b' Backspace key
			if (!pwd.empty()) {
				pwd.pop_back(); // Delete last char of the string
				std::cout << "\b \b";
			}
		}
		else {
			pwd.push_back(ch); // Add char to the password
			std::cout << '*';
		}
	}
#else
	setEchoMode(false);
	while ((ch = getchar()) != '\n') {
		if (ch == 127 || ch == 8) { // 127 (Backspace ASCII) or 8 (CTRL+H ASCII) 
			if (!password.empty()) {
				password.pop_back();
				std::cout << "\b \b" << std::flush;
			}
		}
		else {
			password.push_back(ch);
			std::cout << '*' << std::flush;
		}
	}
	setEchoMode(true);
#endif
	std::cout << std::endl;
	return pwd;
}

void HelpCommand::Execute(const std::vector<std::string>& args) {
	(void)args;
	std::cout << "Help...\n";
}

void ExitCommand::Execute(const std::vector<std::string>& args) {
	(void)args;
	std::cout << "Terminating...\n";
	std::exit(0);
}

void EnableCommand::Execute(const std::vector<std::string>& args) {
	(void)args;
	if (CLI.GetCurrentMode() == "user") {
		if (CLI.GetHash() == "") {
			CLI.ChangeModeToAdmin();
			return;
		}
		if (verify_password(InputPassword(), CLI.GetHash(), CLI.GetSalt())) {
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

void DisableCommand::Execute(const std::vector<std::string>& args) {
	(void)args;
	if (CLI.GetCurrentMode() == "admin")
		CLI.ChangeModeToUser();
	else
		std::cout << "Mode is already 'user'.\n";
}

void ResetCommand::Execute(const std::vector<std::string>& args) {
	if (args[0] == "password") {
		if (CLI.GetCurrentMode() == "admin") {
			std::string new_pwd;
			std::cout << "Enter new password: ";
			std::getline(std::cin, new_pwd);
			try {
				HashedResult result = create_password_hash(new_pwd);
				CLI.SetHashedResult(result.hash, result.salt);
			}
			catch (const std::exception& e) {
				std::cerr << "Fatal Error: " << e.what() << std::endl;
				return;
			}
			std::cout << "Password changed.\n";
		}
		else {
			std::cout << "Unauthorized access.\n";
		}
	}
	else {
		std::cout << "Unknown command.\n";
	}
}

void ClearCommand::Execute(const std::vector<std::string>& args) {
	(void)args;
#ifdef _WIN32
	std::system("cls");
#else
	std::system("clear");
#endif
}