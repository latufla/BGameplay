#include "stdafx.h"
#include "Infos.h"

using std::unordered_map;
using std::shared_ptr;
using std::string;

Infos::Infos(std::shared_ptr<FieldInfo> fieldInfo, unordered_map<string, shared_ptr<ObjectInfo>> nameToObjectInfo) {
	this->fieldInfo = fieldInfo;
	this->nameToObjectInfo = nameToObjectInfo;
}
