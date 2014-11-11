#pragma once
#include <memory>
#include "ObjectBase.h"

enum BehaviorType {};

class BehaviorBase {
public:
	BehaviorBase(std::weak_ptr<ObjectBase>);

	virtual ~BehaviorBase();

	virtual bool start();
	virtual bool stop();

private:
	std::weak_ptr<ObjectBase> object;
	bool enabled = false;	
};

