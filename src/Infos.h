#pragma once
#include <memory>
#include <unordered_map>
#include <fstream>
#include <vector>
#include "FieldInfo.h"
#include "ObjectInfo.h"
#include "yaml-cpp/yaml.h"

namespace bg {

	class Factory;

	class Infos {
	public:
		Infos(Factory* factory, std::ifstream& level, std::ifstream& objects);
		~Infos() = default;

		std::weak_ptr<FieldInfo> getFieldInfo() { return fieldInfo; }
		std::weak_ptr<ObjectInfo> getObjectInfoBy(std::string name);

	protected:
		std::shared_ptr<BehaviorInfo> parseBehaviorInfo(Factory*, const YAML::Node&);
		std::vector<std::string> parseApplicableCommandInfo(const YAML::Node&);
		void updateInfoWithPrimitives(const YAML::Node&, Info*);

		template<typename T>
		bool is(const YAML::Node&);

		template<typename T>
		bool is(const YAML::Node&, std::string name);

		template<typename T>
		T get(const YAML::Node&);

		std::shared_ptr<FieldInfo> fieldInfo;
		std::unordered_map<std::string, std::shared_ptr<ObjectInfo>> nameToObjectInfo;
	};


	template<typename T>
	bool Infos::is(const YAML::Node& n) {
		try {
			T val;
			n >> val;
			return true;
		} catch(const YAML::InvalidScalar& e) { e; }

		return false;
	}

	template<typename T>
	bool Infos::is(const YAML::Node& n, std::string name) {
		const YAML::Node* vNode = n.FindValue(name);
		if(vNode == nullptr)
			return false;

		try {
			T val;
			*vNode >> val;
			return true;
		} catch(const YAML::InvalidScalar& e) { e; }

		return false;
	}

	template<typename T>
	T Infos::get(const YAML::Node& n) {
		T val;
		n >> val;
		return val;
	}
}