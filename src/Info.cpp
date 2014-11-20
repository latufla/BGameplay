#include "SharedHeaders.h"
#include "Info.h"

using std::string;

void Info::update(string prop, int32_t val) {
	id = (prop == "id") ? val : -1;
}

void Info::update(string prop, float val) {}

void Info::update(string prop, string val) {
	name = (prop == "name") ? val : "illegal name";
}
