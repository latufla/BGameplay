#include "stdafx.h"
#include "ObjectBase.h"
#include "BehaviorBase.h"
#include <algorithm>

ObjectBase::ObjectBase(uint32_t id, std::string name) 
	: id(id), name(name){
	 
}

ObjectBase::~ObjectBase() {
	stopBehaviors();
}

bool ObjectBase::addBehavior(std::weak_ptr<BehaviorBase> b) {
	auto sb = b.lock();
	if (!sb)
		return false;
	
	auto it = find_if(cbegin(behaviors), cend(behaviors), [sb](std::weak_ptr<BehaviorBase> b2){
		if (auto sb2 = b2.lock())
			return sb == sb2;

		return false;
	});
	if (it != cend(behaviors))
		return false;

	behaviors.push_back(b);
	return true;
}

bool ObjectBase::removeBehavior(std::weak_ptr<BehaviorBase> b) {
	auto sb = b.lock();
	if (!sb)
		return false;

	auto it = find_if(cbegin(behaviors), cend(behaviors), [sb](std::weak_ptr<BehaviorBase> b2){
		if (auto sb2 = b2.lock())
			return sb == sb2;

		return false;
	});
	if (it == cend(behaviors))
		return false;
	
	sb->stop();
	behaviors.erase(it);
	return true;
}

bool ObjectBase::startBehaviors() {
	for (auto b : behaviors) {
		if (auto sb = b.lock())
			sb->start();
	}
	return true;
}

bool ObjectBase::stopBehaviors() {
	for (auto b : behaviors) {
		if (auto sb = b.lock())
			sb->stop();
	}
	return true;
}
