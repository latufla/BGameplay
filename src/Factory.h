#pragma once
#include "Info.h"
#include <memory>
#include "BehaviorBase.h"
#include "ObjectBase.h"
#include <unordered_map>
#include "CommandBase.h"

template<class T, class P>
std::shared_ptr<P> createInstance() {
	return std::make_shared<T>();
}

template<class T, class P>
std::shared_ptr<P> createInstance(std::weak_ptr<ObjectBase> caller, std::weak_ptr<ObjectBase> target) {
	return std::make_shared<T>(caller, target);
}

template<class T, class P>
std::shared_ptr<P> createInstance(std::shared_ptr<BehaviorInfo> info, std::weak_ptr<ObjectBase> carrier) {
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
	
	std::shared_ptr<BehaviorBase> create(std::shared_ptr<BehaviorInfo> info, std::weak_ptr<ObjectBase> obj) {
		return nameToBehaviorInstance.at(info->name)(info, obj);
	}


	template<class T, class P>
	void registerCommand(std::string name) {
		nameToCommandInstance[name] = &createInstance < T, P > ;
	}

	std::shared_ptr<CommandBase> create(std::string name, std::weak_ptr<ObjectBase> caller, std::weak_ptr<ObjectBase> target) {
		return nameToCommandInstance.at(name)(caller, target);
	}


private:
	
	std::unordered_map <
		std::string, 
		std::shared_ptr<BehaviorInfo>(*)()> nameToBehaviorInfo;

	std::unordered_map<
		std::string, 
		std::shared_ptr<BehaviorBase>(*)(std::shared_ptr<BehaviorInfo>, std::weak_ptr<ObjectBase>)
	> nameToBehaviorInstance;


	std::unordered_map <
		std::string,
		std::shared_ptr<CommandBase>(*)(std::weak_ptr<ObjectBase>, std::weak_ptr<ObjectBase>)
	> nameToCommandInstance;
};

