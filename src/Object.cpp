#include "SharedHeaders.h"
#include <algorithm>
#include "Object.h"
#include "Behavior.h"

using std::weak_ptr;

namespace bg {
	Object::Object(uint32_t id, weak_ptr<ObjectInfo> info)
		: id(id), info(info) {

		if(auto sInfo = info.lock())
			name = sInfo->name;
	}

	Object::~Object() {
		stopBehaviors();
	}

	bool Object::addBehavior(weak_ptr<Behavior> b) {
		auto sb = b.lock();
		if(!sb)
			return false;

		auto it = find_if(cbegin(behaviors), cend(behaviors), [sb](weak_ptr<Behavior> b2) {
			if(auto sb2 = b2.lock())
				return sb == sb2;

			return false;
		});
		if(it != cend(behaviors))
			return false;

		behaviors.push_back(b);
		return true;
	}

	bool Object::removeBehavior(weak_ptr<Behavior> b) {
		auto sb = b.lock();
		if(!sb)
			return false;

		auto it = find_if(cbegin(behaviors), cend(behaviors), [sb](weak_ptr<Behavior> b2) {
			if(auto sb2 = b2.lock())
				return sb == sb2;

			return false;
		});
		if(it == cend(behaviors))
			return false;

		sb->stop();
		behaviors.erase(it);
		return true;
	}

	bool Object::startBehaviors() {
		for(auto b : behaviors) {
			if(auto sb = b.lock())
				sb->start();
		}
		return true;
	}

	bool Object::stopBehaviors() {
		for(auto b : behaviors) {
			if(auto sb = b.lock())
				sb->stop();
		}
		return true;
	}

	bool Object::resumeBehaviors() {
		for(auto b : behaviors) {
			if(auto sb = b.lock())
				sb->resume();
		}
		return true;
	}

	bool Object::pauseBehaviors() {
		for(auto b : behaviors) {
			if(auto sb = b.lock())
				sb->pause();
		}
		return true;
	}
}