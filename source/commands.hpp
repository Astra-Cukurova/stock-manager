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

class DisableCommand : public Command {
	void Execute() override;
};

class ResetPasswordCommand : public Command {
	void Execute() override;
};

class ClearCommand : public Command {
	void Execute() override;
};

#endif // COMMANDS_HPP