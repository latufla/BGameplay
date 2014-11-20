#include "SharedHeaders.h"
#include "Command.h"


Command::Command(std::string name, std::weak_ptr<Object> caller, std::weak_ptr<Object> target) 
	: name(name), caller(caller), target(target) {
}

bool Command::tryToExecute() {
	if (canExecute()) {
		execute();
		return true;
	}
	return false;
}

bool Command::canExecute() {
	auto sTarget = target.lock();
	if (!sTarget)
		return false;
		
	auto info = sTarget->getInfo();
	auto sInfo = info.lock();
	if (!sInfo)
		return false;

	auto sCaller = caller.lock();
	if (!sCaller)
		return false;

	return sInfo->canApplyCommand(getName(), sCaller->getName());
}
