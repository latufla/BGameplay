#pragma once
#include <memory>
#include <vector>
#include "ObjectInfo.h"


namespace bg {

	class Behavior;

	class Object {
	public:
		Object() = delete;
		Object(uint32_t id, std::weak_ptr<ObjectInfo> info);

		virtual ~Object();

		uint32_t getId() const { return id; }
		std::string getName() const { return name; }

		std::weak_ptr<ObjectInfo> getInfo() const { return info; }

	protected:
		void setRemove(bool val) { remove = val; }
		bool getRemove() const { return remove; }

		bool addBehavior(std::weak_ptr<Behavior>);
		bool removeBehavior(std::weak_ptr<Behavior>);

		bool startBehaviors();
		bool stopBehaviors();

		bool pauseBehaviors();
		bool resumeBehaviors();

		std::vector<std::weak_ptr<Behavior>> getBehaviors() const { return behaviors; }

		uint32_t id;

		std::string name;
		std::weak_ptr<ObjectInfo> info;

		std::vector<std::weak_ptr<Behavior>> behaviors;

		bool remove = false;

		friend class Field;
		friend class Behavior;
	};
}

