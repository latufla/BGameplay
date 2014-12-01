#include "SharedHeaders.h"
#include "Command.h"
#include "exceptions\BadWeakPtr.h"

using std::string;
using std::weak_ptr;
using std::bad_weak_ptr;

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
			throw BadWeakPtr(__FUNCTION__, __LINE__); 
		
		auto info = sTarget->getInfo();
		auto sInfo = info.lock();
		if(!sInfo)
			throw BadWeakPtr(__FUNCTION__, __LINE__);

		auto sCaller = caller.lock();
		if(!sCaller)
			throw BadWeakPtr(__FUNCTION__, __LINE__);

		return sInfo->canApplyCommand(getName(), sCaller->getName());
	}
}
