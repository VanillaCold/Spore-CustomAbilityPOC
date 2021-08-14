#pragma once

#include <Spore\BasicIncludes.h>
#include "ICreatureAbility.h"

#define cSelfHealAbilityPtr intrusive_ptr<cSelfHealAbility>

class cSelfHealAbility 
	: public ICreatureAbility
{
public:
	static const uint32_t TYPE = id("cSelfHealAbility");
	
	cSelfHealAbility();
	~cSelfHealAbility();

	void OnUse(cCreatureAnimalPtr source, cCombatantPtr target, Anim::AnimationMessage* message);

	int AddRef() override;
	int Release() override;
	void* Cast(uint32_t type) const override;
};
