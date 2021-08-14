#include "stdafx.h"
#include "AbilityManager.h"
#include <Spore\Anim\AnimatedCreature.h>

cAbilityManager::cAbilityManager()
{
	currentAbilities = {};
	sInstance = this;
}


cAbilityManager::~cAbilityManager()
{
	sInstance = nullptr;
}

// For internal use, do not modify.
int cAbilityManager::AddRef()
{
	return DefaultRefCounted::AddRef();
}

// For internal use, do not modify.
int cAbilityManager::Release()
{
	return DefaultRefCounted::Release();
}

cAbilityManager* cAbilityManager::Get()
{
	return sInstance;
}

void cAbilityManager::AddAbility(uint32_t abilityID, uint32_t animationID, uint32_t instanceID)
{
	auto ability = new CustomAbilityType();
	ability->abilityType = abilityID;
	ability->animationID = animationID;

	PropertyListPtr propList;
	PropManager.GetPropertyList(instanceID, GroupIDs::CreatureAbilities, propList);
	ability->propList.attach(propList.get());
	propList.detach();

	currentAbilities.push_back(ability);
}

// You can extend this function to return any other types your class implements.
void* cAbilityManager::Cast(uint32_t type) const
{
	CLASS_CAST(Object);
	CLASS_CAST(cAbilityManager);
	return nullptr;
}

bool cAbilityManager::HandleMessage(uint32_t messageID, void* msg)
{
	App::ConsolePrintF("aea");
	//Anim::AnimationMessage
	if (messageID == 0x635E7BCA)
	{
		SporeDebugPrint("Triggered custom behaviour!");
		auto newMsg = (Anim::AnimationMessage*)msg; //use casting to get an Anim::AnimationMessage from the msg variable
			message = newMsg;;
			auto pos = newMsg->pCreature->mPosition; //get the creature's position
			SporeDebugPrint("Position of creature that triggered event: X = %f, Y = %f, Z = %f", pos.x, pos.y, pos.z); //print the creature's position to the debug console

			cCreatureAnimalPtr crt = nullptr;
			cCombatantPtr target = nullptr;
			for (auto creature : Simulator::GetData<Simulator::cCreatureAnimal>()) {
				if (creature->mpAnimatedCreature.get() == newMsg->pCreature && crt == nullptr)
				{
					SporeDebugPrint("Found creature that triggered ability");
					if (creature.get() == GameNounManager.GetAvatar())
					{
						SporeDebugPrint("Trigger is the avatar!");
					}
					crt = creature;
					break;
				}

			}
	

			if (crt != nullptr)
			{

				//SporeDebugPrint("%i", crt->field_E7C); //
				target = crt->mpCombatantTarget;//field_E7C; //field_E7C seems to be the target
				auto pos2 = target->ToSpatialObject()->GetPosition();
				SporeDebugPrint("Position of combatant that was targetted by player: X = %f, Y = %f, Z = %f", pos2.x, pos2.y, pos2.z); //print the creature's position to the debug console
			}
			if (crt != nullptr && target != nullptr)
			{
				CustomAbilityType* ability = nullptr;
				for (int i = 0; i < currentAbilities.size(); i++)
				{
					uint32_t animID;
					newMsg->pCreature->GetCurrentAnimation(&animID);
					if (currentAbilities[i]->animationID == animID)
					{
						ability = currentAbilities[i];
						break;
					}
				}
				if (ability != nullptr) DoAbility(crt,target,newMsg, ability);
				return true;
			}
	}
	return false;
}

bool cAbilityManager::DoAbility(cCreatureAnimalPtr source, cCombatantPtr target, Anim::AnimationMessage* message, CustomAbilityType* abilityType)
{
	if (abilityType->abilityType == id("InstaKill"))
	{
		target->SetHealthPoints(0);
		//target->func18h(10000.0F, 1, 1, 1, 1);
		if (target->mHealthPoints <= 0 && object_cast<Simulator::cCreatureAnimal>(target.get()) != nullptr)
		{
			auto crt = (Simulator::cCreatureAnimal*)target.get();
			SporeDebugPrint("%b", crt->field_F90);
			crt->mbDead = 1;
			crt->field_F90 = 1;
			//target->func2Ch(0); func2Ch() fills up health bar?

			// field_80 says if it has infinite health or not
		}
		return true;
		//target->ToSpatialObject()->SetScale(target->ToSpatialObject()->mScale / 2);
	}

	if (abilityType->abilityType == id("SelfHeal"))
	{
		uint32_t level;
		App::Property::GetUInt32(abilityType->propList.get(), id("SelfHealAbility-HealingLevel"), level);
		source->SetHealthPoints(source->mHealthPoints + (5*level));
	}

	return false;
}


cAbilityManager* cAbilityManager::sInstance;