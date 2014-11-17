#include "stdafx.h"
#include "CommandBase.h"


CommandBase::CommandBase(std::weak_ptr<ObjectBase> caller, std::weak_ptr<ObjectBase> target) 
	: caller(caller), target(target){
}

bool CommandBase::tryToExecute() {
	if (canExecute()) {
		execute();
		return true;
	}
	return false;
}

bool CommandBase::canExecute() {
// 	ObjectInfo* info = Infos::getInstance().getObjectInfoBy(target->getName());
// 	ObjectBase* commander = caller->getController()->getObject();
// 	return info->canApplyCommand(getType(), commander->getName());
	return true;
}
