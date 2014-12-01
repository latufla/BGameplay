#include "../SharedHeaders.h"
#include "BadWeakPtr.h"

using std::string;
using std::to_string;

namespace bg {
	BadWeakPtr::BadWeakPtr(string func, uint32_t line) : func(func), line(line) {
	}

	string BadWeakPtr::msg() const {
		std::string res = func + " (" + to_string(line) + "): " + __super::what();
		return res.c_str();
	}
}
