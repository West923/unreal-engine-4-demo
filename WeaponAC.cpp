// EXAMPLE code

#include "ObjMain.h"
#include "WeaponAC.h"


// Sets default values for this component's properties
UWeaponAC::UWeaponAC()
{
	PrimaryComponentTick.bCanEverTick = true;

	baseDmg = 100.f;

	AttunementEnum = EAttunementEnum::AE_Sapphire;
	ActionEnum = EActionEnum::ActE_None;
	RangeOptimal = 50000;
	RangeMax = 80000;
	RangeFalloff = 10000;

}

void UWeaponAC::BeginPlay()
{
	Super::BeginPlay();
}

void UWeaponAC::TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction )
{
	Super::TickComponent( DeltaTime, TickType, ThisTickFunction );

}

void UWeaponAC::SetAction(EActionEnum TmpEnum)
{
	ActionEnum = TmpEnum;
}

EActionEnum UWeaponAC::GetAction()
{
	return (ActionEnum);
}

float UWeaponAC::CalcTotalDmg()
{
	float tmpFloat = baseDmg;
	return (tmpFloat);
}
EAttunementEnum UWeaponAC::GetAttunement()
{
	return (AttunementEnum);
}

void UWeaponAC::SetAttunement(EAttunementEnum TmpAtt)
{
	AttunementEnum = TmpAtt;
}

bool UWeaponAC::FireWeapon(int32 ActionPKey)
{
	if (ActionPKey == 2)
	{
		return (true);
	}
	else
	{
		return (false);
	}
	
}

float UWeaponAC::MaxLongRange()
{
	return (RangeMax);
}

float UWeaponAC::MaxMidRange()
{
	return (RangeOptimal+RangeFalloff);
}
float UWeaponAC::MaxCloseRange()
{
	return (RangeOptimal);
}

float UWeaponAC::GetMaxRange()
{
	return (RangeMax);
}
//------------------------------------------
float UWeaponAC::MaxOptimalRange()
{
	return (RangeOptimal);
}

float UWeaponAC::MaxFalloffRange()
{
	return (RangeFalloff);
}

float UWeaponAC::MaxRange()
{
	return (RangeMax);
}

void UWeaponAC::SetMaxOptimalRange(float tmp)
{
	RangeOptimal = tmp;
}

void UWeaponAC::SetMaxFalloffRange(float tmp)
{
	RangeFalloff = tmp;
}

void UWeaponAC::SetMaxRange(float tmp)
{
	RangeMax = tmp;
}
void UWeaponAC::GenerateWeaponPreset(int32 PresetNum)
{

	RangeMax = 100000;
}