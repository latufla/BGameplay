#pragma once
#include "src\Behavior.h"
#include "CustomFactory.h"

class CustomBehavior : public Behavior {
public:
	CustomBehavior(std::weak_ptr<BehaviorInfo> info, std::weak_ptr<Object> obj, Field* field, Factory* factory)
		: Behavior(info, obj, field, factory){
	};

protected:
	bool doStep(float stepSec) override {
		__super::doStep(stepSec);

		auto cmd = factory->createCommand(((CustomFactory*)factory)->CUSTOM_COMMAND, object, object);
		return cmd->tryToExecute();
	};
};

