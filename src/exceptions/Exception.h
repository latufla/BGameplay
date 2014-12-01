#pragma once
#include <memory>
#include "../SharedHeaders.h"

namespace bg {
	class Exception : public std::exception {
	public:
		Exception(std::string func, uint32_t line) : func(func), line(line) {}
		~Exception() = default;

		virtual std::string msg() const {
			return func + " (" + std::to_string(line) + "): " + what();
		};

	protected:
		std::string func;
		uint32_t line;
	};

	class WeakPtrException : public Exception {
	public:
		WeakPtrException(std::string func, uint32_t line) : Exception(func, line) {}
		~WeakPtrException() = default;
		
		const char* what() const override {
			return "WeakPtrException";
		}
	};
	
	class IOException : public Exception {
	public:
		IOException(std::string func, uint32_t line) : Exception(func, line) {}
		~IOException() = default;
	
		const char* what() const override {
			return "IOException";
		}
	};

	class ExternalFormatException : public Exception {
	public:
		ExternalFormatException(std::string func, uint32_t line) : Exception(func, line) {}
		~ExternalFormatException() = default;

		const char* what() const override {
			return "ExternalFormatException";
		}
	};
}

