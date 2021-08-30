// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.

#include "ObjMain.h"
#include "ObjMainPawn.h"
#include "DrawDebugHelpers.h"
#include "Targetable.h"
#include "Kismet/KismetMathLibrary.h"
#include "GameFramework/HUD.h"
AObjMainPawn::AObjMainPawn()
{
	struct FConstructorStatics
	{
		ConstructorHelpers::FObjectFinderOptional<UStaticMesh> OrisonMesh;
		FConstructorStatics()
			: OrisonMesh(TEXT("/Game/Meshes/OrisonCPit.OrisonCPit"))
		{
		}
	};
	static FConstructorStatics ConstructorStatics;

	OrisonMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("OrisonMesh"));
	OrisonMesh->SetStaticMesh(ConstructorStatics.OrisonMesh.Get());
	RootComponent = OrisonMesh;
	WeakPoint = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("WeakPoint"));
	WeakPoint->SetupAttachment(RootComponent);


	AutoPossessPlayer = EAutoReceiveInput::Player0;

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm0"));
	SpringArm->SetupAttachment(RootComponent);
	SpringArm->TargetArmLength = 50.f;
	SpringArm->SocketOffset = FVector(-700.f, 0.f, 250.f);
	SpringArm->bEnableCameraLag = true;
	SpringArm->CameraLagSpeed = 15.f;
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("GameCam"));
	Camera->SetupAttachment(SpringArm, USpringArmComponent::SocketName);
	Camera->bUsePawnControlRotation = false; // Don't rotate camera with controller
	FwdAccelerationDEF = 1500.f;
	FwdAcceleration = 4000.f;
	FwdAccelerationBoosted = 7000.f;
	FwdBrakeDecel = -6000.f;
	HorAcceleration = 5000.f;
	VerAcceleration = 1000.f;
	TmpStoreAcceleration = FwdAcceleration;
	ForwardInertialDamper = -0.8f;//set negative to slow forward acc with no input
	DriftForwardInertialDamper = 0;
	UpThrusterAcc = 6000.f;/
	RightThrusterAcc = 3000.f;
	PitchSpeed = 90.f;
	PitchFwdSpdMod = 1.f;
	YawSpeed = 90.f;
	YawFwdSpdMod = 1.f;
	RollSpeed = 65.f;
	RollFwdSpdMod = 1.f;
	StopThreshold = 10.f;
	SpeedLimit = 5100000.f;
	FwdAccelLimitDEF = 15000.f;
	FwdAccelLimit = FwdAccelLimitDEF;

	FwdAccelLimitUncloakedDEF = 15000.f;
	FwdAccelLimitUncloaked = FwdAccelLimitUncloakedDEF;// FwdAccelLimitUncloakedDEF;
	FwdAccelLimitBoosted = 25000.f;
	HorAccelLimit = 9500.f;
	VerAccelLimit = 1500.f;
	TmpStoreAccelLimit = FwdAccelLimit;
	MinSpeed = 8000.0f;
	CurrentForwardSpeed = 8000.f;//set this to govern forward speed
	CurrentUpSpeed = 0.0f;
	CurrentRightSpeed = 0.0f;
	CurrentRollSpeed = 0;
	MaxSP = 500.f;
	CurrentSP = 490.f;
	InertialDamper = 0.0f;
	bIsCloaked = false;
	
	bFirstTarget = true;
	bDriftIsActive = false;
	bWantsToFirePrimary = false;
	bWantsToFireSecondary = false;
	bWantsToFireW1 = false;
	bWantsToFireW2 = false;
	bWantsToFireW3 = false;
	bWantsToFireW4 = false;
	bWantsToFireW5 = false;
	bWantsToFireW6 = false;
	bWantsToFireW7 = false;
	bWantsToFireW8 = false;
	RateOfFire = 0.2f;
	SelectedActionSlot = 1;
	BaseEyeHeight = 0.f;
	MuzzleOffset = FVector(500.f, 5.f, 4.f);
	bHasAttacked = false;
	bWantsToRoll = false;
	RollDegrees = 30.f;
	bPlayerHasTarget = false;
	WeakPointBound = 10.f;
	WeakPointSpeed = 0.5f;
	TotalYAxisVal = 0.f;
	TotalXAxisVal = 0.f;
	WeaponPrimary = CreateDefaultSubobject<UWeaponAC>(TEXT("WeaponSysP"));
	WeaponSecondary = CreateDefaultSubobject<UWeaponAC>(TEXT("WeaponSysS"));
	bIsShieldModeOn = false;
	bShouldShipMove = true;
	bIsVanished = false;

	//---3primary weapons to switch between
	Weapon1 = CreateDefaultSubobject<UWeaponAC>(TEXT("WeaponSysW1"));
	Weapon2 = CreateDefaultSubobject<UWeaponAC>(TEXT("WeaponSysW2"));
	Weapon3 = CreateDefaultSubobject<UWeaponAC>(TEXT("WeaponSysW3"));
	//---5 secondary weapons on the action bar
	Weapon4 = CreateDefaultSubobject<UWeaponAC>(TEXT("WeaponSysW4"));
	Weapon5 = CreateDefaultSubobject<UWeaponAC>(TEXT("WeaponSysW5"));
	Weapon6 = CreateDefaultSubobject<UWeaponAC>(TEXT("WeaponSysW6"));
	Weapon7 = CreateDefaultSubobject<UWeaponAC>(TEXT("WeaponSysW7"));
	Weapon8 = CreateDefaultSubobject<UWeaponAC>(TEXT("WeaponSysW8"));
	//-----------


	OrisonDefenseSys = CreateDefaultSubobject<UDefenseSysAC>(TEXT("DefensiveSystems"));
	bGCDActionSet = false;
	bGCDActionReady = false;
	GCDTurns = 0;

	ActiveWeapon = Weapon1;
	ActiveWeaponNum = 1;

	bIsBoostOn = false;
	bEnginePipIsOn = false;
	BoostMod = 2.f;//number for testing
	SlowMod = 0.2f;//number for testing
	BoostAccelLimitMod = 5;
	StoredVelocity = FVector(0.f, 0.f, 0.f);
	RicochetOffset = FVector(0.f, 0.f, 0.f);
	RollVal = 0.f;
	bSlowIsActive = false;
	BuffStartIndex = 5;
	bFirstTargetAhead = true;

	bIsRetreatActive = false;

	bIsFireModeOn = false;

	bIsMenuOpen = false;
	bAreBrakesApplied = false;
	CrystalWardMod=6.f;

	SappWardMod=6.f;

	JadeWardMod=2.f;

	MaxCP = 1000;
	CurrentCP = 1000;
	//----------------
	ShipTemp = 0.f;
	ShipMaxTemp = 100.f;
	MaxTempForStealth = 100.f;
	MaxTorps = 3;
	CurrentTorps = MaxTorps;
	bWantsToCloak = false;
	bIsDroneModOn = false;
	bIsPayloadModOn = false;
	bHasStealthed = false;
	bIsOverheated = false;
	
}
void AObjMainPawn::BeginPlay()
{	
	Super::BeginPlay();
	MaxStatusEffects = OrisonDefenseSys->GetMaxStatusEffects();
	for (int32 b = 0; b < MaxStatusEffects; b++)
	{
		StatusTicks.Add(0);

	}

	bShouldShipMove = false;
	//setting up the weapons: 1-3 are the primary, 4-8
	Weapon4->GenerateWeaponPreset(4);

}

