// EXAMPLE code
#include "ObjMain.h"
#include "Targetable.h"


// Sets default values
ATargetable::ATargetable()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	TargWeapon1 = CreateDefaultSubobject<UWeaponAC>(TEXT("TargWeaponSys")); 
	TargDefenseSys = CreateDefaultSubobject<UDefenseSysAC>(TEXT("TargDefensiveSystems"));
	DistanceToPlayer = 666.f;//Number of the beast for testing
	BuffStartIndex = 5;
	MaxStatusEffects = 10;
	TestNum = 0;
	GCDTicks = 0;
}

// Called when the game starts or when spawned
void ATargetable::BeginPlay()
{
	Super::BeginPlay();
	bIsAwareOfPlayer = false;
	bCanBeTargeted = true;
	//TargDefenseSys->AddStatus(EStatusEnum::StatE_Sleep, 0);
	MaxStatusEffects = TargDefenseSys->GetMaxStatusEffects();

	for (int32 b = 0; b < MaxStatusEffects; b++)
	{
		StatusTicks.Add(0);
	}
	TargWeapon1->SetMaxOptimalRange(10000.f);//close range testing...
	TargWeapon1->SetMaxFalloffRange(5000.f);
	TargWeapon1->SetMaxRange(20000.f);
}

float ATargetable::GetDistanceToPlayer()
{
	DistanceToPlayer = GetDistanceTo(UGameplayStatics::GetPlayerPawn(this, 0));

	return (DistanceToPlayer);
}
void ATargetable::SetTargCurrentSP(float val)
{

}
void ATargetable::SetTargCurrentFP(float val)
{
	int32 valForDS = val;
	TargDefenseSys->SetCurrentFP(valForDS);
}

float ATargetable::TakeSimpDamage(float val)
{
	return (TargDefenseSys->TakeSimpleDamage(val));
}

void ATargetable::TargDmgSP(float val)
{
	TargDefenseSys->DmgSP(val);
	float tmpSP = TargDefenseSys->GetCurrentSP();
	if (tmpSP<=0)
	{
		//DESTROY THE SHIELD
		//Destroy();
	}
}
void ATargetable::TargDmgHP(float val)
{
	TargDefenseSys->DmgHP(val);
	float tmpHP = TargDefenseSys->GetCurrentHP();
	if (tmpHP <= 0)
	{
		//DESTROY THE SHIP
		Destroy();
	}
}


bool ATargetable::SetMinDesiredRange(float val)
{
	//we do not compare min with max here, since we are not assuming the other is set to anything meaningful

	if (val > 0.f)
	{
		MinDesiredRange = val;
		return (true);
	}
	else
	{
		return (false);
	}
}

bool ATargetable::SetMaxDesiredRange(float val)
{
	//here we can compare min with max, since we can assume if min is greater than max, that min has been set.
	//max cannot be less than min logically
	if (val < MinDesiredRange)
	{
		return (false);
	}
	if (val > 0.f)
	{
		MaxDesiredRange = val;
		return (true);
	}
	else
	{
		return (false);
	}
	
}

float ATargetable::GetMinDesiredRange()
{
	return (MinDesiredRange);
}

float ATargetable::GetMaxDesiredRange()
{
	return (MaxDesiredRange);
}


void ATargetable::BecomeAwareOfPlayer()
{
	bIsAwareOfPlayer = true;
}

void ATargetable::BecomeUnwareOfPlayer()
{
	bIsAwareOfPlayer = false;
}

bool ATargetable::GetAwarenessOfPlayer()
{
	return (bIsAwareOfPlayer);
}

bool ATargetable::WithinWeaponRangeToPl()
{
	if ((GetDistanceToPlayer()) < (TargWeapon1->MaxRange()))
	{
		return (true);
	}
	else
	{
		return (false);
	}
}


float ATargetable::GetAWMaxRange()
{
	return (TargWeapon1->MaxRange());
}
float ATargetable::GetAWFalloff()
{
	return (TargWeapon1->MaxFalloffRange());
}
float  ATargetable::GetAWMaxOptimal()
{
	return (TargWeapon1->MaxOptimalRange());
}

