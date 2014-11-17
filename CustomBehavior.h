#pragma once
#include "src\Behavior.h"
#include "CustomCommand.h"

class CustomBehavior : public Behavior{
public:
	CustomBehavior(std::weak_ptr<BehaviorInfo> info, std::weak_ptr<Object> obj) 
		: Behavior(info, obj) {
	};

protected:
	bool doStep(float stepSec) override {
		__super::doStep(stepSec);
		
		CustomCommand cmd(object, object);
		return cmd.tryToExecute();
	};
};

