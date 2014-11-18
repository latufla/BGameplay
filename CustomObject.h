#pragma once
#include "src/Object.h"

class CustomObject : public Object{
public:
	CustomObject(uint32_t id, std::weak_ptr<ObjectInfo> info)
		: Object(id, info) {
	}
};

