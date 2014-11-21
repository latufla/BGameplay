#pragma once
#include "src\BehaviorInfo.h"

class HitBehaviorInfo : public BehaviorInfo{
public:
	HitBehaviorInfo() : BehaviorInfo() {
	};

	uint32_t power;

	void HitBehaviorInfo::update(std::string prop, int32_t val) {
		__super::update(prop, val);

		if(prop == "power")
			power = (val > 0) ? val : 0;
	}
};

