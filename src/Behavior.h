#pragma once
#include <memory>
#include "Object.h"
#include "BehaviorInfo.h"

class Factory;

class Behavior {
public:
	Behavior() = delete;
	Behavior(std::weak_ptr<BehaviorInfo>, std::weak_ptr<Object>, std::weak_ptr<Factory>);

	virtual ~Behavior() {};

	virtual bool start();
	virtual bool stop();

	virtual bool pause();
	virtual bool resume();

	bool tryDoStep(float); // sec

	std::string getName() const { return name; }

	std::weak_ptr<Object> getObject() const { return object; }
	uint32_t getPriority() const { return priority; }
	bool getEnabled() const { return enabled; }

protected:
	virtual bool doStep(float);
	virtual bool canDoStep();

	std::string name;
	uint32_t priority = 0;
	std::weak_ptr<Object> object;
	
	float lifeTime = 0.0f;
	bool enabled = false;

	std::weak_ptr < Factory > factory;
};

