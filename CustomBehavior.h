#pragma once
#include "src\Behavior.h"
#include "CustomFactory.h"

class CustomBehavior : public Behavior {
public:
	CustomBehavior(std::weak_ptr<BehaviorInfo> info, std::weak_ptr<Object> obj, Factory* factory)
		: Behavior(info, obj),
		factory(factory) {
	};

protected:
	Factory* factory;

	bool doStep(float stepSec) override {
		__super::doStep(stepSec);

		auto cmd = factory->createCommand(((CustomFactory*)factory)->CUSTOM_COMMAND, object, object);
		return cmd->tryToExecute();
	};
};

