#pragma once
#include <memory>
#include <vector>

class BehaviorBase;
enum BehaviorType;

class ObjectBase {
public:
	ObjectBase() = delete;
	ObjectBase(uint32_t id, std::string name);	

	virtual ~ObjectBase();

	uint32_t getId() const { return id; }
	std::string getName() const { return name; }

	void setRemove(bool val) { remove = val; }
	bool getRemove() const { return remove; }

protected:
	bool addBehavior(std::weak_ptr<BehaviorBase>);
	bool removeBehavior(std::weak_ptr<BehaviorBase>);

	bool startBehaviors();
	bool stopBehaviors();
	
	bool pauseBehaviors();
	bool resumeBehaviors();
	
	uint32_t id;
	std::string name;

	std::vector<std::weak_ptr<BehaviorBase>> behaviors;
	
	bool remove = false;

	friend class Field;
};

