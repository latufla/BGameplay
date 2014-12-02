// BGameplay.cpp : Defines the entry point for the console application.
//

#include <fstream>

#include "src/SharedHeaders.h"
#include "src/Object.h"
#include "src/Behavior.h"
#include "src/Field.h"

#include "CustomFactory.h"
#include "CustomFieldInfo.h"
#include "CustomField.h"
#include "CustomObjectInfo.h"
#include "CustomObject.h"
#include "HitBehaviorInfo.h"
#include "HealBehaviorInfo.h"
#include "HitBehavior.h"
#include "HealBehavior.h"
#include "HitCommand.h"
#include "HealCommand.h"
#include "src/exceptions/Exception.h"


void run();
void handleExceptions();

int _tmain(int argc, _TCHAR* argv[])
{
	try {
		run();
	} catch(...) {
		handleExceptions();
	}

	return 0;
}

void run() {
	CustomFactory factory;

	// ONCE, register all classes
 	factory.registerFieldInfo< CustomFieldInfo, bg::FieldInfo >();
	factory.registerField< CustomField, bg::Field >();
 
 	factory.registerObjectInfo< CustomObjectInfo, bg::ObjectInfo >();
  	factory.registerObject< CustomObject, bg::Object >();

	factory.registerBehaviorInfo< HitBehaviorInfo, bg::BehaviorInfo >(factory.HIT_BEHAVIOR);
 	factory.registerBehaviorInfo< HealBehaviorInfo, bg::BehaviorInfo >(factory.HEAL_BEHAVIOR);

	factory.registerBehavior< HitBehavior, bg::Behavior >(factory.HIT_BEHAVIOR);
 	factory.registerBehavior< HealBehavior, bg::Behavior >(factory.HEAL_BEHAVIOR);

	factory.registerCommand<HitCommand, bg::Command>(factory.HIT_COMMAND);
 	factory.registerCommand<HealCommand, bg::Command>(factory.HEAL_COMMAND);
	// ---


	// EACH LEVEL, load infos
	{
		std::string levelPath = "config/Level1.yml";
		std::ifstream level(levelPath);
		if(!level.is_open())
			throw bg::IOException(EXCEPTION_INFO, levelPath);

		std::string objectsPath = "config/Level1Objects.yml";
		std::ifstream objects(objectsPath);
		if(!objects.is_open())
			throw bg::IOException(EXCEPTION_INFO, objectsPath);

		factory.parseInfos(level, objects);
	}


	auto field = factory.createField();
	field->startBehaviors();
    field->doStep(1.0f);
	field->doStep(1.0f);
}

void handleExceptions() {
	std::string error = "";	
	try {
		throw;
	} catch(bg::Exception& e) {
		error = e.msg();
	} catch(std::exception& e) {
		error = e.what();
	} catch(...) {
		error = "unknown exception";
	}

	if(error != "") {
		std::cout << error;
		std::exit(1);	
	}
}

