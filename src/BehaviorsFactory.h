#pragma once
#include <memory>
#include "BehaviorBase.h"
#include "BehaviorInfo.h"
#include "ObjectBase.h"

class BehaviorsFactory {
public:
	BehaviorsFactory() = default;
	~BehaviorsFactory() = default;

	static std::shared_ptr<BehaviorBase> create(std::weak_ptr<BehaviorInfo> info, std::weak_ptr<ObjectBase> obj) {
		std::string name;
		if (auto sInfo = info.lock())
			name = sInfo->name;

		std::shared_ptr<BehaviorBase> behavior = std::make_shared<BehaviorBase>(info, obj);
		return behavior;
	};
};

