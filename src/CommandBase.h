#pragma once
#include <memory>
#include "BehaviorBase.h"

class CommandBase {
public:
	CommandBase() = delete;
	CommandBase(std::weak_ptr<ObjectBase>, std::weak_ptr<ObjectBase>);

	~CommandBase() = default;

	virtual bool tryToExecute();

	std::string getName() const { return name; }

protected:
	virtual bool canExecute();
	virtual void execute() = 0;

	std::string name;
	
	std::weak_ptr<ObjectBase> caller;
	std::weak_ptr<ObjectBase> target;
};

