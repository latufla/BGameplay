#pragma once
#include "Info.h"
#include <memory>
#include "Behavior.h"
#include "Object.h"
#include <unordered_map>
#include "Command.h"

template<class T, class P>
std::shared_ptr<P> createInstance() {
	return std::make_shared<T>();
}

template<class T, class P>
std::shared_ptr<P> createInstance(std::weak_ptr<Object> caller, std::weak_ptr<Object> target) {
	return std::make_shared<T>(caller, target);
}

template<class T, class P>
std::shared_ptr<P> createInstance(std::shared_ptr<BehaviorInfo> info, std::weak_ptr<Object> carrier) {
	return std::make_shared<T>(info, carrier);
}

class Factory {
public:
	Factory() = default;
	~Factory() = default;

	
	template<class T, class P>
	void registerBehaviorInfo(std::string name) {
		nameToBehaviorInfo[name] = &createInstance<T, P>;
	}
	
	std::shared_ptr<BehaviorInfo> create(std::string name) {
		auto res = nameToBehaviorInfo.at(name)();
		res->name = name;
		return res;
	}
	
	template<class T, class P>
	void registerBehavior(std::string name) {
		nameToBehaviorInstance[name] = &createInstance<T, P>;
	}
	
	std::shared_ptr<Behavior> create(std::shared_ptr<BehaviorInfo> info, std::weak_ptr<Object> obj) {
		return nameToBehaviorInstance.at(info->name)(info, obj);
	}


	template<class T, class P>
	void registerCommand(std::string name) {
		nameToCommandInstance[name] = &createInstance < T, P > ;
	}

	std::shared_ptr<Command> create(std::string name, std::weak_ptr<Object> caller, std::weak_ptr<Object> target) {
		return nameToCommandInstance.at(name)(caller, target);
	}


private:
	
	std::unordered_map <
		std::string, 
		std::shared_ptr<BehaviorInfo>(*)()> nameToBehaviorInfo;

	std::unordered_map<
		std::string, 
		std::shared_ptr<Behavior>(*)(std::shared_ptr<BehaviorInfo>, std::weak_ptr<Object>)
	> nameToBehaviorInstance;


	std::unordered_map <
		std::string,
		std::shared_ptr<Command>(*)(std::weak_ptr<Object>, std::weak_ptr<Object>)
	> nameToCommandInstance;
};

