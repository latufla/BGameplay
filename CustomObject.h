#pragma once
#include "src/Object.h"

class CustomObject : public bg::Object{
public:
	CustomObject(uint32_t id, std::weak_ptr<bg::ObjectInfo> info)
		: bg::Object(id, info) {
		if(auto sInfo = info.lock()) {
			CustomObjectInfo* cInfo = (CustomObjectInfo*)sInfo.get();
			hp = cInfo->hp;
		}
	}
	uint32_t getHp() const { return hp; }
	void setHp(uint32_t val) { hp = val; }

protected:
	uint32_t hp;
};

