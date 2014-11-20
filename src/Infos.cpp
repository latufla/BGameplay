#include "SharedHeaders.h"
#include "Infos.h"
#include "Factory.h"

using std::unordered_map;
using std::vector;
using std::shared_ptr;
using std::string;

using YAML::Parser;
using YAML::Node;

Infos::Infos(Factory* factory, std::ifstream& level, std::ifstream& objects) {
	Parser parser;
	Node doc;
	parser.Load(level);
	if(!parser.GetNextDocument(doc))
		throw std::exception("Factory::parseInfos can`t parse level");

	fieldInfo = factory->createFieldInfo();
	for(auto it = doc.begin(); it != doc.end(); ++it) {
		auto item = std::make_shared<FieldInfo::FieldItemInfo>();
		updateInfoWithPrimitives(*it, item.get());
		fieldInfo->items.push_back(item);
	}


	parser.Load(objects);
	if(!parser.GetNextDocument(doc))
		throw std::exception("Factory::parseInfos can`t parse objects");

	for(auto i = doc.begin(); i != doc.end(); ++i) {
		shared_ptr<ObjectInfo> info = factory->createObjectInfo();
		i.first() >> info->name;

		const Node& item = i.second();
		updateInfoWithPrimitives(item, info.get());
		for(auto j = item.begin(); j != item.end(); ++j) {
			string nName = get<string>(j.first());
			const Node& val = j.second();
			if(nName == "behaviors") {
				for(auto s = val.begin(); s != val.end(); ++s) {
					auto b = parseBehaviorInfo(factory, *s);
					info->behaviors.push_back(b);
				}
			} else if(nName == "applicableCommands") {
				for(auto s = val.begin(); s != val.end(); ++s) {
					auto b = parseApplicableCommandInfo(*s);
					string bName = get<string>((*s)["name"]);
					info->applicableCommands.emplace(bName, b);
				}
			}
		}
		nameToObjectInfo.emplace(info->name, info);
	}
}

std::shared_ptr<BehaviorInfo> Infos::parseBehaviorInfo(Factory* factory, const Node& b) {
	auto info = factory->createBehaviorInfo(get<string>(b["name"]));
	updateInfoWithPrimitives(b, info.get());
	return info;
}

vector<string> Infos::parseApplicableCommandInfo(const Node& b) {
	vector<string> res;
	const Node& commanders = b["commanders"];
	for(auto i = commanders.begin(); i != commanders.end(); ++i) {
		res.push_back(get<string>(*i));
	}
	return res;
}

void Infos::updateInfoWithPrimitives(const YAML::Node& b, Info* outInfo) {
	for(auto it = b.begin(); it != b.end(); ++it) {
		string prop;
		it.first() >> prop;

		const Node& val = it.second();
		if(is<int32_t>(val))
			outInfo->update(prop, get<int32_t>(val));
		else if(is<float>(val))
			outInfo->update(prop, get<float>(val));
		else if(is<string>(val))
			outInfo->update(prop, get<string>(val));
	}
}

std::weak_ptr<ObjectInfo> Infos::getObjectInfoBy(string name) {
	return nameToObjectInfo.at(name);
}
