#ifndef CLI_HPP
#define CLI_HPP

#include <iostream>
#include <string>
#include <memory>
#include <sstream>
#include <string_view>
#include <unordered_map>
#include <cstdlib>
#include "commands.hpp"

class CLICommandPattern {
private:
	std::string current_mode = "user";
	struct {
		std::string hash = "";
		std::string salt = "";
	} HashedResult;
	std::unordered_map<std::string, std::unique_ptr<Command>> commands;

	CLICommandPattern() = default; // private constructor
	CLICommandPattern(const CLICommandPattern&) = delete;
	CLICommandPattern& operator=(const CLICommandPattern&) = delete;
public:
	static CLICommandPattern& GetInstance() {
		static CLICommandPattern instance;
		return instance;
	}
	void CommandPattern();
	void ShowPrompt();
	void ProcessCommand(const std::string& input);
	void Run();
	void SetHashedResult(std::string_view hash, std::string_view salt);
	std::string GetHash();
	std::string GetSalt();
	std::string_view GetCurrentMode();
	void ChangeModeToUser();
	void ChangeModeToAdmin();
};

#endif // CLI_HPP