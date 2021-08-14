#include "stdafx.h"
#include "ICreatureAbility.h"


ICreatureAbility::ICreatureAbility()
{
}


ICreatureAbility::~ICreatureAbility()
{
}

// For internal use, do not modify.
int ICreatureAbility::AddRef()
{
	return DefaultRefCounted::AddRef();
}

// For internal use, do not modify.
int ICreatureAbility::Release()
{
	return DefaultRefCounted::Release();
}

// You can extend this function to return any other types your class implements.
void* ICreatureAbility::Cast(uint32_t type) const
{
	CLASS_CAST(Object);
	CLASS_CAST(ICreatureAbility);
	return nullptr;
}
