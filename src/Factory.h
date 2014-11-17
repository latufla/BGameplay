#pragma once
#include "Info.h"
#include <memory>
#include "BehaviorBase.h"
#include "ObjectBase.h"
#include <unordered_map>

template<class T, class P>
std::shared_ptr<P> createInstance() {
	return std::make_shared<T>();
}

template<class T, class P>
std::shared_ptr<P> createInstance(std::shared_ptr<BehaviorInfo> info, std::weak_ptr<ObjectBase> obj) {
	return std::make_shared<T>(info, obj);
}

class Factory {
public:
	Factory() = default;
	~Factory() = default;

	
	template<class T, class P>
	void registerInfo(std::string name) {
		nameToInfo[name] = &createInstance<T, P>;
	}
	
	std::shared_ptr<BehaviorInfo> create(std::string name) {
		auto res = nameToInfo.at(name)();
		res->name = name;
		return res;
	}


	template<class T, class P>
	void registerBehavior(std::string name) {
		nameToInstance.emplace(name, &createInstance<T, P>);
	}
	
	std::shared_ptr<BehaviorBase> create(std::shared_ptr<BehaviorInfo> info, std::weak_ptr<ObjectBase> obj) {
		return nameToInstance.at(info->name)(info, obj);
	}

private:
	std::unordered_map <
		std::string, 
		std::shared_ptr<BehaviorInfo>(*)()> nameToInfo;

	std::unordered_map<
		std::string, 
		std::shared_ptr<BehaviorBase>(*)(std::shared_ptr<BehaviorInfo>, std::weak_ptr<ObjectBase>)
	> nameToInstance;
};

