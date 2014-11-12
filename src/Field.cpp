#include "stdafx.h"
#include "Field.h"
#include <algorithm>
#include "BehaviorsFactory.h"

using std::shared_ptr;
using std::weak_ptr;
using std::make_shared;
using std::remove_if;

Field::Field(uint32_t initialObjectId) 
	: initialObjectId(initialObjectId), nextObjectId(initialObjectId + 1){

}

Field::~Field() {
}


weak_ptr<ObjectBase> Field::addObject(ObjectInfo const& info) {
	shared_ptr<ObjectBase> obj = make_shared<ObjectBase>(nextObjectId, info.name);
	objects.push_back(obj);
	
	for (auto i : info.behaviors) {
		auto b = BehaviorsFactory::create(i, obj);
		behaviors.push_back(b);
	
		obj->addBehavior(b);
	}

	nextObjectId++;
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
	for (auto i : behaviors) {
		bool sc = i->start();
		res = res && sc;
	}
	return res;
}

bool Field::startBehaviors(std::weak_ptr<ObjectBase> obj) {
	auto sObj = obj.lock();
	if (!sObj)
		return false;

	return sObj->startBehaviors();
}


bool Field::stopBehaviors() {
	bool res = true;
	for (auto i : behaviors) {
		bool sc = i->stop();
		res = res && sc;
	}
	return res;
}

bool Field::stopBehaviors(std::weak_ptr<ObjectBase> obj) {
	auto sObj = obj.lock();
	if (!sObj)
		return false;

	return sObj->stopBehaviors();
}


bool Field::pauseBehaviors() {
	bool res = true;
	for (auto i : behaviors) {
		bool sc = i->pause();
		res = res && sc;
	}
	return res;
}

bool Field::pauseBehaviors(std::weak_ptr<ObjectBase> obj) {
	auto sObj = obj.lock();
	if (!sObj)
		return false;

	return sObj->pauseBehaviors();
}


bool Field::resumeBehaviors() {
	bool res = true;
	for (auto i : behaviors) {
		bool sc = i->resume();
		res = res && sc;
	}
	return res;
}

bool Field::resumeBehaviors(std::weak_ptr<ObjectBase> obj) {
	auto sObj = obj.lock();
	if (!sObj)
		return false;

	return sObj->resumeBehaviors();
}


bool Field::doStep(float stepMSec) {
	bool res = true;
	for (auto i : behaviors) {
		bool sc = i->tryDoStep(stepMSec);
		res = res && sc;
	}
	doRemoveStep();
	return res;
}

bool Field::doRemoveStep() {
	auto objectsToRemove = remove_if(begin(objects), end(objects), [](shared_ptr<ObjectBase> obj) -> bool{		
		return obj->getRemove();
	});

	for (auto i = objectsToRemove; i != objects.cend(); ++i){
		auto behaviorsToRemove = i->get()->getBehaviors();
		for (auto b : behaviorsToRemove) {
			auto sb = b.lock();
			if (!sb)
				continue;
			
			auto it = remove_if(begin(behaviors), end(behaviors), [sb](shared_ptr<BehaviorBase> sb2) -> bool{
				return sb == sb2;
			});
			
			behaviors.erase(it, behaviors.end());
		}
	}
	objects.erase(objectsToRemove, objects.end());
	
	return true;
}

