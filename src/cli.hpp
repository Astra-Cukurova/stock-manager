#ifndef CLI_HPP
#define CLI_HPP

#include <iostream>
#include <functional>
#include <map>
#include "password_hasher.hpp"
#include "functions.hpp"

enum UserMode { USER, ADMIN, BOTH };

class CLICore {
private:
	bool status_flag;
	UserMode user_mode;
	HashedPassword hashed_password;
	CLICore() {
		status_flag = true;
		user_mode = USER;
		hashed_password = { "","" };
	}
public:
	// Singleton
	CLICore(const CLICore&) = delete;
	CLICore& operator=(const CLICore&) = delete;
	static CLICore& GetInstance() {
		static CLICore instance;
		return instance;
	}
	// Getters
	bool GetStatusFlag() const;
	UserMode GetUserMode() const;
	const HashedPassword& GetHashedPassword() const;
	// Setters
	void SetStatusFlag(bool status_flag);
	void SetUserMode(UserMode user_mode);
	void SetHashedPassword(const HashedPassword& hashed_password);
};

class CLIShell {
private:
	CLICore& cli_core = CLICore::GetInstance();
	std::map<std::string, std::function<void(const std::vector<std::string>&)>> command_map;
	
	void ShowPrompt();
	void ProcessCommand(const std::string& input);
	void Navigator(const std::string& command, const std::vector<std::string>& args);

	// Helper Functions
	std::string HiddenInput(const std::string& input_message);
	bool ValidateCommand(const std::vector<std::string>& args, 
                         UserMode required_mode, 
                         size_t max_args, 
                         const std::string& command_name, 
                         const std::string& help_text);
	void PrintInvalidArgumentError(const std::string& command_name);
	
	// Command Funcitons
	void HelpFunc(const std::vector<std::string>& args);
	void ClearFunc(const std::vector<std::string>& args);
	void ExitFunc(const std::vector<std::string>& args);
	void EnableFunc(const std::vector<std::string>& args);
	void DisableFunc(const std::vector<std::string>& args);
	void PasswordFunc(const std::vector<std::string>& args);
	void ShowFunc(const std::vector<std::string>& args);
	void ShowProductFunc(const std::vector<std::string>& args);
	void BalanceFunc(const std::vector<std::string>& args);
	void ProductFunc(const std::vector<std::string>& args);
public:
	CLIShell();
	void Run();
};

#endif // CLI_HPP