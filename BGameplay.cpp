// BGameplay.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "src\ObjectBase.h"
#include "src\BehaviorBase.h"
#include "src\Field.h"


int _tmain(int argc, _TCHAR* argv[])
{
	Field field;
	
	ObjectInfo info;
	info.name = "first";
	auto obj = field.addObject(1, &info);

	std::shared_ptr<BehaviorBase> behavior = std::make_shared<BehaviorBase>(obj);
	std::weak_ptr<BehaviorBase> wBehavior(behavior);

	if (auto sObj = obj.lock()) {
		sObj->addBehavior(wBehavior);
		behavior->start();
	}
	
	field.removeObject(obj);

	field.doStep(1.0f);

	return 0;
}

