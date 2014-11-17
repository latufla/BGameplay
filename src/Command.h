#pragma once
#include <memory>
#include "Behavior.h"

class Command {
public:
	Command() = delete;
	Command(std::string name, std::weak_ptr<Object>, std::weak_ptr<Object>);

	~Command() = default;

	virtual bool tryToExecute();

	std::string getName() const { return name; }

protected:
	virtual bool canExecute();
	virtual void execute() = 0;

	std::string name;
	
	std::weak_ptr<Object> caller;
	std::weak_ptr<Object> target;
};

