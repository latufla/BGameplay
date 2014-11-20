#include "SharedHeaders.h"
#include "Infos.h"

using std::unordered_map;
using std::shared_ptr;
using std::string;

Infos::Infos(std::shared_ptr<FieldInfo> fieldInfo, unordered_map<string, shared_ptr<ObjectInfo>> nameToObjectInfo) 
	: fieldInfo(fieldInfo), nameToObjectInfo(nameToObjectInfo){
}

std::weak_ptr<ObjectInfo> Infos::getObjectInfoBy(string name) {
	return nameToObjectInfo.at(name);
}
