#include "stdafx.h"
#include "ObjectInfo.h"

bool ObjectInfo::canApplyCommand(std::string command, std::string commander) {
	auto it = applicableCommands.find(command);
	if (it == cend(applicableCommands))
		return false;

	auto commanders = it->second;
	auto cIt = find(cbegin(commanders), cend(commanders), commander);
	return cIt != cend(commanders);
}
