#pragma once
#include "src\Command.h"

class HitCommand : public Command{
public:
	HitCommand(std::string name, std::weak_ptr<Object> caller, std::weak_ptr<Object> target)
		: Command(name, caller, target) {
	};

protected:
	void execute() override {

	};
};

