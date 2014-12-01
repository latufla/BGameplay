#pragma once
#include <vector>
#include <memory>
#include <unordered_map>
#include "Info.h"
#include "BehaviorInfo.h"

namespace bg {
	class ObjectInfo : public Info {
	public:
		ObjectInfo() = default;
		~ObjectInfo() = default;

		bool canApplyCommand(std::string command, std::string commander);

		std::vector<std::shared_ptr<BehaviorInfo>> behaviors;
		std::unordered_map<std::string, std::vector<std::string>> applicableCommands;
	};
}