void AObjMainPawn::Tick(float DeltaSeconds)
{
	if (!bIsMenuOpen&&bShouldShipMove)
	{

		// Calculate change in rotation this frame
		FRotator DeltaRotation(0, 0, 0);
		FRotator RollRotation(0, 0, 0);
		if (!bIsHarpoonModeOn)
		{
			if (!bDriftIsActive)
			{
				DeltaRotation.Pitch = -CurrentPitchSpeed * DeltaSeconds;//invert
				DeltaRotation.Yaw = CurrentYawSpeed * DeltaSeconds;
				DeltaRotation.Roll = CurrentRollSpeed * DeltaSeconds;
				AddActorLocalRotation(DeltaRotation);
			}
			else
			{
				DeltaRotation.Pitch = -CurrentPitchSpeed * DeltaSeconds;//invert
				DeltaRotation.Yaw = CurrentYawSpeed * DeltaSeconds;
				DeltaRotation.Roll = CurrentRollSpeed * DeltaSeconds;
				SpringArm->AddRelativeRotation(DeltaRotation);
				RollRotation.Roll = CurrentRollSpeed * DeltaSeconds;
				AddActorLocalRotation(RollRotation);
			}
		}

		else
		{
			if (DetectedTarget != NULL)
			{
				DeltaRotation = UKismetMathLibrary::FindLookAtRotation(this->GetActorLocation(), DetectedTarget->GetActorLocation());
			}

			FRotator RollRot = GetActorRotation();
			DeltaRotation.Roll = RollRot.Roll;
			SetActorRotation(DeltaRotation);
			FRotator AddRollRot = FRotator(0.f, 0.f, 0.f);
			AddRollRot.Roll = CurrentRollSpeed*DeltaSeconds;

			AddActorLocalRotation(AddRollRot);


		}

		RollVal = CurrentRollSpeed*DeltaSeconds;
		FVector LocalMove;
		if (bIsBoostOn)
		{
			ThrustForward(1.f);
			LocalMove = FVector(CurrentForwardSpeed * DeltaSeconds, CurrentRightSpeed * DeltaSeconds, CurrentUpSpeed * DeltaSeconds);
		}
		else if (bSlowIsActive)
		{
			LocalMove = FVector(CurrentForwardSpeed * SlowMod * DeltaSeconds, CurrentRightSpeed * SlowMod * DeltaSeconds, CurrentUpSpeed * SlowMod * DeltaSeconds);
		}
		else
		{
			if (CurrentForwardSpeed > FwdAccelLimit)
			{
				CurrentForwardSpeed = FwdAccelLimit;
			}

			LocalMove = FVector(CurrentForwardSpeed * DeltaSeconds, CurrentRightSpeed * DeltaSeconds, CurrentUpSpeed * DeltaSeconds);
		}

		
		AddActorLocalOffset(LocalMove, true);

	}
	
	Super::Tick(DeltaSeconds);
}

