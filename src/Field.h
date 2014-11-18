#pragma once
#include <memory>
#include "Object.h"
#include "ObjectInfo.h"
#include <vector>
#include <unordered_map>
#include "Factory.h"
#include "Infos.h"

class Field {
public:
	Field(std::weak_ptr<Infos> infos, Factory*);
	
	~Field();

	std::weak_ptr<Object> addObject(uint32_t, std::weak_ptr<ObjectInfo>);
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

	Factory* factory;
};

