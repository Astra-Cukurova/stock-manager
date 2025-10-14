#ifndef CLI_HPP
#define CLI_HPP

#include <iostream>
#include <functional>
#include "password_hasher.hpp"

enum UserMode { USER, ADMIN };

class CLICore {
private:
	bool status_flag;
	UserMode user_mode;
	HashedPassword hashed_password;
	CLICore() = default; // Private Constructor
public:
	// Singleton
	CLICore(const CLICore&) = delete;
	CLICore& operator=(const CLICore&) = delete;
	static CLICore& GetInstance() {
		static CLICore instance;
		return instance;
	}
	// Getters
	bool GetStatusFlag();
	UserMode GetUserMode();
	HashedPassword GetHashedPassoword();
	// Setters
	void SetStatusFlag(bool status_flag);
	void SetUserMode(UserMode user_mode);
	void SetHashedPassword(HashedPassword hashed_password);
	// Functions
	void CLICoreInit();
};

class CLIShell {
private:
	CLICore& cli_core = CLICore::GetInstance();
	void ShowPrompt();
	void ProcessCommand(const std::string& input);
	void Navigator(const std::string& command, const std::vector<std::string>& args);
	std::string HiddenInput(const std::string& input_message);
	void HelpFunc();
	void ClearFunc();
	void ExitFunc();
	void EnableFunc(const std::vector<std::string>& args);
	void DisableFunc();
	void PasswordFunc(const std::vector<std::string>& args);
public:
	void Run();
};

#endif // CLI_HPP