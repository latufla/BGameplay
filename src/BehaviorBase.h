#pragma once
#include <memory>
#include "ObjectBase.h"

enum BehaviorType {};

class BehaviorBase {
public:
	BehaviorBase(std::string name, std::weak_ptr<ObjectBase>);

	virtual ~BehaviorBase();

	virtual bool start();
	virtual bool stop();

	bool tryDoStep(float); // mSec

private:
	std::string name;
	std::weak_ptr<ObjectBase> object;

	bool enabled = false;	
};

