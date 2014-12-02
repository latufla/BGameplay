#include "SharedHeaders.h"
#include "Command.h"
#include "exceptions\Exception.h"

using std::string;
using std::weak_ptr;

namespace bg {
	Command::Command(string name, weak_ptr<Object> caller, weak_ptr<Object> target)
		: name(name), caller(caller), target(target) {
	}

	bool Command::tryToExecute() {
		if(canExecute()) {
			execute();
			return true;
		}
		return false;
	}

	bool Command::canExecute() {
		auto sTarget = target.lock();
		if(!sTarget)
			throw WeakPtrException(EXCEPTION_INFO); 
		
		auto info = sTarget->getInfo();
		auto sInfo = info.lock();
		if(!sInfo)
			throw WeakPtrException(EXCEPTION_INFO);

		auto sCaller = caller.lock();
		if(!sCaller)
			throw WeakPtrException(EXCEPTION_INFO);

		return sInfo->canApplyCommand(getName(), sCaller->getName());
	}
}
