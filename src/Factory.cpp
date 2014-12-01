#include "SharedHeaders.h"
#include "Factory.h"

using std::string;
using std::ifstream;
using std::shared_ptr;
using std::weak_ptr;
using std::unordered_map;
using std::make_shared;

namespace bg {
	shared_ptr<FieldInfo> Factory::createFieldInfo() {
		return fieldInfoCreator();
	}

	shared_ptr<Field> Factory::createField() {
		return fieldCreator(this);
	}

	shared_ptr<ObjectInfo> Factory::createObjectInfo() {
		return objectInfoCreator();
	}

	shared_ptr<Object> Factory::createObject(uint32_t id, weak_ptr<ObjectInfo> info) {
		return objectCreator(id, info);
	}

	shared_ptr<BehaviorInfo> Factory::createBehaviorInfo(string name) {
		auto res = nameToBehaviorInfoCreator.at(name)();
		res->name = name;
		return res;
	}

	shared_ptr<Behavior> Factory::createBehavior(shared_ptr<BehaviorInfo> info, weak_ptr<Object> obj, Field* field) {
		return nameToBehaviorCreator.at(info->name)(info, obj, field, this);
	}

	shared_ptr<Command> Factory::createCommand(string name, weak_ptr<Object> caller, weak_ptr<Object> target) {
		return nameToCommandCreator.at(name)(name, caller, target);
	}


	void Factory::parseInfos(ifstream& level, ifstream& objects) {
		infos = make_shared<Infos>(this, level, objects);
	}
}