void AObjMainPawn::NotifyHit(class UPrimitiveComponent* MyComp, class AActor* Other, class UPrimitiveComponent* OtherComp, bool bSelfMoved, FVector HitLocation, FVector HitNormal, FVector NormalImpulse, const FHitResult& Hit)
{
	Super::NotifyHit(MyComp, Other, OtherComp, bSelfMoved, HitLocation, HitNormal, NormalImpulse, Hit);
}


int32 AObjMainPawn::PlTakeSimpDamage(int32 val)
{
	return (OrisonDefenseSys->TakeSimpleDamage(val));
}

bool AObjMainPawn::GetbDriftIsActive()
{
	return bDriftIsActive;
}
void AObjMainPawn::TogglebDriftIsActive()
{
	if (bDriftIsActive)
	{
		bDriftIsActive = true;

	}
	else
	{

		bDriftIsActive = true;
	}
}
float AObjMainPawn::GetDistanceToTarget()
{
	if (DetectedTarget!=nullptr)
	{
		float someFloat = DetectedTarget->GetDistanceToPlayer();
		return (someFloat);
	}
	else
	{
		return (-1.f);
	}
}


void AObjMainPawn::ThrustForward(float Val)
{
	if (bIsBoostOn)
	{
		FwdAccelLimit = FwdAccelLimitBoosted;
		FwdAcceleration = FwdAccelerationBoosted;

	}
	else if (bEnginePipIsOn)
	{
		FwdAccelLimit = 20000.f;
		FwdAcceleration = 20000.f;
	}
	else if (bIsCloaked)
	{
		FwdAcceleration = FwdAccelerationDEF;
		FwdAccelLimit = FwdAccelLimitDEF;
	}
	else
	{
		FwdAcceleration = FwdAccelerationDEF;
		FwdAccelLimit = FwdAccelLimitUncloaked;
	}
	bool bHasInput = !FMath::IsNearlyEqual(Val, 0.f);

	//}
	if (bHasInput)
	{
		float tmpDampener;
		if (bDriftIsActive)
		{
			tmpDampener = DriftForwardInertialDamper;
		}

		else
		{
			tmpDampener = ForwardInertialDamper;
		}


		float CurrentAcc = 0.f;
	if (bHasInput&&CurrentForwardSpeed <= FwdAccelLimit&&CurrentForwardSpeed >= -FwdAccelLimit)
		{
			CurrentAcc = Val*FwdAcceleration;
		}
		else if (CurrentForwardSpeed > FwdAccelLimit)
		{
			CurrentAcc = -0.9f*FwdAcceleration;
		}
		else
		{
			CurrentAcc = tmpDampener * FwdAcceleration;
		}

		float NewForwardSpeed;
		NewForwardSpeed = CurrentForwardSpeed + (GetWorld()->GetDeltaSeconds() * CurrentAcc);
		CurrentForwardSpeed = FMath::Clamp(NewForwardSpeed, MinSpeed, SpeedLimit);//CurrentForwardSpeed = FMath::Clamp(NewForwardSpeed, -SpeedLimit, SpeedLimit);
	}

}

