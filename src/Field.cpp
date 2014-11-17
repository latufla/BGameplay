#include "stdafx.h"
#include "Field.h"
#include <algorithm>

using std::shared_ptr;
using std::weak_ptr;
using std::make_shared;
using std::remove_if;

Field::Field(uint32_t initialObjectId, Factory* factory) 
	: initialObjectId(initialObjectId)
	, nextObjectId(initialObjectId + 1)
	, factory(factory) {

}

Field::~Field() {
	for (auto i : objects) {
		i->setRemove(true);
	}
	doRemoveStep();
}


weak_ptr<Object> Field::addObject(std::weak_ptr<ObjectInfo> info) {
	auto sInfo = info.lock();
	if (!sInfo)
		throw std::exception("Field::addObject can`t add object");

	shared_ptr<Object> obj = make_shared<Object>(nextObjectId, sInfo);
	objects.push_back(obj);
	
	for (auto i : sInfo->behaviors) {
		auto b = factory->create(i, obj);

		auto it = find_if(begin(behaviors), end(behaviors), [&b](shared_ptr<Behavior> b2){
			return b2->getPriority() < b->getPriority();
		});
		behaviors.insert(it, b);

		obj->addBehavior(b);
	}

	nextObjectId++;
	return weak_ptr<Object>(obj);
}

bool Field::removeObject(std::weak_ptr<Object> obj, bool onNextStep) {
	auto sObj = obj.lock();
	if (!sObj)
		return false;

	sObj->setRemove(true);
	if (!onNextStep)
		return doRemoveStep(); // not efficient, but single entry point 

	return true;
}


bool Field::startBehaviors() {
	bool res = true;
	for (auto i : behaviors) {
		bool sc = i->start();
		res = res && sc;
	}
	return res;
}

bool Field::startBehaviors(std::weak_ptr<Object> obj) {
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

bool Field::stopBehaviors(std::weak_ptr<Object> obj) {
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

bool Field::pauseBehaviors(std::weak_ptr<Object> obj) {
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

bool Field::resumeBehaviors(std::weak_ptr<Object> obj) {
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
	auto lastObject = remove_if(begin(objects), end(objects), [this](shared_ptr<Object> obj) -> bool{
		if (!obj->getRemove())
			return false;

		auto behaviorsToRemove = obj->getBehaviors();
		for (auto b : behaviorsToRemove) {
			auto sb = b.lock();
			if (!sb)
				continue;

			auto lastBehavior = remove_if(begin(behaviors), end(behaviors), [sb](shared_ptr<Behavior> sb2) -> bool{
				return sb == sb2;
			});
			behaviors.erase(lastBehavior, cend(behaviors));
		}
		return true;
	});
	
	objects.erase(lastObject, cend(objects));
	return true;
}

