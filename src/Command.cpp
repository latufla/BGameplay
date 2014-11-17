#include "stdafx.h"
#include "Command.h"


Command::Command(std::weak_ptr<Object> caller, std::weak_ptr<Object> target) 
	: caller(caller), target(target){
}

bool Command::tryToExecute() {
	if (canExecute()) {
		execute();
		return true;
	}
	return false;
}

bool Command::canExecute() {
// 	ObjectInfo* info = Infos::getInstance().getObjectInfoBy(target->getName());
// 	ObjectBase* commander = caller->getController()->getObject();
// 	return info->canApplyCommand(getType(), commander->getName());
	return true;
}
