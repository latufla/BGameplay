// BGameplay.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "src\ObjectBase.h"
#include "src\BehaviorBase.h"
#include "src\Field.h"


int _tmain(int argc, _TCHAR* argv[])
{
	Field field(0);
	
	ObjectInfo info;
	info.name = "first";

	std::shared_ptr<BehaviorInfo> behavior = std::make_shared<BehaviorInfo>();
	behavior->name = "stubBehavior";
	info.behaviors.push_back(behavior);

	auto obj = field.addObject(info);

 	field.startBehaviors(obj);	
//  field.pauseBehaviors(obj);
// 	field.resumeBehaviors(obj);
// 	field.stopBehaviors(obj);
// 	field.removeObject(obj);
	field.doStep(1.0f);
	field.doStep(1.0f);

	return 0;
}

