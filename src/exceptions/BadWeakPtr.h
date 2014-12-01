#pragma once
#include <memory>

namespace bg {
	class BadWeakPtr : public std::bad_weak_ptr {
	public:
		BadWeakPtr(std::string func, uint32_t line);
		~BadWeakPtr() = default;

		std::string msg() const;

	private:
		std::string func;
		uint32_t line;

	};
}

