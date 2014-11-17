#pragma once
#include "src\BehaviorBase.h"
#include "CustomCommand.h"

class CustomBehavior : public BehaviorBase{
public:
	CustomBehavior(std::weak_ptr<BehaviorInfo> info, std::weak_ptr<ObjectBase> obj) 
		: BehaviorBase(info, obj) {
	};

protected:
	bool doStep(float stepSec) override {
		__super::doStep(stepSec);
		
		CustomCommand cmd(object, object);
		return cmd.tryToExecute();
	};
};

