#include "SharedHeaders.h"
#include <algorithm>
#include "Object.h"
#include "Behavior.h"
#include "exceptions\Exception.h"

using std::weak_ptr;

namespace bg {
	Object::Object(uint32_t id, weak_ptr<ObjectInfo> info)
		: id(id), info(info) {

		if(auto sInfo = info.lock())
			name = sInfo->name;
	}

	void Object::addBehavior(weak_ptr<Behavior> b) {
		auto sb = b.lock();
		if(!sb)
			throw WeakPtrException(EXCEPTION_INFO);

		auto it = find_if(cbegin(behaviors), cend(behaviors), [sb](weak_ptr<Behavior> b2) {
			if(auto sb2 = b2.lock())
				return sb == sb2;

			return false;
		});
		if(it == cend(behaviors))
			behaviors.push_back(b);

		pauseBehaviors();
	}

	void Object::removeBehavior(weak_ptr<Behavior> b) {
		auto sb = b.lock();
		if(!sb)
			throw WeakPtrException(EXCEPTION_INFO);

		auto it = find_if(cbegin(behaviors), cend(behaviors), [sb](weak_ptr<Behavior> b2) {
			if(auto sb2 = b2.lock())
				return sb == sb2;

			return false;
		});
		if(it != cend(behaviors)) {
			sb->stop();
			behaviors.erase(it);
		}
	}

	bool Object::startBehaviors() {
		for(auto b : behaviors) {
			auto sb = b.lock();
			if(!sb)
				throw WeakPtrException(EXCEPTION_INFO);

			sb->start();
		}
		return true;
	}

	bool Object::stopBehaviors() {
		for(auto b : behaviors) {
			auto sb = b.lock();
			if(!sb)
				throw WeakPtrException(EXCEPTION_INFO);
			
			sb->stop();
		}
		return true;
	}

	bool Object::resumeBehaviors() {
		for(auto b : behaviors) {
			auto sb = b.lock();
			if(!sb)
				throw WeakPtrException(EXCEPTION_INFO);
			
			sb->resume();
		}
		return true;
	}

	bool Object::pauseBehaviors() {
		for(auto b : behaviors) {
			auto sb = b.lock();
			if(!sb)
				throw WeakPtrException(EXCEPTION_INFO);
		
			sb->pause();
		}
		return true;
	}
}