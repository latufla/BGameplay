#pragma once
#include <vector>
#include <memory>
#include "Info.h"

class FieldInfo : public Info{
public:
	FieldInfo() = default;
	~FieldInfo() = default;

	struct Item {
		uint32_t id;
		std::string name;
	};

	std::vector<std::shared_ptr<Item>> items;
};

