#pragma once
#include "src\Command.h"

class CustomCommand : public Command {
public:
	CustomCommand(std::string name, std::weak_ptr<Object> target, std::weak_ptr<Object> caller)
		: Command(name, target, caller) {
	};

protected:
	void execute() override {
	
	};
};

