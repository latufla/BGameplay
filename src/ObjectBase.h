#pragma once
class ObjectBase {
public:
	ObjectBase() = delete;
	ObjectBase(uint32_t id, std::string name);	

	virtual ~ObjectBase() = 0;

	uint32_t getId() const { return id; }
	std::string getName() const { return name; }

private:
	uint32_t id;
	std::string name;
};

