#include "stdafx.h"
#include "Field.h"
#include <algorithm>

using std::shared_ptr;
using std::weak_ptr;
using std::make_shared;
using std::remove_if;

Field::Field() {
}

Field::~Field() {
}


weak_ptr<ObjectBase> Field::addObject(uint32_t id, const ObjectInfo* info) {
	shared_ptr<ObjectBase> obj = make_shared<ObjectBase>(id, info->name);
	objects.push_back(obj);
	return weak_ptr<ObjectBase>(obj);
}

bool Field::removeObject(std::weak_ptr<ObjectBase> obj) {
	if (auto sObj = obj.lock()) {
		sObj->setRemove(true);
		return true;
	}
	return false;
}

bool Field::startBehaviors() {
	bool res = true;
	for (auto i : objects) {
		bool sc = i->startBehaviors();
		res = res && sc;
	}
	return res;
}

bool Field::stopBehaviors() {
	bool res = true;
	for (auto i : objects) {
		bool sc = i->stopBehaviors();
		res = res && sc;
	}
	return res;
}

bool Field::doStep(float) {
	bool res = true;
	// do behaviors
	//
	doRemoveStep();
	return res;
}

bool Field::doRemoveStep() {
	objects.erase(remove_if(begin(objects), end(objects), [](shared_ptr<ObjectBase> obj) -> bool{
		return obj->getRemove();
	}), objects.end());
	return true;
}

