#pragma once
#include "Info.h"

class BehaviorInfo : public Info{
public:
	BehaviorInfo() = default;
	~BehaviorInfo() = default;

	uint32_t priority = 0;

	virtual void update(std::string prop, int32_t val) override;
};

