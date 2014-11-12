#include "stdafx.h"
#include "BehaviorBase.h"

using std::string;
using std::to_string;

BehaviorBase::BehaviorBase(std::weak_ptr<BehaviorInfo> info, std::weak_ptr<ObjectBase> object)
	: object(object) {

	if (auto sInfo = info.lock())
		name = sInfo->name;
}

bool BehaviorBase::start() {
	enabled = true;
	lifeTime = 0;

	return true;
}

bool BehaviorBase::stop() {
	enabled = false;
	return true;
}

bool BehaviorBase::pause() {
	enabled = false;
	return true;
}

bool BehaviorBase::resume() {
	enabled = true;
	return true;
}

bool BehaviorBase::tryDoStep(float stepSec) {
	return canDoStep() ? doStep(stepSec) : false;
}

bool BehaviorBase::canDoStep() {
	return enabled;
}

bool BehaviorBase::doStep(float stepSec) {
	lifeTime += stepSec;
	return true;
}

