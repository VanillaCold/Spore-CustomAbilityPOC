#include "stdafx.h"
#include "CustomAbilityConcept.h"
#include <Spore\Anim\AnimatedCreature.h>

CustomAbilityConcept::CustomAbilityConcept()
{
}


CustomAbilityConcept::~CustomAbilityConcept()
{
}

// For internal use, do not modify.
int CustomAbilityConcept::AddRef()
{
	return DefaultRefCounted::AddRef();
}

// For internal use, do not modify.
int CustomAbilityConcept::Release()
{
	return DefaultRefCounted::Release();
}

// You can extend this function to return any other types your class implements.
void* CustomAbilityConcept::Cast(uint32_t type) const
{
	CLASS_CAST(Object);
	CLASS_CAST(CustomAbilityConcept);
	return nullptr;
}

bool CustomAbilityConcept::HandleMessage(uint32_t messageID, void* msg)
{
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
				DoAbility(crt,target,newMsg);
				return true;
			}
	}
	return false;
}

bool CustomAbilityConcept::DoAbility(cCreatureAnimalPtr source, cCombatantPtr target, Anim::AnimationMessage* message)
{
	target->SetHealthPoints(target->mHealthPoints - 5);
	target->ToSpatialObject()->SetScale(target->ToSpatialObject()->mScale / 2);
	return false;
}
