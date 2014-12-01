#include "SharedHeaders.h"
#include "ObjectInfo.h"

using std::string;

namespace bg {
	bool ObjectInfo::canApplyCommand(string command, string commander) {
		auto it = applicableCommands.find(command);
		if(it == cend(applicableCommands))
			return false;

		auto commanders = it->second;
		auto cIt = find(cbegin(commanders), cend(commanders), commander);
		return cIt != cend(commanders);
	}
}
