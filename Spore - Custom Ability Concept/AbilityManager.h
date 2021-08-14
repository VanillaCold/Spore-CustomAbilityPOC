#pragma once

#include <Spore\BasicIncludes.h>
#include <Spore\App\IMessageListener.h>
#include "ICreatureAbility.h"

#define AbilityManager  (*cAbilityManager::Get())
#define CustomAbilityConceptPtr intrusive_ptr<cAbilityManager>

class cAbilityManager
	: public Object
	, public DefaultRefCounted
	, public App::IMessageListener
{
public:

	/*struct CustomAbilityType
	{
		uint32_t abilityType; //The ability's ID
		PropertyListPtr propList; //The ability's PropertyListPtr
		uint32_t animationID; //The ability's animation ID - MUST BE UNIQUE, MUST ALSO TRIGGER EVENT ID 0x635E7BCA!
	};*/

	static const uint32_t TYPE = id("cAbilityManager-POC"); //Add your mod's name to this as a prefix, so that mods which include the Ability Manager won't conflict with each other.
	
	cAbilityManager();
	~cAbilityManager();

	vector<ICreatureAbilityPtr> currentAbilities;
	Anim::AnimationMessage* message;
	int AddRef() override;
	int Release() override;

	static cAbilityManager* Get();
	ICreatureAbility* CreateAbility(uint32_t type, uint32_t instanceID, uint32_t animation, ICreatureAbility* ability);

	void* Cast(uint32_t type) const override;
	bool HandleMessage(uint32_t messageID, void* msg) override;
	//bool DoAbility(cCreatureAnimalPtr source, cCombatantPtr target, Anim::AnimationMessage* message, CustomAbilityType* abilityType);

protected:
	static cAbilityManager* sInstance;
};
