// BGameplay.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "src\ObjectBase.h"
#include "src\BehaviorBase.h"
#include "src\Field.h"
#include "src\Factory.h"
#include "CustomBehavior.h"
#include "CustomBehaviorInfo.h"


int _tmain(int argc, _TCHAR* argv[])
{
	Factory factory;
	
	// register all info and behavior types from cfg
	factory.registerInfo< CustomBehaviorInfo, BehaviorInfo >("punch");
	factory.registerInfo< CustomBehaviorInfo, BehaviorInfo >("heal");
	factory.registerInfo< CustomBehaviorInfo, BehaviorInfo >("resurrect");

	factory.registerBehavior< CustomBehavior, BehaviorBase >("punch");
	factory.registerBehavior< CustomBehavior, BehaviorBase >("heal");
	factory.registerBehavior< CustomBehavior, BehaviorBase >("resurrect");
	// ---
	Field field(0, factory);
	
	std::shared_ptr<ObjectInfo> damagerInfo = std::make_shared<ObjectInfo>();
	damagerInfo->name = "damager";
	
	std::shared_ptr<BehaviorInfo> punch = factory.create("punch");
	punch->priority = 3;
	damagerInfo->behaviors.push_back(punch);


	std::shared_ptr<ObjectInfo> healerInfo = std::make_shared<ObjectInfo>();
	healerInfo->name = "healer";

	std::shared_ptr<BehaviorInfo> heal = factory.create("heal");
	heal->priority = 1;
	healerInfo->behaviors.push_back(heal);

	std::shared_ptr<BehaviorInfo> resurrect = factory.create("resurrect");
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

