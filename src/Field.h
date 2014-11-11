#pragma once
#include <memory>
#include "ObjectBase.h"
#include "ObjectInfo.h"
#include <vector>

class Field {
public:
	Field();
	~Field();

	std::weak_ptr<ObjectBase> addObject(uint32_t, const ObjectInfo*);
	bool removeObject(std::weak_ptr<ObjectBase>);

	bool startBehaviors();
	bool stopBehaviors();

	bool doStep(float); // mSec

private:
	bool doRemoveStep();

	std::vector<std::shared_ptr<ObjectBase>> objects;

};

