#pragma once
#include <memory>
#include "Object.h"
#include "ObjectInfo.h"
#include <vector>
#include <unordered_map>
#include "Factory.h"

class Field {
public:
	Field() = default;
	Field(uint32_t, Factory*);
	
	~Field();

	std::weak_ptr<Object> addObject(std::weak_ptr<ObjectInfo>);
	bool removeObject(std::weak_ptr<Object>, bool = false);

	bool startBehaviors();
	bool startBehaviors(std::weak_ptr<Object>);

	bool stopBehaviors();
	bool stopBehaviors(std::weak_ptr<Object>);

	bool pauseBehaviors();
	bool pauseBehaviors(std::weak_ptr<Object>);
	
	bool resumeBehaviors();
	bool resumeBehaviors(std::weak_ptr<Object>);

	bool doStep(float); // sec

private:
	bool doRemoveStep();

	std::vector<std::shared_ptr<Object>> objects;
	std::vector<std::shared_ptr<Behavior>> behaviors;

	uint32_t initialObjectId = 0;
	uint32_t nextObjectId = 0;

	Factory* factory;
};

