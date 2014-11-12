// BGameplay.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "src\ObjectBase.h"
#include "src\BehaviorBase.h"
#include "src\Field.h"


int _tmain(int argc, _TCHAR* argv[])
{
	Field field(0);
	
	std::shared_ptr<ObjectInfo> damager = std::make_shared<ObjectInfo>();
	damager->name = "damager";
	
	std::shared_ptr<BehaviorInfo> punch = std::make_shared<BehaviorInfo>();
	punch->name = "punch";
	punch->priority = 3;
	damager->behaviors.push_back(punch);


	std::shared_ptr<ObjectInfo> healer = std::make_shared<ObjectInfo>();
	healer->name = "healer";

	std::shared_ptr<BehaviorInfo> heal = std::make_shared<BehaviorInfo>();
	heal->name = "heal";
	heal->priority = 1;
	healer->behaviors.push_back(heal);

	std::shared_ptr<BehaviorInfo> ressurect = std::make_shared<BehaviorInfo>();
	ressurect->name = "resurrect";
	ressurect->priority = 2;
	healer->behaviors.push_back(ressurect);
	
	auto obj = field.addObject(damager);
	auto obj2 = field.addObject(healer);

	field.startBehaviors();
	field.removeObject(obj2);
	field.doStep(1.0f);
	field.doStep(1.0f);

	return 0;
}

