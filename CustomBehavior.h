#pragma once
#include "src\Behavior.h"
#include "CustomFactory.h"

class CustomBehavior : public Behavior{
public:
	CustomBehavior(std::weak_ptr<BehaviorInfo> info, std::weak_ptr<Object> obj, std::weak_ptr<Factory> factory) 
		: Behavior(info, obj, factory) {
	};

protected:
	bool doStep(float stepSec) override {
		__super::doStep(stepSec);
		
		auto sFactory = factory.lock();
		if (!sFactory)
			return false;

		CustomFactory* cFactory = (CustomFactory*)sFactory.get();
	
		auto cmd = sFactory->create(cFactory->CUSTOM_COMMAND, object, object);
		return cmd->tryToExecute();
	};
};

