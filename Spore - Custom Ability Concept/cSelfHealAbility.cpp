#include "stdafx.h"
#include "cSelfHealAbility.h"

cSelfHealAbility::cSelfHealAbility()
{
}


cSelfHealAbility::~cSelfHealAbility()
{
}

void cSelfHealAbility::OnUse(cCreatureAnimalPtr source, cCombatantPtr target, Anim::AnimationMessage* message)
{
	uint32_t level; //create a new uint32_t
	App::Property::GetUInt32(abilityPropList.get(), id("SelfHealAbility-HealingLevel"), level); //set the uint32_t to the value of SelfHealAbility-HealingLevel in the prop file
	source->SetHealthPoints(source->mHealthPoints + (5 * level)); //Increase the health of the source creature
}

// For internal use, do not modify.
int cSelfHealAbility::AddRef()
{
	return DefaultRefCounted::AddRef();
}

// For internal use, do not modify.
int cSelfHealAbility::Release()
{
	return DefaultRefCounted::Release();
}

// You can extend this function to return any other types your class implements.
void* cSelfHealAbility::Cast(uint32_t type) const
{
	CLASS_CAST(Object);
	CLASS_CAST(cSelfHealAbility);
	return nullptr;
}
