#pragma once
#include "src\Factory.h"

class CustomFactory : public bg::Factory{
public:
	const std::string HIT_BEHAVIOR = "HitBehavior";
	const std::string HEAL_BEHAVIOR = "HealBehavior";

	const std::string HIT_COMMAND = "HitCommand";
	const std::string HEAL_COMMAND = "HealCommand";

	CustomFactory() : bg::Factory() {
	};
};

