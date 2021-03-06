#include "SharedHeaders.h"
#include "Field.h"
#include <algorithm>
#include "exceptions\Exception.h"

using std::vector;
using std::string;
using std::shared_ptr;
using std::weak_ptr;
using std::make_shared;
using std::remove_if;
using std::exception;

namespace bg {
	Field::Field(Factory* factory)
		: factory(factory) {

		auto infos = factory->getInfos();
		if(auto sInfo = infos->getFieldInfo().lock()) {
			for(auto i : sInfo->items) {
				addObject(i);
			}
		}
	}

	Field::~Field() {
		for(auto i : objects) {
			i->setRemove(true);
		}
		doRemoveStep();
	}


	weak_ptr<Object> Field::addObject(weak_ptr<FieldInfo::FieldItemInfo> itemInfo) {
		auto sItemInfo = itemInfo.lock();
		if(!sItemInfo)
			throw WeakPtrException(EXCEPTION_INFO);

		auto infos = factory->getInfos();
		return addObject(sItemInfo->id, infos->getObjectInfoBy(sItemInfo->name));
	}

	weak_ptr<Object> Field::addObject(uint32_t id, weak_ptr<ObjectInfo> info) {
		auto sInfo = info.lock();
		if(!sInfo)
			throw WeakPtrException(EXCEPTION_INFO);

		shared_ptr<Object> obj = factory->createObject(id, sInfo);
		objects.push_back(obj);

		for(auto i : sInfo->behaviors) {
			auto b = factory->createBehavior(i, obj, this);

			auto it = find_if(begin(behaviors), end(behaviors), [&b](shared_ptr<Behavior> b2) {
				return b2->getPriority() < b->getPriority();
			});
			behaviors.insert(it, b);

			obj->addBehavior(b);
		}
		return weak_ptr<Object>(obj);
	}

	void Field::removeObject(weak_ptr<Object> obj, bool onNextStep) {
		auto sObj = obj.lock();
		if(!sObj)
			throw WeakPtrException(EXCEPTION_INFO);

		sObj->setRemove(true);
		if(!onNextStep)
			doRemoveStep(); // not efficient, but single entry point 
	}


	bool Field::startBehaviors() {
		bool res = true;
		for(auto i : behaviors) {
			bool sc = i->start();
			res = res && sc;
		}
		return res;
	}

	bool Field::startBehaviors(weak_ptr<Object> obj) {
		auto sObj = obj.lock();
		if(!sObj)
			throw WeakPtrException(EXCEPTION_INFO);

		return sObj->startBehaviors();
	}


	bool Field::stopBehaviors() {
		bool res = true;
		for(auto i : behaviors) {
			bool sc = i->stop();
			res = res && sc;
		}
		return res;
	}

	bool Field::stopBehaviors(weak_ptr<Object> obj) {
		auto sObj = obj.lock();
		if(!sObj)
			throw WeakPtrException(EXCEPTION_INFO);

		return sObj->stopBehaviors();
	}


	bool Field::pauseBehaviors() {
		bool res = true;
		for(auto i : behaviors) {
			bool sc = i->pause();
			res = res && sc;
		}
		return res;
	}

	bool Field::pauseBehaviors(weak_ptr<Object> obj) {
		auto sObj = obj.lock();
		if(!sObj)
			throw WeakPtrException(EXCEPTION_INFO);

		return sObj->pauseBehaviors();
	}


	bool Field::resumeBehaviors() {
		bool res = true;
		for(auto i : behaviors) {
			bool sc = i->resume();
			res = res && sc;
		}
		return res;
	}

	bool Field::resumeBehaviors(weak_ptr<Object> obj) {
		auto sObj = obj.lock();
		if(!sObj)
			throw WeakPtrException(EXCEPTION_INFO);

		return sObj->resumeBehaviors();
	}


	bool Field::doStep(float stepSec) {
		bool res = true;
		for(auto i : behaviors) {
			bool sc = i->tryDoStep(stepSec);
			res = res && sc;
		}
		doRemoveStep();
		return res;
	}

	void Field::doRemoveStep() {
		auto lastObject = remove_if(begin(objects), end(objects), [this](shared_ptr<Object> obj) -> bool {
			if(!obj->getRemove())
				return false;

			obj->stopBehaviors();
			auto behaviorsToRemove = obj->getBehaviors();
			for(auto b : behaviorsToRemove) {
				auto sb = b.lock();
				if(!sb)
					continue;

				auto lastBehavior = remove_if(begin(behaviors), end(behaviors), [sb](shared_ptr<Behavior> sb2) -> bool {
					return sb == sb2;
				});
				behaviors.erase(lastBehavior, cend(behaviors));
			}
			return true;
		});
		objects.erase(lastObject, cend(objects));
	}

	vector<weak_ptr<Object>> Field::getObjectsBy(string applicableCommand, string commander) {
		vector<weak_ptr<Object>> res;
		for(auto& i : objects) {
			auto info = i->getInfo();
			auto sInfo = info.lock();	
			if(!sInfo)
				throw WeakPtrException(EXCEPTION_INFO);

			if(sInfo->canApplyCommand(applicableCommand, commander))
				res.push_back(i);
		}
		return res;
	}
}
