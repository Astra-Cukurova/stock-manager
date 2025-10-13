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
		if (CLI.CheckPassword("")) {
			CLI.ChangeModeToAdmin();
			return;
		}
		std::string pwd;
		std::cout << "Enter password: ";
		std::getline(std::cin, pwd);
		if (CLI.CheckPassword(pwd)) {
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
	if (CLI.GetCurrentMode() == "admin")
		CLI.ChangeModeToUser();
	else
		std::cout << "Mode is already 'user'.\n";
}

void ResetPasswordCommand::Execute() {
	if (CLI.GetCurrentMode() == "admin") {
		std::string new_psw;
		std::cout << "Enter new password: ";
		std::getline(std::cin, new_psw);
		CLI.SetPassword(new_psw);

		if (new_psw == "")
			std::cout << "Password removed.\n";
		else
			std::cout << "Password changed.\n";
	}
	else {
		std::cout << "Unauthorized access.\n";
	}
}

void ClearCommand::Execute() {
#if defined(_WIN32) || defined(WIN32)
	std::system("cls");
#else
	std::system("clear");
#endif
}