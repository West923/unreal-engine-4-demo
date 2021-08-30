// EXAMPLE code

#include "ObjMain.h"
#include "DefenseSysAC.h"


// Sets default values for this component's properties
UDefenseSysAC::UDefenseSysAC()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;


	CurrentFieldPoints=0;
	MaxFieldPoints=1;

	CurrentShieldPoints=2000;
	MaxShieldPoints=2000;

	CurrentHullPoints=1500;
	MaxHullPoints=1500;

	CurrentExpressionPoints = 0.f;
	MaxExpressionPoints = 100.f;

	CurrentOrisonPoints = 0.f;
	MaxOrisonPoints = 100.f;


	XP = 100;
	Lvl = 1;
	MaxStatusEffects = 10;
	MaxStatusTime = 2400.f;
}

// Called when the game starts
void UDefenseSysAC::BeginPlay()
{
	Super::BeginPlay();
	for (int32 b = 0; b < MaxStatusEffects; b++)
	{
		StatusList.Add(EStatusEnum::StatE_None);
	}
	
}


int32 UDefenseSysAC::TakeSimpleDamage(int32 SimpDmg)
{
	int32 RemainingDmgPts = SimpDmg;//if an outer defense is brought down, this remaining damage point amount is applied to next inner defense.  outer to inner defenses: Field>Shield>hull
	//deal FP, then SP, then HP
	if (CurrentFieldPoints > 0)
	{
		RemainingDmgPts = DmgFP(RemainingDmgPts);
	}
	if ((CurrentShieldPoints > 0)&&(RemainingDmgPts > 0))
	{
		RemainingDmgPts = DmgSP(RemainingDmgPts);
	}
	if ((CurrentHullPoints > 0) && (RemainingDmgPts > 0))
	{
		RemainingDmgPts = DmgHP(RemainingDmgPts);
	}
	if (RemainingDmgPts > 0)
	{
		return (RemainingDmgPts);
	}
	else
	{
		return (0);
	}
}
// Called every frame
void UDefenseSysAC::TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction )
{
	Super::TickComponent( DeltaTime, TickType, ThisTickFunction );
}

int32 UDefenseSysAC::GetCurrentSP()
{
	return CurrentShieldPoints;
}

int32 UDefenseSysAC::GetMaxSP()
{
	return MaxShieldPoints;
}
int32 UDefenseSysAC::DmgSP(int32 DmgAmt)
{
	if (DmgAmt > CurrentShieldPoints)
	{
		DmgAmt -= CurrentShieldPoints;
		CurrentShieldPoints = 0;
		return (DmgAmt);
	}
	else
	{
		CurrentShieldPoints -= DmgAmt;
		return (0);
	}

}
void UDefenseSysAC::IncreaseSP(int32 Amt)
{
	if ((MaxShieldPoints - CurrentShieldPoints) <= Amt)
	{
		CurrentShieldPoints = MaxShieldPoints;
	}
	else
	{
		CurrentShieldPoints += Amt;
	}
}
float UDefenseSysAC::GetCurrentEP()
{
	return CurrentShieldPoints;
}

float UDefenseSysAC::GetMaxEP()
{
	return MaxShieldPoints;
}
float UDefenseSysAC::ChangeEP(float ChangeAmt)
{
	CurrentExpressionPoints += ChangeAmt;
	return CurrentExpressionPoints;
}

int32 UDefenseSysAC::GetCurrentFP()
{
	return CurrentFieldPoints;
}

void UDefenseSysAC::SetCurrentFP(int32 tmp)
{
	if (tmp >= 0 && tmp <= MaxFieldPoints)
	{
		CurrentFieldPoints = tmp;
	}

}
int32 UDefenseSysAC::GetMaxFP()
{
	return MaxFieldPoints;
}

int32 UDefenseSysAC::DmgFP(int32 DmgAmt)
{
	if (DmgAmt > CurrentFieldPoints)
	{
		DmgAmt -= CurrentFieldPoints;
		CurrentFieldPoints = 0;
		return (DmgAmt);
	}
	else
	{
		CurrentFieldPoints -= DmgAmt;
		return (0);
	}
}

