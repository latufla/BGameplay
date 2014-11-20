#include "SharedHeaders.h"
#include "Factory.h"

using YAML::Parser;
using YAML::Node;

using std::string;
using std::ifstream;
using std::shared_ptr;
using std::unordered_map;
using std::vector;

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


void Factory::parseInfos(ifstream& level, ifstream& objects) {
	Parser parser;
	Node doc;
	parser.Load(level);
	if (!parser.GetNextDocument(doc))
		throw std::exception("Factory::parseInfos can`t parse level");

	shared_ptr<FieldInfo> fieldInfo = createFieldInfo();
	for (auto it = doc.begin(); it != doc.end(); ++it) {
		auto item = std::make_shared<FieldInfo::FieldItemInfo>();
		updateInfoWithPrimitives(*it, item.get());
		fieldInfo->items.push_back(item);
	}


	parser.Load(objects);
	if (!parser.GetNextDocument(doc))
		throw std::exception("Factory::parseInfos can`t parse objects");

	unordered_map<string, shared_ptr<ObjectInfo>> nameToObjectInfo;
	for (auto i = doc.begin(); i != doc.end(); ++i) {
		shared_ptr<ObjectInfo> info = createObjectInfo();
		i.first() >> info->name;

		const Node& item = i.second();
		updateInfoWithPrimitives(item, info.get());
		for (auto j = item.begin(); j != item.end(); ++j) {
			string nName = get<string>(j.first());
			const Node& val = j.second();
			if (nName == "behaviors") {
				for (auto s = val.begin(); s != val.end(); ++s) {
					auto b = parseBehaviorInfo(*s);
					info->behaviors.push_back(b);
				}
			} else if (nName == "applicableCommands") {
				for (auto s = val.begin(); s != val.end(); ++s) {
					auto b = parseApplicableCommandInfo(*s);
					string bName = get<string>((*s)["name"]);
					info->applicableCommands.emplace(bName, b);
				}
			}
		}
		nameToObjectInfo.emplace(info->name, info);
	}

	infos = std::make_shared<Infos>(fieldInfo, nameToObjectInfo);
}


std::shared_ptr<BehaviorInfo> Factory::parseBehaviorInfo(const Node& b) {
	auto info = createBehaviorInfo(get<string>(b["name"]));
	updateInfoWithPrimitives(b, info.get());
	return info;
}

vector<string> Factory::parseApplicableCommandInfo(const Node& b) {
	vector<string> res;
	const Node& commanders = b["commanders"];
	for (auto i = commanders.begin(); i != commanders.end(); ++i) {
		res.push_back(get<string>(*i));
	}
	return res;
}

void Factory::updateInfoWithPrimitives(const YAML::Node& b, Info* outInfo) {
	for (auto it = b.begin(); it != b.end(); ++it) {
		string prop;
		it.first() >> prop;

		const Node& val = it.second();
		if(is<int32_t>(val))
			outInfo->update(prop, get<int32_t>(val));
		else if (is<float>(val))
			outInfo->update(prop, get<float>(val));
		else if (is<string>(val))
			outInfo->update(prop, get<string>(val));
	}
}
