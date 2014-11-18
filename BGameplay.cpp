// BGameplay.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "src\Object.h"
#include "src\Behavior.h"
#include "src\Field.h"
#include "CustomBehavior.h"
#include "CustomBehaviorInfo.h"
#include "CustomCommand.h"
#include "CustomFactory.h"


int _tmain(int argc, _TCHAR* argv[])
{
	CustomFactory factory;

	// register all infos and derived classes
	factory.registerFieldInfo< FieldInfo, FieldInfo >();
	factory.registerField< Field, Field >(); 
	
	factory.registerObjectInfo< ObjectInfo, ObjectInfo >();
	factory.registerObject< Object, Object >();

	factory.registerBehaviorInfo< CustomBehaviorInfo, BehaviorInfo >(factory.HIT_BEHAVIOR); // typically unique classes
	factory.registerBehaviorInfo< CustomBehaviorInfo, BehaviorInfo >(factory.HEAL_BEHAVIOR);

	factory.registerBehavior< CustomBehavior, Behavior >(factory.HIT_BEHAVIOR);
	factory.registerBehavior< CustomBehavior, Behavior >(factory.HEAL_BEHAVIOR);

	factory.registerCommand<CustomCommand, Command>(factory.CUSTOM_COMMAND);
	// ---
		
	std::shared_ptr<Infos> infos = std::make_shared<Infos>(&factory);
	std::shared_ptr<Field> field = factory.createField(infos);

	field->startBehaviors();
	field->doStep(1.0f);
	field->doStep(1.0f);

	return 0;
}

