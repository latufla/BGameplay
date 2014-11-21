#pragma once
#include "src/ObjectInfo.h"

class CustomObjectInfo : public ObjectInfo{
public:
	CustomObjectInfo() 
		: ObjectInfo() {
	}

	void update(std::string prop, int32_t val) {
		__super::update(prop, val);

		if(prop == "hp")
			hp = (val > 0) ? val : 0;
	}

	uint32_t hp;
};

