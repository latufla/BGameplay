#include "stdafx.h"
#include "BehaviorBase.h"


BehaviorBase::BehaviorBase(std::string name, std::weak_ptr<ObjectBase> object) 
	: name(name), object(object) {
	
}


BehaviorBase::~BehaviorBase() {
	stop();
}

bool BehaviorBase::start() {
	enabled = true;
	return true;
}

bool BehaviorBase::stop() {
	enabled = false;
	return true;
}

bool BehaviorBase::tryDoStep(float stepMSec) {
	return true;
}
