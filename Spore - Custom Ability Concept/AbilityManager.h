#pragma once

#include <Spore\BasicIncludes.h>
#include <Spore\App\IMessageListener.h>

#define CustomAbilityConceptPtr intrusive_ptr<AbilityManager>

class AbilityManager
	: public Object
	, public DefaultRefCounted
	, public App::IMessageListener
{
public:

	struct CustomAbilityType
	{
		uint32_t abilityType;
		PropertyListPtr propList;
	};

	static const uint32_t TYPE = id("AbilityManager");
	
	AbilityManager();
	~AbilityManager();

	Anim::AnimationMessage* message;
	int AddRef() override;
	int Release() override;
	void* Cast(uint32_t type) const override;
	bool HandleMessage(uint32_t messageID, void* msg) override;
	bool DoAbility(cCreatureAnimalPtr source, cCombatantPtr target, Anim::AnimationMessage* message, CustomAbilityType abilityType);
};
