#include "SharedHeaders.h"
#include "Info.h"

void Info::update(std::string prop, int32_t val) {
	id = (prop == "id") ? val : -1;
}

void Info::update(std::string prop, float val) {}

void Info::update(std::string prop, std::string val) {
	name = (prop == "name") ? val : "illegal name";
}
