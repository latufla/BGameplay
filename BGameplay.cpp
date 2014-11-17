// BGameplay.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "src\Object.h"
#include "src\Behavior.h"
#include "src\Field.h"
#include "src\Factory.h"
#include "CustomBehavior.h"
#include "CustomBehaviorInfo.h"
#include "CustomCommand.h"


int _tmain(int argc, _TCHAR* argv[])
{
	Factory factory;
	
	// register all info and behavior types from cfg
	factory.registerBehaviorInfo< CustomBehaviorInfo, BehaviorInfo >("HitBehavior"); // typically unique classes
	factory.registerBehaviorInfo< CustomBehaviorInfo, BehaviorInfo >("HealBehavior");
	factory.registerBehaviorInfo< CustomBehaviorInfo, BehaviorInfo >("ResurrectBehavior");

	factory.registerBehavior< CustomBehavior, Behavior >("HitBehavior");
	factory.registerBehavior< CustomBehavior, Behavior >("HealBehavior");
	factory.registerBehavior< CustomBehavior, Behavior >("ResurrectBehavior");

	factory.registerCommand<CustomCommand, Command>("CustomCommand");
	// ---
	Field field(0, factory);
	
	std::shared_ptr<ObjectInfo> damagerInfo = std::make_shared<ObjectInfo>();
	damagerInfo->name = "damager";
	
	std::shared_ptr<BehaviorInfo> hit = factory.create("HitBehavior");
	hit->priority = 3;
	damagerInfo->behaviors.push_back(hit);


	std::shared_ptr<ObjectInfo> healerInfo = std::make_shared<ObjectInfo>();
	healerInfo->name = "healer";

	std::shared_ptr<BehaviorInfo> heal = factory.create("HealBehavior");
	heal->priority = 1;
	healerInfo->behaviors.push_back(heal);

	std::shared_ptr<BehaviorInfo> resurrect = factory.create("ResurrectBehavior");
	resurrect->priority = 2;
	healerInfo->behaviors.push_back(resurrect);
	
	auto damager = field.addObject(damagerInfo);
	auto healer = field.addObject(healerInfo);

	field.startBehaviors();
	field.removeObject(healer);
	field.doStep(1.0f);
	field.doStep(1.0f);

	return 0;
}

