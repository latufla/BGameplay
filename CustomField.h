#pragma once
#include "src\Field.h"

class CustomField : public Field{
public:
	CustomField(Factory* factory)
		: Field(factory) {
	};
};

