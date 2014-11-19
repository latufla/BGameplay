#pragma once
class Info {
public:
	Info() = default;
	~Info() = default;
	
	int32_t id;
	std::string name;
	
	virtual void update(std::string, int32_t);
	virtual void update(std::string, float);
	virtual void update(std::string, std::string);
};

