#pragma once
#include <memory>
#include <unordered_map>
#include <fstream>
#include "Behavior.h"
#include "Object.h"
#include "Command.h"
#include "FieldInfo.h"
#include "Info.h" 
#include "Infos.h"

namespace bg {
	class Factory {
	public:
		Factory() = default;
		~Factory() = default;

		template<class T, class P>
		void registerFieldInfo();
		std::shared_ptr<FieldInfo> createFieldInfo();

		template<class T, class P>
		void registerField();
		std::shared_ptr<Field> createField();


		template<class T, class P>
		void registerObjectInfo();
		std::shared_ptr<ObjectInfo> createObjectInfo();

		template<class T, class P>
		void registerObject();
		std::shared_ptr<Object> createObject(uint32_t id, std::weak_ptr<ObjectInfo>);


		template<class T, class P>
		void registerBehaviorInfo(std::string name);
		std::shared_ptr<BehaviorInfo> createBehaviorInfo(std::string name);

		template<class T, class P>
		void registerBehavior(std::string name);
		std::shared_ptr<Behavior> createBehavior(std::shared_ptr<BehaviorInfo>, std::weak_ptr<Object>, Field*);


		template<class T, class P>
		void registerCommand(std::string name);
		std::shared_ptr<Command> createCommand(std::string name, std::weak_ptr<Object> caller, std::weak_ptr<Object> target);


		void parseInfos(std::ifstream& level, std::ifstream& objects);
		std::shared_ptr<Infos> getInfos() const { return infos; }

	private:
		std::shared_ptr<Infos> infos;

		std::shared_ptr<FieldInfo>(*fieldInfoCreator)() = nullptr;
		std::shared_ptr<Field>(*fieldCreator)(Factory*) = nullptr;

		std::shared_ptr<ObjectInfo>(*objectInfoCreator)() = nullptr;
		std::shared_ptr<Object>(*objectCreator)(uint32_t, std::weak_ptr<ObjectInfo>) = nullptr;

		std::unordered_map <
			std::string,
			std::shared_ptr<BehaviorInfo>(*)() > nameToBehaviorInfoCreator;

		std::unordered_map <
			std::string,
			std::shared_ptr<Behavior>(*)(std::shared_ptr<BehaviorInfo>, std::weak_ptr<Object>, Field*, Factory*)
		> nameToBehaviorCreator;


		std::unordered_map <
			std::string,
			std::shared_ptr<Command>(*)(std::string, std::weak_ptr<Object>, std::weak_ptr<Object>)
		> nameToCommandCreator;
	};


	template<class T, class P>
	std::shared_ptr<P> createInstance() {
		return std::make_shared<T>();
	}

	template<class T, class P>
	std::shared_ptr<P> createInstance(Factory* factory) {
		return std::make_shared<T>(factory);
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
	std::shared_ptr<P> createInstance(std::shared_ptr<BehaviorInfo> info, std::weak_ptr<Object> carrier, Field* field, Factory* factory) {
		return std::make_shared<T>(info, carrier, field, factory);
	}


	template<class T, class P>
	void Factory::registerFieldInfo() {
		fieldInfoCreator = &createInstance < T, P > ;
	}

	template<class T, class P>
	void Factory::registerField() {
		fieldCreator = &createInstance < T, P > ;
	}


	template<class T, class P>
	void Factory::registerObjectInfo() {
		objectInfoCreator = &createInstance < T, P > ;
	}

	template<class T, class P>
	void Factory::registerObject() {
		objectCreator = &createInstance < T, P > ;
	}


	template<class T, class P>
	void Factory::registerBehaviorInfo(std::string name) {
		nameToBehaviorInfoCreator[name] = &createInstance < T, P > ;
	}

	template<class T, class P>
	void Factory::registerBehavior(std::string name) {
		nameToBehaviorCreator[name] = &createInstance < T, P > ;
	}


	template<class T, class P>
	void Factory::registerCommand(std::string name) {
		nameToCommandCreator[name] = &createInstance < T, P > ;
	}
}
