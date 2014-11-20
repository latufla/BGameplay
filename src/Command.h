#pragma once
#include <memory>
#include "Object.h"

class Command {
public:
	Command() = delete;
	Command(std::string name, std::weak_ptr<Object> caller, std::weak_ptr<Object> target);

	~Command() = default;

	bool tryToExecute();

	std::string getName() const { return name; }

protected:
	virtual bool canExecute();
	virtual void execute() = 0;

	std::string name;
	
	std::weak_ptr<Object> caller;
	std::weak_ptr<Object> target;
};

