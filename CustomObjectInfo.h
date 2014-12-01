#pragma once
#include "src/ObjectInfo.h"

class CustomObjectInfo : public bg::ObjectInfo {
public:
	CustomObjectInfo() 
		: bg::ObjectInfo() {
	}

	void update(std::string prop, int32_t val) {
		__super::update(prop, val);

		if(prop == "hp")
			hp = (val > 0) ? val : 0;
	}

	uint32_t hp;
};

