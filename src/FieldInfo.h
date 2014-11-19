#pragma once
#include <vector>
#include <memory>
#include "Info.h"

class FieldInfo : public Info{
public:
	FieldInfo() = default;
	~FieldInfo() = default;

	class FieldItemInfo : public Info{
	};

	std::vector<std::shared_ptr<FieldItemInfo>> items;
};

