#include "stdafx.h"
#include "Infos.h"
#include "Factory.h"

Infos::Infos(Factory* factory) {
	// TODO: fix hard code	
	fieldInfo =  factory->createFieldInfo();

	auto item = std::make_shared<FieldInfo::Item>();
	item->id = 0;
	item->name = "damager";
	fieldInfo->items.push_back(item);

	item = std::make_shared<FieldInfo::Item>();
	item->id = 1;
	item->name = "healer";
	fieldInfo->items.push_back(item);


	std::shared_ptr<ObjectInfo> damagerInfo = factory->createObjectInfo();
	damagerInfo->name = "damager";

	std::shared_ptr<BehaviorInfo> hit = factory->createBehaviorInfo("HitBehavior");
	hit->priority = 3;
	damagerInfo->behaviors.push_back(hit);
	
	nameToObjectInfo.emplace("damager", damagerInfo);


	std::shared_ptr<ObjectInfo> healerInfo = factory->createObjectInfo();
	healerInfo->name = "healer";

	std::shared_ptr<BehaviorInfo> heal = factory->createBehaviorInfo("HealBehavior");
	heal->priority = 1;
	healerInfo->behaviors.push_back(heal);

	std::vector<std::string> cmds{ "healer" };
	healerInfo->applicableCommands.emplace("CustomCommand", cmds);

	nameToObjectInfo.emplace("healer", healerInfo);	
}
