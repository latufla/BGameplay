#pragma once
#include "src\Command.h"

class HealCommand : public Command{
public:
	HealCommand(std::string name, std::weak_ptr<Object> caller, std::weak_ptr<Object> target)
		: Command(name, caller, target) {
	};

	void setPower(uint32_t val) { power = val; }

protected:
	uint32_t power;

	void execute() override {
		if(auto sTarget = target.lock()) {
			CustomObject* cTarget = (CustomObject*)sTarget.get();
			cTarget->setHp(cTarget->getHp() + power);
		}
	};
};

