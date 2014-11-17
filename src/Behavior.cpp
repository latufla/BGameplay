#include "stdafx.h"
#include "Behavior.h"

using std::string;
using std::to_string;

Behavior::Behavior(std::weak_ptr<BehaviorInfo> info, std::weak_ptr<Object> object, std::weak_ptr<Factory> factory)
	: object(object), factory(factory) {

	if (auto sInfo = info.lock()) {
		name = sInfo->name;
		priority = sInfo->priority;
	}
}
	

bool Behavior::start() {
	enabled = true;
	lifeTime = 0;

	return true;
}

bool Behavior::stop() {
	enabled = false;
	return true;
}

bool Behavior::pause() {
	enabled = false;
	return true;
}

bool Behavior::resume() {
	enabled = true;
	return true;
}

bool Behavior::tryDoStep(float stepSec) {
	return canDoStep() ? doStep(stepSec) : false;
}

bool Behavior::canDoStep() {
	return enabled;
}

bool Behavior::doStep(float stepSec) {
	lifeTime += stepSec;
	return true;
}