bool ATargetable::GetCanTarget()
{
	if (TargDefenseSys->GetCurrentHP() <= 0.f)
	{
		bCanBeTargeted = false;
	}
	//bCanBeTargeted = true;
	//return true;
	return (bCanBeTargeted);
}

void ATargetable::SetCanTarget(bool bCanTarget)
{
	bCanBeTargeted = bCanTarget;
}

//STATUS STUFF
//-------------------------------------------------
EStatusEnum ATargetable::GetStatus(int32 TmpIndex)
{
	if (TmpIndex < 0 && TmpIndex >= MaxStatusEffects)//if (TmpIndex < 0 && TmpIndex >= MaxStatusEffects)
	{
		return (EStatusEnum::StatE_None);
	}
	else
	{
		return (TargDefenseSys->GetStatus(TmpIndex));//return (TargDefenseSys->GetStatus(TmpIndex));
	}
}


bool ATargetable::AddStatus(EStatusEnum TmpStatus, int32 TmpIndex, bool bIsBuff)
{

	//needs to behave differently based on if the status is already applied
	bool bTmpCk = false;
	if (TargDefenseSys->CheckForStatus(TmpStatus) > 0)
	{
		bTmpCk = true;
	}

	//GetWorldTimerManager().SetTimer(Status1Timer, this, &AObjMainPawn::ClearStatus, TmpTime, false);WORKIG ON CHANING THIS TO AN ARRAY
	if (!bIsBuff&&TmpIndex >= 0 && TmpIndex < BuffStartIndex)
	{


		TargDefenseSys->AddStatus(TmpStatus, TmpIndex);


		if (ApplyStatus(TmpStatus, TmpIndex, bTmpCk))
		{

		}
		else
		{

			return false;
		}
		return true;

	}
	else if (bIsBuff&&TmpIndex >= TmpIndex && TmpIndex < MaxStatusEffects)
	{

		TargDefenseSys->AddStatus(TmpStatus, TmpIndex);
		if (ApplyStatus(TmpStatus, TmpIndex, bTmpCk))
		{

		}
		else
		{

			return false;
		}
		return true;
	}

	else
	{
		return false;
	}

}

bool ATargetable::SimpleAddStatus(EStatusEnum TmpStatus, bool bIsBuff)
{
	if (!bIsBuff)
	{
		for (int32 i = 0; i < BuffStartIndex; i++)
		{
			if (GetStatus(i) == EStatusEnum::StatE_None || GetStatus(i) == TmpStatus)
			{
				AddStatus(TmpStatus, i, bIsBuff);
				return true;
			}
		}
		return false;
	}
	else
	{
		for (int32 i = BuffStartIndex; i < MaxStatusEffects; i++)
		{
			if (GetStatus(i) == EStatusEnum::StatE_None || GetStatus(i) == TmpStatus)
			{
				AddStatus(TmpStatus, i, bIsBuff);
				return true;
			}
		}
		return false;
	}
}

//----TICKS
int32 ATargetable::GetGCDTicks()
{
	return (GCDTicks);
}

int32 ATargetable::HandleGCDTick()
{
	for (int32 i = 0; i < MaxStatusEffects; i++)
	{
		if (StatusTicks[i] > 1)
		{
			StatusTicks[i]--;
		}
		else
		{

			if (TargDefenseSys->GetStatus(i) != EStatusEnum::StatE_None)
			{
				StatusTicks[i] = 0;
				if (!RemoveStatus(i))
				{
					UE_LOG(LogTemp, Warning, TEXT("TARGET unable to remove status"));
				}

			}

		}
	}

	return (GCDTicks++);
	//}
}

void ATargetable::SetGCDTicks(int32 NewTicks)
{
	GCDTicks = NewTicks;
}


EStatusEnum ATargetable::GetNPCStatus(int32 TmpIndex)
{
	if (TmpIndex < 0 && TmpIndex >= MaxStatusEffects)
	{
		return (EStatusEnum::StatE_None);
	}
	else
	{
		return (TargDefenseSys->GetStatus(TmpIndex));
	}
}

bool ATargetable::GetIsCorroded()
{
	return bIsCorroded;
}


bool ATargetable::GetIsDampened()
{
	return bIsDampened;
}