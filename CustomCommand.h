#pragma once
#include "src\CommandBase.h"

class CustomCommand : public CommandBase {
public:
	CustomCommand(std::weak_ptr<ObjectBase> target, std::weak_ptr<ObjectBase> caller) 
		: CommandBase(target, caller) {
	};

protected:
	void execute() override {
	
	};
};

