#pragma once
#include <memory>
#include "Object.h"

namespace bg {
	class Command {
	public:
		Command() = delete;
		Command(std::string name, std::weak_ptr<Object> caller, std::weak_ptr<Object> target);

		~Command() = default;

		bool tryToExecute();

		std::string getName() const { return name; }

	protected:
		virtual bool canExecute(); // allow
		virtual void execute() = 0; // implement

		std::string name;

		std::weak_ptr<Object> caller;
		std::weak_ptr<Object> target;
	};
}

