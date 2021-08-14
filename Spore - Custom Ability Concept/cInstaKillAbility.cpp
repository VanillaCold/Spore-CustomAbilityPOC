#include "stdafx.h"
#include "cInstaKillAbility.h"

cInstaKillAbility::cInstaKillAbility()
{
}


cInstaKillAbility::~cInstaKillAbility()
{
}

void cInstaKillAbility::OnUse(cCreatureAnimalPtr source, cCombatantPtr target, Anim::AnimationMessage* message)
{
	target->SetHealthPoints(0); //Simply just set the health of the target to 0

	//ignore the following
	/*if(target->mHealthPoints <= 0 && object_cast<Simulator::cCreatureAnimal>(target.get()) != nullptr)
	{
		auto crt = (Simulator::cCreatureAnimal*)target.get(); //Cast the target to become a cCreatureAnimal
		SporeDebugPrint("%b", crt->field_F90);
		crt->mbDead = 1; //
		crt->field_F90 = 1;
		//target->func2Ch(0); func2Ch() fills up health bar?

		// field_80 says if it has infinite health or not
	}
	//return true;
	//target->ToSpatialObject()->SetScale(target->ToSpatialObject()->mScale / 2);*/
}

// For internal use, do not modify.
int cInstaKillAbility::AddRef()
{
	return DefaultRefCounted::AddRef();
}

// For internal use, do not modify.
int cInstaKillAbility::Release()
{
	return DefaultRefCounted::Release();
}

// You can extend this function to return any other types your class implements.
void* cInstaKillAbility::Cast(uint32_t type) const
{
	CLASS_CAST(Object);
	CLASS_CAST(cInstaKillAbility);
	return nullptr;
}
