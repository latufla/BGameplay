#pragma once
#pragma warning( disable : 4996) // TODO: why yaml cpp?

#include <memory>
#include <vector>
#include <unordered_map>
#include "Factory.h"
#include "Object.h"
#include "ObjectInfo.h"

namespace bg {
	class Field {
	public:
		Field(Factory*);

		virtual ~Field();

		std::vector<std::weak_ptr<Object>> getObjectsBy(std::string applicableCommand, std::string commander);

		bool startBehaviors();
		bool startBehaviors(std::weak_ptr<Object>);

		bool stopBehaviors();
		bool stopBehaviors(std::weak_ptr<Object>);

		bool pauseBehaviors();
		bool pauseBehaviors(std::weak_ptr<Object>);

		bool resumeBehaviors();
		bool resumeBehaviors(std::weak_ptr<Object>);

		virtual bool doStep(float stepSec);

	protected:
		virtual std::weak_ptr<Object> addObject(std::weak_ptr<FieldInfo::FieldItemInfo>);
		std::weak_ptr<Object> addObject(uint32_t id, std::weak_ptr<ObjectInfo> info);
		void removeObject(std::weak_ptr<Object>, bool onNextStep = false);

		void doRemoveStep();

		std::vector<std::shared_ptr<Object>> objects;
		std::vector<std::shared_ptr<Behavior>> behaviors;

		Factory* factory;
	};

}
