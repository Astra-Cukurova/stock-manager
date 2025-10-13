#ifndef CLI_HPP
#define CLI_HPP

#include <iostream>
#include <string>
#include <memory>
#include <sstream>
#include <string_view>
#include <unordered_map>

class Command {
public:
	virtual ~Command() = default;
	virtual void Execute() = 0;
};

class HelpCommand : public Command {
	void Execute() override;
};

class ExitCommand : public Command {
	void Execute() override;
};

class EnableCommand : public Command {
	void Execute() override;
};

class CLICommandPattern {
private:
	std::string current_mode = "user";
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
	std::string_view GetCurrentMode();
	void ChangeModeToUser();
	void ChangeModeToAdmin();
};

#endif // CLI_HPP