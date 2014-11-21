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


int _tmain(int argc, _TCHAR* argv[])
{
	CustomFactory factory;

	// ONCE, register all infos and derived classes
	factory.registerFieldInfo< CustomFieldInfo, FieldInfo >();
	factory.registerField< CustomField, Field >();

	factory.registerObjectInfo< CustomObjectInfo, ObjectInfo >();
	factory.registerObject< CustomObject, Object >();

	factory.registerBehaviorInfo< HitBehaviorInfo, BehaviorInfo >(factory.HIT_BEHAVIOR); // typically unique classes
	factory.registerBehaviorInfo< HealBehaviorInfo, BehaviorInfo >(factory.HEAL_BEHAVIOR);

	factory.registerBehavior< HitBehavior, Behavior >(factory.HIT_BEHAVIOR);
	factory.registerBehavior< HealBehavior, Behavior >(factory.HEAL_BEHAVIOR);

	factory.registerCommand<HitCommand, Command>(factory.HIT_COMMAND);
	factory.registerCommand<HealCommand, Command>(factory.HEAL_COMMAND);
	// ---

	// EACH LEVEL, load infos
	std::ifstream level, objects;
	level.open("config/Level1.yml");
	objects.open("config/Level1Objects.yml");
	if(!level.is_open() || !objects.is_open())
		return 0;

	factory.parseInfos(level, objects);
	level.close();
	objects.close();
	// ---

	std::shared_ptr<Field> field = factory.createField();

	field->startBehaviors();
	field->doStep(1.0f);
	field->doStep(1.0f);

	return 0;
}

