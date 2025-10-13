#ifndef COMMANDS_HPP
#define COMMANDS_HPP

#include <iostream>
#include <string>
#include <memory>
#include <sstream>
#include <string_view>
#include <unordered_map>
#include <cstdlib>

class Command {
public:
	virtual ~Command() = default;
	virtual void Execute(const std::vector<std::string>& args) = 0;
};

class HelpCommand : public Command {
	void Execute(const std::vector<std::string>& args) override;
};

class ExitCommand : public Command {
	void Execute(const std::vector<std::string>& args) override;
};

class EnableCommand : public Command {
	void Execute(const std::vector<std::string>& args) override;
};

class DisableCommand : public Command {
	void Execute(const std::vector<std::string>& args) override;
};

class ResetCommand : public Command {
	void Execute(const std::vector<std::string>& args) override;
};

class ClearCommand : public Command {
	void Execute(const std::vector<std::string>& args) override;
};

#endif // COMMANDS_HPP