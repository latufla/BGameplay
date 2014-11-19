#pragma once
#include <memory>
#include "FieldInfo.h"
#include "ObjectInfo.h"
#include <unordered_map>

class Infos {
public:
	Infos(std::shared_ptr<FieldInfo>, std::unordered_map<std::string, std::shared_ptr<ObjectInfo>>);
	~Infos() = default;

	std::weak_ptr<FieldInfo> getFieldInfo() { return fieldInfo; }
	std::weak_ptr<ObjectInfo> getObjectInfoBy(std::string name){ return nameToObjectInfo.at(name);}
	
protected:
	std::shared_ptr<FieldInfo> fieldInfo;
	std::unordered_map<std::string, std::shared_ptr<ObjectInfo>> nameToObjectInfo;
};

