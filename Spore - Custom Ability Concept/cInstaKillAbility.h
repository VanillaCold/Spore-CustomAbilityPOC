#pragma once

#include <Spore\BasicIncludes.h>
#include "ICreatureAbility.h"

#define cInstaKillAbilityPtr intrusive_ptr<cInstaKillAbility>

class cInstaKillAbility 
	: public ICreatureAbility
{
public:
	static const uint32_t TYPE = id("cInstaKillAbility");
	
	cInstaKillAbility();
	~cInstaKillAbility();

	void OnUse(cCreatureAnimalPtr source, cCombatantPtr target, Anim::AnimationMessage* message) override;

	int AddRef() override;
	int Release() override;
	void* Cast(uint32_t type) const override;
};