void AObjMainPawn::ThrustUp(float Val)
{
	 bool bShipNearlyStationary = !FMath::IsNearlyEqual(CurrentUpSpeed, 0.f);
	 // Is there no input?
	 bool bHasInput = !FMath::IsNearlyEqual(Val, 0.f);
	 if (CurrentUpSpeed>-StopThreshold&&CurrentUpSpeed<StopThreshold&&!bHasInput)
	 {
		InertialDamper = 0.f;
		CurrentUpSpeed = 0.f;
	 }
	 else
	 {

		 InertialDamper = CalcInertialDamper(CurrentUpSpeed, 0.6f);
		// If input is not held down, reduce speed
		 float CurrentAcc = 0.f;
		 if (bHasInput&&CurrentUpSpeed <= VerAccelLimit&&CurrentUpSpeed>=-VerAccelLimit&&!bIsBoostOn)
		 {
			 CurrentAcc = Val*VerAcceleration;
		 }
		 else
		 {
			 CurrentAcc = InertialDamper * VerAcceleration;
		 }
		float NewUpSpeed = CurrentUpSpeed + (GetWorld()->GetDeltaSeconds() * CurrentAcc);

		CurrentUpSpeed = FMath::Clamp(NewUpSpeed, -SpeedLimit, SpeedLimit);
		float WeakPointYMovement = Val*WeakPointSpeed;
		
		if ((FMath::Abs(TotalYAxisVal) < WeakPointBound)
			|| ((TotalYAxisVal >= WeakPointBound) && (Val <= 0))
			|| ((TotalYAxisVal <= (-WeakPointBound)) && (Val>0)))
		{
			const FVector WeakPointMove = FVector(0.f, 0.f, WeakPointYMovement);//need delta seconds.

			WeakPoint->AddLocalOffset(WeakPointMove, true);
			TotalYAxisVal += WeakPointYMovement;
		}

	}


}
void AObjMainPawn::ThrustRight(float Val)
{

	bool bShipNearlyStationary = !FMath::IsNearlyEqual(CurrentUpSpeed, 0.f);
	bool bHasInput = !FMath::IsNearlyEqual(Val, 0.f);
	if (CurrentRightSpeed>-StopThreshold && CurrentRightSpeed<StopThreshold && !bHasInput)
	{
		InertialDamper = 0.f;
		CurrentRightSpeed = 0.f;
	}
	else
	{
		InertialDamper = CalcInertialDamper(CurrentRightSpeed, 0.6f);
		// If input is not held down, reduce speed
		float CurrentAcc = 0.f;
		if (bHasInput&&CurrentRightSpeed <= HorAccelLimit&&CurrentRightSpeed >= -HorAccelLimit&&!bIsBoostOn)
		{
			CurrentAcc = Val*HorAcceleration;

		}
		else
		{
			CurrentAcc = InertialDamper * HorAcceleration;
		}

		// Calculate new speed
		float NewRightSpeed = CurrentRightSpeed + (GetWorld()->GetDeltaSeconds() * CurrentAcc);
		
		CurrentRightSpeed = FMath::Clamp(NewRightSpeed, -SpeedLimit, SpeedLimit);

	}

		float WeakPointXMovement = Val*WeakPointSpeed;

	if ((FMath::Abs(TotalXAxisVal) < WeakPointBound)
		|| ((TotalXAxisVal >= WeakPointBound) && (Val <= 0))
		|| ((TotalXAxisVal <= (-WeakPointBound))&&(Val>0)))
	{
		TotalXAxisVal += WeakPointXMovement;
		const FVector WeakPointMove = FVector(0.f, WeakPointXMovement, 0.f);//need delta seconds.
		WeakPoint->AddLocalOffset(WeakPointMove, true);
	}

}
void AObjMainPawn::PitchUp(float Val)
{
	if (bIsBoostOn)
	{
		YawFwdSpdMod = 0.1f;
	}
	else
	{
		PitchFwdSpdMod = 0.8f - (CurrentForwardSpeed / FwdAccelLimitDEF);//using the value DEF which is uncloaked and unboost, the idea is that you maneuver well when cloaked, slower when uncloaked, slowest when boosted
		if (PitchFwdSpdMod < 0.2f)
		{
			PitchFwdSpdMod = 0.2f;
		}
	}
	float TargetPitchSpeed;
	if (bDriftIsActive)
	{
		TargetPitchSpeed = (Val * (PitchSpeed*4));//player is focused on hub and should be slowed in rotation ability to keep him roughly lined up
	}
	else
	{
		// Target pitch speed is based in input
		TargetPitchSpeed = (Val * PitchSpeed*PitchFwdSpdMod);
	}
	if (bIsBoostOn)
	{
		TargetPitchSpeed = TargetPitchSpeed/4.f;
	}
	else if (bSlowIsActive)
	{
	}

	// When steering, we decrease pitch slightly
	TargetPitchSpeed += (FMath::Abs(CurrentYawSpeed) * -0.2f);

	// Smoothly interpolate to target pitch speed
	CurrentPitchSpeed = FMath::FInterpTo(CurrentPitchSpeed, TargetPitchSpeed, GetWorld()->GetDeltaSeconds(), 2.f);
	
	
}

