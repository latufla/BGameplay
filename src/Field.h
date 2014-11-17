#pragma once
#include <memory>
#include "ObjectBase.h"
#include "ObjectInfo.h"
#include <vector>
#include <unordered_map>
#include "Factory.h"

class Field {
public:
	Field() = default;
	Field(uint32_t, Factory const&);
	
	~Field();

	std::weak_ptr<ObjectBase> addObject(std::weak_ptr<ObjectInfo>);
	bool removeObject(std::weak_ptr<ObjectBase>, bool = false);

	bool startBehaviors();
	bool startBehaviors(std::weak_ptr<ObjectBase>);

	bool stopBehaviors();
	bool stopBehaviors(std::weak_ptr<ObjectBase>);

	bool pauseBehaviors();
	bool pauseBehaviors(std::weak_ptr<ObjectBase>);
	
	bool resumeBehaviors();
	bool resumeBehaviors(std::weak_ptr<ObjectBase>);

	bool doStep(float); // sec

private:
	bool doRemoveStep();

	std::vector<std::shared_ptr<ObjectBase>> objects;
	std::vector<std::shared_ptr<BehaviorBase>> behaviors;

	uint32_t initialObjectId = 0;
	uint32_t nextObjectId = 0;

	Factory factory;
};

