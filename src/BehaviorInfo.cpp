#include "SharedHeaders.h"
#include "BehaviorInfo.h"


void BehaviorInfo::update(std::string prop, int32_t val) {
	__super::update(prop, val);

	if(prop == "priority")
		priority = (val > 0) ? val : 0;
}