void AObjMainPawn::YawRight(float Val)
{
	//Target yaw speed is based on input
	float TargetYawSpeed;
	if (bIsBoostOn)
	{
		YawFwdSpdMod = 0.1f;
	}
	else
	{
		YawFwdSpdMod = 0.8f - (CurrentForwardSpeed / FwdAccelLimitDEF);
		if (YawFwdSpdMod < 0.2f)
		{
			YawFwdSpdMod = 0.2f;
		}
	}

	if (bDriftIsActive)
	{
		TargetYawSpeed = (Val*(YawSpeed*4));
	}
	else
	{
		TargetYawSpeed = (Val * YawSpeed*YawFwdSpdMod);
	}

	if (bIsBoostOn)
	{
		TargetYawSpeed = TargetYawSpeed / 4.f;/
	}
	else if (bSlowIsActive)
	{

	}

	CurrentYawSpeed = FMath::FInterpTo(CurrentYawSpeed, TargetYawSpeed, GetWorld()->GetDeltaSeconds(), 2.f);
	// Is there any left/right input?
	const bool bIsTurning = FMath::Abs(Val) > 0.2f;

	// If turning, yaw value is used to influence roll
	// If not turning, roll to reverse current roll value
	float TargetRollSpeed = 0.f;
	if (bIsTurning)
	{
		TargetRollSpeed = CurrentYawSpeed * 0.5f;
	}
}

void AObjMainPawn::RollRight(float Val)
{

	// When steering, we decrease pitch slightly
	float TargetRollSpeed = (Val * RollSpeed);

	if (bIsBoostOn)
	{
		TargetRollSpeed = (Val * 0.2f*RollSpeed);
	}
	else if (bSlowIsActive)
	{
		TargetRollSpeed = (Val * 2.f*RollSpeed);
	}

	// Smoothly interpolate to target yaw speed
	CurrentRollSpeed = FMath::FInterpTo(CurrentRollSpeed, TargetRollSpeed, GetWorld()->GetDeltaSeconds(), 2.f);

}

void AObjMainPawn::DiscreteRollRight()
{
	bWantsToRoll = true;
}
bool AObjMainPawn::FireModeIsActive()
{
	return bIsFireModeOn;
}


void AObjMainPawn::StartTargetAhead()
{
	//Ray trace from camera, if we hit targetable class, have it hilight itself etc.
	if (Controller != NULL)
	{
		FCollisionQueryParams RV_TraceParams = FCollisionQueryParams(FName(TEXT("RV_Trace")), true, this);
		RV_TraceParams.bTraceComplex = true;
		RV_TraceParams.bTraceAsyncScene = true;
		RV_TraceParams.bReturnPhysicalMaterial = false;
		FVector CamLoc;
		FRotator CamRot;


		Controller->GetPlayerViewPoint(CamLoc, CamRot);
		FHitResult RV_Hit(ForceInit);
		FVector Start = GetActorLocation();
		FVector Direc = CamRot.Vector();

		FVector StartPoint = Start + (Direc * 6000);//start the sphere trace ahead by roughly its radius to avoid hitting actors to your side, behind you etc.  Exact location being tested
		FVector EndPoint = Start + (Direc * 1000000);//End = Start + Direc * 2000; //FVector(10.0f, 10.0f, 20.0f);
												   //call GetWorld() from within an actor extending class
		FQuat someQuat;
		
		someQuat = CamRot.Quaternion();
		GetWorld()->SweepSingleByChannel(
			RV_Hit,        //result
			StartPoint,    
			EndPoint, //end
			someQuat,
			ECC_Pawn, //collision channel
			FCollisionShape::MakeSphere(100.f),
			RV_TraceParams
			);
		ATargetable* ActiveTarget = Cast<ATargetable>(RV_Hit.GetActor());

		if (ActiveTarget&&ActiveTarget->GetCanTarget()&&!ActiveTarget->IsPendingKill() )
		{

			if (bPlayerHasTarget)
			{

				if (DetectedTarget != NULL)
				{
					DetectedTarget->EndHilight();
				}

				ActiveTarget->StartHilight();
			}
			else
			{
				DetectedTarget = ActiveTarget;
				if (DetectedTarget != NULL)
				{

					DetectedTarget->StartHilight();
				}
				bPlayerHasTarget = true;
			}

			DetectedTarget = ActiveTarget;

			StartLockOn();
		}
		
		if (bFirstTargetAhead)
		{
			//moved to tick to see how it plays if target ahead is always happening.  GetWorldTimerManager().SetTimer(TargetAheadTimer, this, &AObjMainPawn::StartTargetAhead, 0.8f, true);
			bFirstTargetAhead = false;
		}
		//
	}

}
void AObjMainPawn::EndTargetAhead()
{

	bFirstTargetAhead = true;
	EndPrimaryFire();
	EndLockOn();

	if (DetectedTarget != nullptr)
	{
		DetectedTarget->EndHilight();
	}
	DetectedTarget = nullptr;

	//--
	
}
void AObjMainPawn::StartPrimaryFire()
{
	bIsFireModeOn = true;
	bWantsToFirePrimary = true;
	SelectedActionSlot = 1;
	FirePrimary();
	GetWorldTimerManager().SetTimer(PFireTimer, this, &AObjMainPawn::FirePrimary, 0.4f, true);

}

