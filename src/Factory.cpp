#include "SharedHeaders.h"
#include "Factory.h"
#include "exceptions\Exception.h"

using std::string;
using std::ifstream;
using std::shared_ptr;
using std::weak_ptr;
using std::unordered_map;
using std::make_shared;

namespace bg {
	shared_ptr<FieldInfo> Factory::createFieldInfo() {
		if(!fieldInfoCreator)
			throw FactoryCreateException(EXCEPTION_INFO, "FieldInfo is unregistered");

		return fieldInfoCreator();
	}

	shared_ptr<Field> Factory::createField() {
		if(!fieldCreator)
			throw FactoryCreateException(EXCEPTION_INFO, "Field is unregistered");
		
		return fieldCreator(this);
	}

	shared_ptr<ObjectInfo> Factory::createObjectInfo() {
		if(!objectInfoCreator)
			throw FactoryCreateException(EXCEPTION_INFO, "ObjectInfo is unregistered");

		return objectInfoCreator();
	}

	shared_ptr<Object> Factory::createObject(uint32_t id, weak_ptr<ObjectInfo> info) {
		if(!objectCreator)
			throw FactoryCreateException(EXCEPTION_INFO, "Object is unregistered");

		return objectCreator(id, info);
	}

	shared_ptr<BehaviorInfo> Factory::createBehaviorInfo(string name) {
		shared_ptr<BehaviorInfo> res;
		try { 
			auto creator = nameToBehaviorInfoCreator.at(name);
			res = creator();
		} catch(...) { // TODO: catch concrete exceptions
			throw FactoryCreateException(EXCEPTION_INFO, "" + name + "Info is unregistered");
		}
		
		res->name = name;
		return res;
	}

	shared_ptr<Behavior> Factory::createBehavior(shared_ptr<BehaviorInfo> info, weak_ptr<Object> obj, Field* field) {
		shared_ptr<Behavior> res;
		try {
			auto creator = nameToBehaviorCreator.at(info->name);
			res = creator(info, obj, field, this);
		} catch(...) {
			throw FactoryCreateException(EXCEPTION_INFO, "" + info->name + " is unregistered");
		}
		return res;
	}

	shared_ptr<Command> Factory::createCommand(string name, weak_ptr<Object> caller, weak_ptr<Object> target) {
		shared_ptr<Command> res;
		try {
			auto creator = nameToCommandCreator.at(name);
			res = creator(name, caller, target);
		} catch(...) {
			throw FactoryCreateException(EXCEPTION_INFO, "" + name + " is unregistered");
		}
		
		return res;
	}


	void Factory::parseInfos(ifstream& level, ifstream& objects) {
		infos = make_shared<Infos>(this, level, objects);
	}
}