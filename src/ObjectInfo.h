#pragma once
#include "Info.h"
#include "BehaviorInfo.h"
#include <vector>
#include <memory>
#include <unordered_map>

class ObjectInfo : public Info {
public:
	ObjectInfo() = default;
	~ObjectInfo() = default;

	bool canApplyCommand(std::string, std::string);

	std::vector<std::shared_ptr<BehaviorInfo>> behaviors;
	std::unordered_map<std::string, std::vector<std::string>> applicableCommands;
};

