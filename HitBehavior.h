#pragma once
#include "src\Behavior.h"
#include "HitCommand.h"

class HitBehavior : public Behavior{
public:
	HitBehavior(std::weak_ptr<BehaviorInfo> info, std::weak_ptr<Object> obj, Field* field, Factory* factory)
		: Behavior(info, obj, field, factory) {
		if(auto sInfo = info.lock()) {
			HitBehaviorInfo* cInfo = (HitBehaviorInfo*)sInfo.get();
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

		auto command = cFactory->HIT_COMMAND;
		auto targets = field->getObjectsBy(command, commander->getName()); // typically its AI or User choice, just a cap here
		if(!targets.size())
			return false;

		auto cmd = factory->createCommand(command, object, targets.at(0));
		
		HitCommand* hit = (HitCommand*)cmd.get();
		hit->setPower(power);
		
		return cmd->tryToExecute();
	};
};

