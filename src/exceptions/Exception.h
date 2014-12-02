#pragma once
#include <memory>
#include "../SharedHeaders.h"

#define EXCEPTION_INFO __FUNCTION__,__LINE__

namespace bg {
	class Exception : public std::exception {
	public:
		Exception(std::string func, uint32_t line, std::string reason) : func(func), line(line), reason(reason) {}
		~Exception() = default;

		virtual std::string msg() const {
			return func + "(" + std::to_string(line) + "): " + what() + " " + reason;
		};

	protected:
		std::string func;
		uint32_t line;
		std::string reason;
	};

	class WeakPtrException : public Exception {
	public:
		WeakPtrException(std::string func, uint32_t line) : Exception(func, line, "") {}
		~WeakPtrException() = default;
		
		const char* what() const override {
			return "WeakPtrException";
		}
	};
	
	class IOException : public Exception {
	public:
		IOException(std::string func, uint32_t line, std::string file) : Exception(func, line, file) {}
		~IOException() = default;
	
		const char* what() const override {
			return "IOException";
		}
	};

	class ExternalFormatException : public Exception {
	public:
		ExternalFormatException(std::string func, uint32_t line, std::string reason) : Exception(func, line, reason) {}
		~ExternalFormatException() = default;

		const char* what() const override {
			return "ExternalFormatException";
		}
	};

	class FactoryCreateException : public Exception {
	public:
		FactoryCreateException(std::string func, uint32_t line, std::string reason) : Exception(func, line, reason) {}
		~FactoryCreateException() = default;

		const char* what() const override {
			return "FactoryCreateException";
		}
	};
}

