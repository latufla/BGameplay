#pragma once
#include <memory>
#include <vector>

class Behavior;

class Object {
public:
	Object() = delete;
	Object(uint32_t id, std::string name);	

	virtual ~Object();

	uint32_t getId() const { return id; }
	std::string getName() const { return name; }

	void setRemove(bool val) { remove = val; }
	bool getRemove() const { return remove; }

protected:
	bool addBehavior(std::weak_ptr<Behavior>);
	bool removeBehavior(std::weak_ptr<Behavior>);

	bool startBehaviors();
	bool stopBehaviors();
	
	bool pauseBehaviors();
	bool resumeBehaviors();

	std::vector<std::weak_ptr<Behavior>> getBehaviors() const { return behaviors; }

	uint32_t id;
	std::string name;

	std::vector<std::weak_ptr<Behavior>> behaviors;
	
	bool remove = false;

	friend class Field;
};

