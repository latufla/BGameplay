#pragma once
#include "Info.h"
#include "BehaviorInfo.h"
#include <vector>
#include <memory>

class ObjectInfo : public Info {
public:
	ObjectInfo() = default;
	~ObjectInfo() = default;

	std::vector<std::shared_ptr<BehaviorInfo>> behaviors;
};

