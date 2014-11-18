#pragma once
#include "src\Field.h"

class CustomField : public Field{
public:
	CustomField(std::weak_ptr<Infos> infos, Factory* factory)
		: Field(infos, factory) {
	};
};

