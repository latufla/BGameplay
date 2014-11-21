#pragma once
#include "src\Behavior.h"

class HealBehavior : public Behavior{
public:
	HealBehavior(std::weak_ptr<BehaviorInfo> info, std::weak_ptr<Object> obj, Field* field, Factory* factory)
		: Behavior(info, obj, field, factory) {
	};
protected:
	bool doStep(float stepSec) override {
		__super::doStep(stepSec);
		
		CustomFactory* cFactory = (CustomFactory*)factory;

		auto commander = object.lock();
		if(!commander)
			return false;

		auto command = cFactory->HEAL_COMMAND;
		auto target = field->getObjectsBy(command, commander->getName()); // typically its AI or User choice, just a cap here
		if(!target.size())
			return false;

		auto cmd = factory->createCommand(command, object, target.at(0));
		return cmd->tryToExecute();
	};

};

