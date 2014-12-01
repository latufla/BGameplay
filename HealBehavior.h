#pragma once
#include "src\Behavior.h"
#include "HealCommand.h"

class HealBehavior : public bg::Behavior {
public:
	HealBehavior(std::weak_ptr<bg::BehaviorInfo> info, std::weak_ptr<bg::Object> obj, bg::Field* field, bg::Factory* factory)
		: bg::Behavior(info, obj, field, factory) {
		if(auto sInfo = info.lock()) {
			HealBehaviorInfo* cInfo = (HealBehaviorInfo*)sInfo.get();
			power = cInfo->power;
		}
	};

protected:
	uint32_t power;

	bool doStep(float stepSec) override {
		__super::doStep(stepSec);
		
		CustomFactory* cFactory = (CustomFactory*)factory;

		auto commander = object.lock();
		if(!commander)
			return false;

		auto command = cFactory->HEAL_COMMAND;
		auto targets = field->getObjectsBy(command, commander->getName()); // typically its AI or User choice, just a cap here
		if(!targets.size())
			return false;

		auto cmd = factory->createCommand(command, object, targets.at(0));
		
		HealCommand* heal = (HealCommand*)cmd.get();
		heal->setPower(power);
		
		return cmd->tryToExecute();
	};

};

