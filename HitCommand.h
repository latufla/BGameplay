#pragma once
#include "src\Command.h"

class HitCommand : public bg::Command {
public:
	HitCommand(std::string name, std::weak_ptr<bg::Object> caller, std::weak_ptr<bg::Object> target)
		: bg::Command(name, caller, target) {
	};

	void setPower(uint32_t val) { power = val; }

protected:
	uint32_t power;

	void execute() override {
		if(auto sTarget = target.lock()) {
			CustomObject* cTarget = (CustomObject*)sTarget.get();
			cTarget->setHp(cTarget->getHp() - power);
		}
	};
};

