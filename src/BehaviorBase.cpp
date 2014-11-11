#include "stdafx.h"
#include "BehaviorBase.h"


BehaviorBase::BehaviorBase(std::weak_ptr<ObjectBase> object) 
	: object(object) {
	
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
