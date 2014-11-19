#include "stdafx.h"
#include "Factory.h"


std::shared_ptr<FieldInfo> Factory::createFieldInfo() {
	return fieldInfoCreator();
}

std::shared_ptr<Field> Factory::createField() {
	return fieldCreator(this);
}

std::shared_ptr<ObjectInfo> Factory::createObjectInfo() {
	return objectInfoCreator();
}

std::shared_ptr<Object> Factory::createObject(uint32_t id, std::weak_ptr<ObjectInfo> info) {
	return objectCreator(id, info);
}

std::shared_ptr<BehaviorInfo> Factory::createBehaviorInfo(std::string name) {
	auto res = nameToBehaviorInfoCreator.at(name)();
	res->name = name;
	return res;
}

std::shared_ptr<Behavior> Factory::createBehavior(std::shared_ptr<BehaviorInfo> info, std::weak_ptr<Object> obj) {
	return nameToBehaviorCreator.at(info->name)(info, obj, this);
}

std::shared_ptr<Command> Factory::createCommand(std::string name, std::weak_ptr<Object> caller, std::weak_ptr<Object> target) {
	return nameToCommandCreator.at(name)(name, caller, target);
}

void Factory::parseInfos(std::ifstream& level, std::ifstream& objects) {
	infos = std::make_shared<Infos>(this);
}