void AObjMainPawn::EndPrimaryFire()
{
	bIsFireModeOn = false;
	bWantsToFirePrimary = false;
	GetWorldTimerManager().ClearTimer(PFireTimer);

}

bool AObjMainPawn::RemoveStatus(int32 TmpIndex)
{
	/*-------------------------------------------------
	This is the fundamental counterpart to Apply Status and the two must exist in every actor handling the status effect: the rules
	are not held in an external class, struct, etc.  This may change in time.  When this function is finished it should be as though
	no status was ever applied, being mindful of stacking logic and possible exceptions.
	--------------------------------------------------*/
	bool bReturn=true;
	bUpdateHotbarHUD = true;
	if (TmpIndex >= 0 && TmpIndex<MaxStatusEffects)
	{
		switch (OrisonDefenseSys->GetStatus(TmpIndex))
		{

		case EStatusEnum::StatE_Mesmerize:
			//Take off corrode modifiers, make bp call if needed
			OrisonDefenseSys->RemoveStatus(TmpIndex);
			FwdAccelLimit = FwdAccelLimitDEF;

			break;
		case EStatusEnum::StatE_Slow:
			//Take off corrode modifiers, make bp call if needed
			OrisonDefenseSys->RemoveStatus(TmpIndex);
			FwdAccelLimit = FwdAccelLimitDEF;
			FwdAccelLimitUncloaked = FwdAccelLimitUncloakedDEF;
			break;
		case EStatusEnum::StatE_Root:
			//Take off corrode modifiers, make bp call if needed
			OrisonDefenseSys->RemoveStatus(TmpIndex);
			FwdAccelLimit = FwdAccelLimitDEF;
			UE_LOG(LogTemp, Warning, TEXT("root removed"));
			break;
		case EStatusEnum::StatE_Sleep:
			//Take off corrode modifiers, make bp call if needed
			OrisonDefenseSys->RemoveStatus(TmpIndex);
			bIsOverheated = false;
			break;
		case EStatusEnum::StatE_Corrode:
			//Take off corrode modifiers, make bp call if needed
			OrisonDefenseSys->RemoveStatus(TmpIndex);
			FwdAccelLimit = FwdAccelLimitDEF;
			UE_LOG(LogTemp, Warning, TEXT("corrode removed"));
			break;
		case EStatusEnum::StatE_DampenField:
			//Take off corrode modifiers, make bp call if needed
			OrisonDefenseSys->RemoveStatus(TmpIndex);
			FwdAccelLimit = FwdAccelLimitDEF;
			UE_LOG(LogTemp, Warning, TEXT("dampen removed"));
			break;
		case EStatusEnum::StatE_Boost:
			//Take off corrode modifiers, make bp call if needed
			OrisonDefenseSys->RemoveStatus(TmpIndex);
			FwdAccelLimit = FwdAccelLimitDEF;
			UE_LOG(LogTemp, Warning, TEXT("boost removed"));
			break;
		case EStatusEnum::StatE_Focus:
			//Take off corrode modifiers, make bp call if needed
			OrisonDefenseSys->RemoveStatus(TmpIndex);
			FwdAccelLimit = FwdAccelLimitDEF;
			UE_LOG(LogTemp, Warning, TEXT("focus removed"));
			break;

		default:
			bReturn = false;
			break;
		}
		return (bReturn);
	}
	else
	{
		return (false);
	}

}

float AObjMainPawn::AW_MaxCloseRange()
{
	if (ActiveWeapon)
	{
		return (ActiveWeapon->MaxCloseRange());
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Error: AW_MaxRange found no active weapon"));
		return (-1.f);
	}
}
float AObjMainPawn::AW_MaxMidRange()
{
	if (ActiveWeapon)
	{
		return (ActiveWeapon->MaxMidRange());
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Error: AW_MaxRange found no active weapon"));
		return (-1.f);
	}
}
float AObjMainPawn::AW_MaxLongRange()
{
	if (ActiveWeapon)
	{
		return (ActiveWeapon->MaxLongRange());
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Error: AW_MaxRange found no active weapon"));
		return (-1.f);
	}
}

