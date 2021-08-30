// EXAMPLE code

#include "ObjMain.h"
#include "SecondaryShip.h"

ASecondaryShip::ASecondaryShip()
{

	MaxRollSpeed = 50.f;
	CurrentRollSpeed = 0;
	SetTargCurrentSP(100.f);//default
	SetTargMaxSP(100.f);

}
void ASecondaryShip::BeginPlay()
{
	Super::BeginPlay();
	FacePlayerTime = 9.f;
	bIsAIActive = true;
	bIsPFireActive = true;
	bShouldFacePlayer = false;
	SetAIUpdateActive(2.0f);
	SetPFireActive(2.f);//time for testing

	GetWorldTimerManager().SetTimer(timerPrimaryFire, this, &ASecondaryShip::PrimaryFire, 6.f, true);
	GetWorldTimerManager().SetTimer(timerAIUpdate, this, &ASecondaryShip::AIUpdate, 16.f, true);
	GetWorldTimerManager().SetTimer(timerFacePlayer, this, &ASecondaryShip::FacePlayer, FacePlayerTime, true);
}
//When activated, enemy will fire primary weapon at player every (PFireDelay) seconds(?)
void ASecondaryShip::SetPFireActive(float PFireDelay)
{
	if (PFireDelay>0.f&&bIsPFireActive)
	{
		GetWorldTimerManager().SetTimer(timerPrimaryFire, this, &ASecondaryShip::PrimaryFire, 6.f, true);
		//GetWorldTimerManager().ClearTimer(timerPrimaryFire);
	}
	else if (!bIsPFireActive)
	{
		GetWorldTimerManager().ClearTimer(timerPrimaryFire);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("PFireDelay <=0, out of range OR unknown error"));
	}
}
void ASecondaryShip::SetAIUpdateActive(float AIUpdateDelay)
{
	if (AIUpdateDelay>0.f&&bIsAIActive)
	{
		GetWorldTimerManager().SetTimer(timerAIUpdate, this, &ASecondaryShip::AIUpdate, 2.f, true);

	}
	else if (!bIsAIActive)
	{
		GetWorldTimerManager().ClearTimer(timerAIUpdate);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("AIUpdate <=0, out of range OR unknown error"));
	}
}


void ASecondaryShip::UseActionSlot1_Implementation()
{
	//use action slot 1
	UE_LOG(LogTemp, Warning, TEXT("AS1"));
}
float ASecondaryShip::GetSPRatio()
{
	return (0.7f);
}

float ASecondaryShip::DmgSP(float tmpDmg)
{

	TargDmgSP(tmpDmg);
	return (GetTargCurrentSP());
}



void ASecondaryShip::AIUpdate_Implementation()
{
	//move BP stuff over here wehn getting ready to release
}

void ASecondaryShip::FacePlayer()
{
	if (!bShouldFacePlayer)
	{
		bShouldFacePlayer = true;
	}
}

bool ASecondaryShip::GetShouldFacePlayer()
{
	return bShouldFacePlayer;
}
void ASecondaryShip::SetShouldFacePlayer(bool bShould)
{
	bShouldFacePlayer = bShould;
}