void UDefenseSysAC::AddFP(int32 AddAmt)
{
	if ((CurrentFieldPoints + AddAmt) >= MaxFieldPoints)
	{
		CurrentFieldPoints = MaxFieldPoints;
	}
	else
	{
		CurrentFieldPoints += AddAmt;
	}
}
int32 UDefenseSysAC::GetCurrentHP()
{
	return CurrentHullPoints;
}

int32 UDefenseSysAC::GetMaxHP()
{
	return MaxHullPoints;
}

int32 UDefenseSysAC::DmgHP(int32 DmgAmt)
{
	if (DmgAmt > CurrentHullPoints)
	{
		DmgAmt -= CurrentHullPoints;
		CurrentHullPoints = 0;
		return (DmgAmt);
	}
	else
	{
		CurrentHullPoints -= DmgAmt;
		return (0);
	}
}

int32 UDefenseSysAC::GetCurrentXP()
{
	return (XP);
}

int32 UDefenseSysAC::GetCurrentLvl()
{
	return (Lvl);
}

int32 UDefenseSysAC::SetLvl(int32 NewLvl)
{
	if (NewLvl < 1)
	{
		//error...
		return (-1);
	}
	else
	{
		Lvl = NewLvl;
	}
	return (Lvl);
}
float UDefenseSysAC::GetCurrentOP()
{
	if (CurrentExpressionPoints > MaxExpressionPoints)
	{
		CurrentOrisonPoints = CurrentExpressionPoints - MaxExpressionPoints;
	}
	else
	{
		CurrentOrisonPoints = 0.f;
	}
	return CurrentOrisonPoints;
}

float UDefenseSysAC::GetMaxOP()
{
	return MaxOrisonPoints;
}


bool UDefenseSysAC::AddStatus(EStatusEnum TmpStatus,  int32 TmpIndex)
{
	if ((TmpIndex >= MaxStatusEffects) || (TmpIndex<0))
	{
		return false;
	}
	else
	{
		StatusList[TmpIndex] = TmpStatus;
		return true;
	}

}

bool UDefenseSysAC::RemoveStatus(int32 TmpIndex)
{
	if ((TmpIndex >= MaxStatusEffects) || (TmpIndex<0))
	{
		return false;
	}
	else
	{
		StatusList[TmpIndex] = EStatusEnum::StatE_None;
		//bHasStatusChanged = true;
		return true;
	}
}
int32 UDefenseSysAC::CheckForStatus(EStatusEnum TmpStatus)
{
	int32 totalInst = 0;
	for (int32 i = 0; i < MaxStatusEffects; i++)
	{
		if (StatusList[i] == TmpStatus)
		{
			totalInst++;
		}
	}
	return totalInst;
}
int32 UDefenseSysAC::GetMaxStatusEffects()
{
	return MaxStatusEffects;
}

EStatusEnum UDefenseSysAC::GetStatus(int32 TmpIndex) 
{

	if (TmpIndex < 0 && TmpIndex >= MaxStatusEffects)
	{
		return (EStatusEnum::StatE_None);
	}
	else if (TmpIndex>=StatusList.Num())
	{

		return (EStatusEnum::StatE_None);
	}
	else
	{
		return (StatusList[TmpIndex]);
	}
}

void UDefenseSysAC::SetDefensePoints(int32 TmpFP, int32 TmpSP, int32 TmpHP)
{
	if (TmpFP <= 0)
	{
		CurrentFieldPoints = 0;
		MaxFieldPoints = 1;
	}
	else
	{
		CurrentFieldPoints = TmpFP;
		MaxFieldPoints = TmpFP;
	}

	if (TmpSP <= 0)
	{
		CurrentShieldPoints = 0;
		MaxShieldPoints = 1;
	}
	else
	{
		CurrentShieldPoints = TmpSP;
		MaxShieldPoints = TmpSP;
	}

	if (TmpHP <= 0)
	{
		CurrentHullPoints = 0;
		MaxHullPoints = 1;
	}
	else
	{
		CurrentHullPoints = TmpHP;
		MaxHullPoints = TmpHP;
	}


}