bool AObjMainPawn::HasAttacked()
{
	return bHasAttacked;
}

int32 AObjMainPawn::GetGCDTicks()
{
	return (GCDTurns);
}

int32 AObjMainPawn::HandleGCDTick()
{
	for (int32 i = 0; i < MaxStatusEffects; i++)
	{
		if (StatusTicks[i] > 1)
		{
			StatusTicks[i]--;
		}
		else
		{
			
			if (OrisonDefenseSys->GetStatus(i)!=EStatusEnum::StatE_None)
			{
				StatusTicks[i] = 0;
				if (RemoveStatus(i))
				{
					UE_LOG(LogTemp, Warning, TEXT("HandleGCDTick function successfully removed status"));
				}
				else
				{
					UE_LOG(LogTemp, Warning, TEXT("Error: unable to remove status"));
				}
			}
			
		}
	}

	return (GCDTurns++);
}

bool  AObjMainPawn::WeaponIsReady() 
{
	if (bGCDActionReady && bGCDActionSet)
	{
		return (true);
	}
	else
	{
		return (false);
	}
}
void AObjMainPawn::SetBoost(bool tmp)
{
	bIsBoostOn = tmp;
}
bool AObjMainPawn::GetBoost()
{
	return(bIsBoostOn);
}
void AObjMainPawn::StartLockOn()
{
	

}

void AObjMainPawn::EndLockOn()
{
	bIsLockOnActive = false;
	
}

bool AObjMainPawn::IsLockOnActive()
{
	return (bIsLockOnActive);
}


void AObjMainPawn::SetLockOnActive(bool bTmp)
{
	bIsLockOnActive = bTmp;
}


