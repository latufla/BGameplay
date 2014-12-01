#include "SharedHeaders.h"
#include "Info.h"

using std::string;

namespace bg {
	void Info::update(string prop, int32_t val) {
		if(prop == "id")
			id = val;
	}

	void Info::update(string prop, float val) {}

	void Info::update(string prop, string val) {
		if(prop == "name")
			name = val;
	}
}
