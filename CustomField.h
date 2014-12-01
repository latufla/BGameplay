#pragma once
#include "src\Field.h"

class CustomField : public bg::Field{
public:
	CustomField(bg::Factory* factory)
		: bg::Field(factory) {
	};
};

