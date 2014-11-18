#pragma once
#include <memory>
#include "FieldInfo.h"
#include "ObjectInfo.h"
#include <unordered_map>

class Factory;

class Infos {
public:
	Infos(Factory*);
	~Infos() = default;

	std::weak_ptr<FieldInfo> getFieldInfo() { return fieldInfo; }
	std::weak_ptr<ObjectInfo> getObjectInfoBy(std::string name){ return nameToObjectInfo.at(name);}
	
protected:
	std::shared_ptr<FieldInfo> fieldInfo;
	std::unordered_map<std::string, std::shared_ptr<ObjectInfo>> nameToObjectInfo;
};

