// BGameplay.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "src\Object.h"
#include "src\Behavior.h"
#include "src\Field.h"
#include "CustomBehavior.h"
#include "CustomBehaviorInfo.h"
#include "CustomCommand.h"
#include "CustomFactory.h"


int _tmain(int argc, _TCHAR* argv[])
{
	CustomFactory factory;

	// register all info and behavior types from cfg 
	factory.registerBehaviorInfo< CustomBehaviorInfo, BehaviorInfo >(factory.HIT_BEHAVIOR); // typically unique classes
	factory.registerBehaviorInfo< CustomBehaviorInfo, BehaviorInfo >(factory.HEAL_BEHAVIOR);

	factory.registerBehavior< CustomBehavior, Behavior >(factory.HIT_BEHAVIOR);
	factory.registerBehavior< CustomBehavior, Behavior >(factory.HEAL_BEHAVIOR);

	factory.registerCommand<CustomCommand, Command>(factory.CUSTOM_COMMAND);
	// ---
	Field field(0, &factory);
	
	std::shared_ptr<ObjectInfo> damagerInfo = std::make_shared<ObjectInfo>();
	damagerInfo->name = "damager";
	
	std::shared_ptr<BehaviorInfo> hit = factory.create(factory.HIT_BEHAVIOR);
	hit->priority = 3;
	damagerInfo->behaviors.push_back(hit);


	std::shared_ptr<ObjectInfo> healerInfo = std::make_shared<ObjectInfo>();
	healerInfo->name = "healer";

	std::shared_ptr<BehaviorInfo> heal = factory.create(factory.HEAL_BEHAVIOR);
	heal->priority = 1;
	healerInfo->behaviors.push_back(heal);

	std::vector<std::string> cmds{"healer"};
	healerInfo->applicableCommands.emplace(factory.CUSTOM_COMMAND, cmds);
	
	auto damager = field.addObject(damagerInfo);
	auto healer = field.addObject(healerInfo);

	field.startBehaviors();
	field.removeObject(damager);
	field.doStep(1.0f);
	field.doStep(1.0f);

	return 0;
}

