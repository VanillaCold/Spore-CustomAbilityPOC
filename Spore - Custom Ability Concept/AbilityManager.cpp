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

cAbilityManager* cAbilityManager::sInstance;

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
	if (messageID == id("AnimationManager_Message")) //Only accept this message ID, and no others
	{
		SporeDebugPrint("Triggered custom behaviour!");
		auto newMsg = (Anim::AnimationMessage*)msg; //use casting to get an Anim::AnimationMessage from the msg variable
			message = newMsg;;
			auto pos = newMsg->pCreature->mPosition; //get the creature's position
			SporeDebugPrint("Position of creature that triggered event: X = %f, Y = %f, Z = %f", pos.x, pos.y, pos.z); //print the creature's position to the debug console

			cCreatureAnimalPtr crt = nullptr; //create two pointers and set them to nullptr
			cCombatantPtr target = nullptr;
			for (auto creature : Simulator::GetData<Simulator::cCreatureAnimal>()) { //loop through all creatures
				if (creature->mpAnimatedCreature.get() == newMsg->pCreature && crt == nullptr) //if the current creature is the owner of the AnimatedCreature that triggered the event, do the following
				{
					SporeDebugPrint("Found creature that triggered ability"); //Print it to the debug console when compiled as a debug DLL
					if (creature.get() == GameNounManager.GetAvatar()) //if the trigger creature is the avatar, print it to the debug console when compiled as a debug DLL
					{
						SporeDebugPrint("Trigger is the avatar!");
					}
					crt = creature; //set the crt pointer to the current creature
					break; //Leave the loop, as the creature was found.
				}

			}
	

			if (crt != nullptr) //If the creature is not nullptr...
			{

				//SporeDebugPrint("%i", crt->field_E7C); //
				target = crt->mpCombatantTarget; //Find the creature's target
				auto pos2 = target->ToSpatialObject()->GetPosition(); //Get the target's position
				SporeDebugPrint("Position of combatant that was targetted by player: X = %f, Y = %f, Z = %f", pos2.x, pos2.y, pos2.z); //print the creature's position to the debug console when compiled as a debug DLL

				ICreatureAbilityPtr ability = nullptr; //create an ICreatureAbilityPtr (see ICreatureAbility.h)

				uint32_t animID; //create a new uint32_t
				newMsg->pCreature->GetCurrentAnimation(&animID); //Set the animID variable to the trigger's current animation

				for (int i = 0; i < currentAbilities.size(); i++) //loop through all custom abilities and do the following for each
				{
					if (currentAbilities[i]->animationID == animID) // If the ability's animation ID is equal to the trigger's current animation...
					{
						ability = currentAbilities[i]; //Set the contents of the ability pointer
						ability->OnUse(crt, target, newMsg); //Trigger the ability's OnUse() function
						return true; //Returns true, as the ability has been found. 
					}
				}
			}
	}
	return false; //Returns false if the message is incorrect, if there is no found trigger or if the trigger's animation doesn't match any abilities.
}

ICreatureAbility* cAbilityManager::CreateAbility(uint32_t type, uint32_t instanceID, uint32_t animation, ICreatureAbility* ability)
{
	ability->abilityType = type; //Set the ability's ID

	PropManager.GetPropertyList(instanceID, GroupIDs::CreatureAbilities, ability->abilityPropList); //Gets the ability's property list and attaches it to the abilityPropList variable

	ability->animationID = animation; //Sets the ability's animation ID, which tells Spore when to use
	currentAbilities.push_back(ability); //Adds the ability to currentAbilities
	return ability; //return the ability, in case it's needed for something else
}


//Depricated functions below

/*void cAbilityManager::AddAbility(ICreatureAbility* ability)
{
	/*auto ability = new CustomAbilityType();
	ability->abilityType = abilityID;
	ability->animationID = animationID;

	PropertyListPtr propList;
	PropManager.GetPropertyList(instanceID, GroupIDs::CreatureAbilities, propList);
	ability->propList.attach(propList.get());
	propList.detach();
}*/

/*bool cAbilityManager::DoAbility(cCreatureAnimalPtr source, cCombatantPtr target, Anim::AnimationMessage* message, CustomAbilityType* abilityType)
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
}*/