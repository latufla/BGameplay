#pragma once
#include "Info.h"
#include <memory>
#include "Behavior.h"
#include "Object.h"
#include <unordered_map>
#include "Command.h"
#include "FieldInfo.h"

class Infos;

template<class T, class P>
std::shared_ptr<P> createInstance() {
	return std::make_shared<T>();
}

template<class T, class P>
std::shared_ptr<P> createInstance(std::weak_ptr<Infos> infos, Factory* factory) {
	return std::make_shared<T>(infos, factory);
}

template<class T, class P>
std::shared_ptr<P> createInstance(uint32_t id, std::weak_ptr<ObjectInfo> info) {
	return std::make_shared<T>(id, info);
}

template<class T, class P>
std::shared_ptr<P> createInstance(std::string name, std::weak_ptr<Object> caller, std::weak_ptr<Object> target) {
	return std::make_shared<T>(name, caller, target);
}

template<class T, class P>
std::shared_ptr<P> createInstance(std::shared_ptr<BehaviorInfo> info, std::weak_ptr<Object> carrier, Factory* factory) {
	return std::make_shared<T>(info, carrier, factory);
}

class Factory {
public:
	Factory() = default;
	~Factory() = default;

	template<class T, class P>
	void registerFieldInfo() {
		fieldInfoCreator = &createInstance < T, P > ;
	}

	std::shared_ptr<FieldInfo> createFieldInfo() {
		return fieldInfoCreator();
	}

	template<class T, class P>
	void registerField() {
		fieldCreator = &createInstance < T, P > ;
	}

	std::shared_ptr<Field> createField(std::weak_ptr<Infos> infos) {
		return fieldCreator(infos, this);
	}


	template<class T, class P>
	void registerObjectInfo() {
		objectInfoCreator = &createInstance < T, P > ;
	}

	std::shared_ptr<ObjectInfo> createObjectInfo() {
		return objectInfoCreator();
	}

	template<class T, class P>
	void registerObject() {
		objectCreator = &createInstance < T, P > ;
	}

	std::shared_ptr<Object> createObject(uint32_t id, std::weak_ptr<ObjectInfo> info) {
		return objectCreator(id, info);
	}


	template<class T, class P>
	void registerBehaviorInfo(std::string name) {
		nameToBehaviorInfoCreator[name] = &createInstance<T, P>;
	}
	
	std::shared_ptr<BehaviorInfo> createBehaviorInfo(std::string name) {
		auto res = nameToBehaviorInfoCreator.at(name)();
		res->name = name;
		return res;
	}
	
	template<class T, class P>
	void registerBehavior(std::string name) {
		nameToBehaviorCreator[name] = &createInstance<T, P>;
	}
	
	std::shared_ptr<Behavior> createBehavior(std::shared_ptr<BehaviorInfo> info, std::weak_ptr<Object> obj) {
		return nameToBehaviorCreator.at(info->name)(info, obj, this);
	}


	template<class T, class P>
	void registerCommand(std::string name) {
		nameToCommandCreator[name] = &createInstance < T, P > ;
	}

	std::shared_ptr<Command> createCommand(std::string name, std::weak_ptr<Object> caller, std::weak_ptr<Object> target) {
		return nameToCommandCreator.at(name)(name, caller, target);
	}


private:
	std::shared_ptr<FieldInfo>(*fieldInfoCreator)();
	std::shared_ptr<Field>(*fieldCreator)(std::weak_ptr<Infos>, Factory*);

	
	std::shared_ptr<ObjectInfo>(*objectInfoCreator)();
	std::shared_ptr<Object>(*objectCreator)(uint32_t, std::weak_ptr<ObjectInfo>);

	
	std::unordered_map <
		std::string, 
		std::shared_ptr<BehaviorInfo>(*)()> nameToBehaviorInfoCreator;

	std::unordered_map<
		std::string, 
		std::shared_ptr<Behavior>(*)(std::shared_ptr<BehaviorInfo>, std::weak_ptr<Object>, Factory*)
	> nameToBehaviorCreator;


	std::unordered_map <
		std::string,
		std::shared_ptr<Command>(*)(std::string, std::weak_ptr<Object>, std::weak_ptr<Object>)
	> nameToCommandCreator;
};

