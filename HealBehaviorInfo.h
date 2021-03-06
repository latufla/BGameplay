#pragma once
#include "src\BehaviorInfo.h"

class HealBehaviorInfo : public bg::BehaviorInfo {
public:
	HealBehaviorInfo() : bg::BehaviorInfo() {
	};

	uint32_t power;

	void HealBehaviorInfo::update(std::string prop, int32_t val) {
		__super::update(prop, val);

		if(prop == "power")
			power = (val > 0) ? val : 0;
	}
};

