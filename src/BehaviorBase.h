#pragma once
#include <memory>
#include "ObjectBase.h"
#include "BehaviorInfo.h"

class BehaviorBase {
public:
	BehaviorBase() = delete;
	BehaviorBase(std::weak_ptr<BehaviorInfo>, std::weak_ptr<ObjectBase>);

	virtual ~BehaviorBase() {};

	virtual bool start();
	virtual bool stop();

	virtual bool pause();
	virtual bool resume();

	bool tryDoStep(float); // sec

	std::string getName() const { return name; }

	std::weak_ptr<ObjectBase> getObject() const { return object; }
	uint32_t getPriority() const { return priority; }
	bool getEnabled() const { return enabled; }

protected:
	virtual bool doStep(float);
	virtual bool canDoStep();

	std::string name;
	uint32_t priority = 0;
	std::weak_ptr<ObjectBase> object;
	
	float lifeTime = 0.0f;
	bool enabled = false;
};