bool AObjMainPawn::SimpleAddStatus(EStatusEnum TmpStatus, bool bIsBuff)
{

	if (!bIsBuff)//debuffs are in the first section of the list
	{
		for (int32 i = 0; i < BuffStartIndex; i++)
		{
			if (GetStatus(i) == EStatusEnum::StatE_None|| GetStatus(i)==TmpStatus)//if status effect is already applied, refesh it.
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
	bUpdateHotbarHUD = true;
}
bool AObjMainPawn::ApplyStatus(EStatusEnum TmpStatus, int32 TmpIndex, bool bAlreadyActive)
{
	/*----------------------------------------------
	Status effect rules are set here.  Since there are fundamental differences when applying the status to player, 
	specific npc types, etc, status is not held in a class or actor component; at least not for now.
	Effects include logic for stacking or not, number of ticks to apply status, temporary changes in variables etc
	to be reset when RemoveStatus is called on it.
	-----------------------------------------------*/
	bool bReturn=true;
	
	if (TmpIndex >= 0 && TmpIndex < MaxStatusEffects)
	{
		switch (TmpStatus)
		{
		case EStatusEnum::StatE_Mesmerize:
			//Apply slow status modifers, call any relevant bps and check stack logic
			if (!bAlreadyActive)//check against stack limit of 1(for sake of testing)
			{
				FwdAccelLimit = 1000.f;// /= 4;//TESTING
			}
			StatusTicks[TmpIndex] = 16;//careful of zero index, -1
			break;
		case EStatusEnum::StatE_Slow:
			//Apply slow status modifers, call any relevant bps and check stack logic
			if (!bAlreadyActive)//check against stack limit of 1(for sake of testing)
			{
				FwdAccelLimitUncloaked = 1000.f;//TESTING
				FwdAccelLimit = 1000.f;

			}
			StatusTicks[TmpIndex] = 8;//careful of zero index, -1
			break;
		case EStatusEnum::StatE_Root:
			//Apply slow status modifers, call any relevant bps and check stack logic
			if (!bAlreadyActive)//check against stack limit of 1(for sake of testing)
			{
				FwdAccelLimit /= 6;//TESTING
			}
			StatusTicks[TmpIndex] = 5;//careful of zero index, -1
			break;
		case EStatusEnum::StatE_Sleep:
			//Apply slow status modifers, call any relevant bps and check stack logic - UPDATE: hijacking this to use as overheat for primary laser
			if (!bAlreadyActive)//check against stack limit of 1(for sake of testing)
			{
				bIsOverheated = true;
			}
			StatusTicks[TmpIndex] = 6;//careful of zero index, -1
			break;
		case EStatusEnum::StatE_Corrode:
			//Apply slow status modifers, call any relevant bps and check stack logic
			if (!bAlreadyActive)//check against stack limit of 1(for sake of testing)
			{
				FwdAccelLimit = 3500.f;// /= 4;//TESTING
			}
			StatusTicks[TmpIndex] = 12;//careful of zero index, -1
			break;
		case EStatusEnum::StatE_DampenField:
			//Apply slow status modifers, call any relevant bps and check stack logic
			if (!bAlreadyActive)//check against stack limit of 1(for sake of testing)
			{
				FwdAccelLimit = 6000.;// /= 4;//TESTING
			}
			StatusTicks[TmpIndex] = 6;//careful of zero index, -1
			break;
		case EStatusEnum::StatE_Boost:
			//Apply slow status modifers, call any relevant bps and check stack logic
			if (!bAlreadyActive)//check against stack limit of 1(for sake of testing)
			{
				FwdAccelLimit *= 2;//testing
			}
			StatusTicks[TmpIndex] = 8;

			break;
		case EStatusEnum::StatE_Regenerate:
			//Apply slow status modifers, call any relevant bps and check stack logic
			if (!bAlreadyActive)//check against stack limit of 1(for sake of testing)
			{

			}
			StatusTicks[TmpIndex] = 8;
			break;
		case EStatusEnum::StatE_Focus://temp acting as vanish

			StatusTicks[TmpIndex] = 10;
			break;
		case EStatusEnum::StatE_Agility:
			//Apply slow status modifers, call any relevant bps and check stack logic
			if (!bAlreadyActive)//check against stack limit of 1(for sake of testing)
			{
				FwdAccelLimit = 11000.f;// *= 2;//testing
			}
			StatusTicks[TmpIndex] = 11;
			break;
		default:
			bReturn = false;
			break;
		}
		return bReturn;
	}
	else
	{
		return false;
	}
	bUpdateHotbarHUD = true;
	//check against max stacks
	//do status stuff.
}

EStatusEnum AObjMainPawn::GetStatus(int32 TmpIndex)
{
	if (TmpIndex < 0 && TmpIndex >= MaxStatusEffects)
	{
		return (EStatusEnum::StatE_None);
	}
	else
	{
		return (OrisonDefenseSys->GetStatus(TmpIndex));
	}
}
EStatusEnum AObjMainPawn::GetTargStatus(int32 TmpIndex)
{
	if (TmpIndex < 0 && TmpIndex >= MaxStatusEffects)
	{
		return (EStatusEnum::StatE_None);
	}
	else if (DetectedTarget == NULL)
	{
		return (EStatusEnum::StatE_None);
	}
	else
	{
		return (DetectedTarget->GetStatus(TmpIndex));//target's defenseac's getstatus (OrisonDefenseSys->GetStatus(TmpIndex));
	}
}


bool AObjMainPawn::RetreatIsActive()
{
	return bIsRetreatActive;
}

float AObjMainPawn::GetWardMod(EAttunementEnum TmpAtt)
{
	if (TmpAtt == EAttunementEnum::AE_Crystal)
	{
		return CrystalWardMod;
	}
	else if (TmpAtt == EAttunementEnum::AE_Jade)
	{
		return JadeWardMod;
	}
	else if (TmpAtt == EAttunementEnum::AE_Sapphire)
	{
		return SappWardMod;
	}
	else
	{
		return -1.f;
	}
}


float AObjMainPawn::GetWeaponMaxRange(int32 tmpWeaponNum)
{
	float WeapRange = -1.f;
	switch (tmpWeaponNum)
	{
		case 1:
			WeapRange = 100000.f;
			break;
		case 2:
			WeapRange = 90000.f;
			break;
		case 3:
			WeapRange = 80000.f;
			break;
		case 4:
			WeapRange = 70000.f;
			break;
		case 5:
			WeapRange = 60000.f;
			break;
		case 6:
			WeapRange = 50000.f;
			break;
		case 7:
			WeapRange = 40000.f;
			break;
		case 8:
			WeapRange = 30000.f;
			break;
		default:
			break;
	}
	return WeapRange;
}

bool AObjMainPawn::IsShielded() 
{
	if (CurrentForwardSpeed >= FwdAccelLimitDEF)
	{
		return true;
	}
	else
	{
		return false;
	}
}
void AObjMainPawn::SetWantsToCloak(bool bTmp)
{
	bWantsToCloak = bTmp;
	bUpdateHotbarHUD = true;
}

bool AObjMainPawn::GetWantsToCloak()
{
	return bWantsToCloak;
	bUpdateHotbarHUD = true;
}
bool AObjMainPawn::GetPayloadMod()
{
	return bIsPayloadModOn;
	
}
bool AObjMainPawn::GetDroneMod()
{
	return bIsDroneModOn;
	
}
bool AObjMainPawn::GetHasStealthed()
{
	return bHasStealthed;
}

bool AObjMainPawn::GetIsOverheated()
{
	return bIsOverheated;
}