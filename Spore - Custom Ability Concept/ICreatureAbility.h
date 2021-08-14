#pragma once

#include <Spore\BasicIncludes.h>

#define ICreatureAbilityPtr intrusive_ptr<ICreatureAbility>

class ICreatureAbility //Extend this class to create a new creature ability
	: public Object
	, public DefaultRefCounted
{
public:

	uint32_t abilityType; //The ability's ID
	PropertyListPtr abilityPropList; //The ability's PropertyListPtr
	uint32_t animationID; //The ability's animation ID - ANIMATION ID MUST BE UNIQUE, THE ANIMATION ITSELF MUST ALSO TRIGGER EVENT ID 0x635E7BCA!

	static const uint32_t TYPE = id("ICreatureAbility");
	
	ICreatureAbility();
	~ICreatureAbility();


	virtual void OnUse(cCreatureAnimalPtr source, cCombatantPtr target, Anim::AnimationMessage* message) = 0; //This function is executed when the ability is used - override it when making a new ability

	int AddRef() override;
	int Release() override;
	void* Cast(uint32_t type) const override;
};
