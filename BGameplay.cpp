// BGameplay.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "src\ObjectBase.h"
#include "src\BehaviorBase.h"
#include "src\Field.h"


int _tmain(int argc, _TCHAR* argv[])
{
	Field field(0);
	
	ObjectInfo oInfo;
	oInfo.name = "first";
	std::shared_ptr<BehaviorInfo> bInfo = std::make_shared<BehaviorInfo>();
	bInfo->name = "punch";
	oInfo.behaviors.push_back(bInfo);

	ObjectInfo oInfo2;
	oInfo2.name = "second";
	std::shared_ptr<BehaviorInfo> bInfo2 = std::make_shared<BehaviorInfo>();
	bInfo2->name = "heal";
	oInfo2.behaviors.push_back(bInfo2);

	auto obj = field.addObject(oInfo);
	auto obj2 = field.addObject(oInfo2);

	field.startBehaviors();
	field.removeObject(obj2);
	field.doStep(1.0f);
	field.doStep(1.0f);

	return 0;
}

