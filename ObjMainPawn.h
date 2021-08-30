// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.
#pragma once
#include "GameFramework/Pawn.h"
#include "ProjectileBase.h"
#include "DefenseSysAC.h"
#include "WeaponAC.h"
#include "ObjMainPawn.generated.h"

UCLASS(config=Game)
class AObjMainPawn : public APawn
{
	GENERATED_BODY()

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	/** StaticMesh component that will be the visuals for our flying pawn */
	UPROPERTY(Category = Mesh, VisibleDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class UStaticMeshComponent* OrisonMesh;


	/** StaticMesh component that will be the visuals for our flying pawn */
	UPROPERTY(Category = Mesh, VisibleDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class UStaticMeshComponent* WeakPoint;

	/** StaticMesh component that will be the visuals for our flying pawn */
	UPROPERTY(Category = Mesh, VisibleDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class UStaticMeshComponent* HellBall;

	/** Spring arm that will offset the camera */
	UPROPERTY(Category = Camera, VisibleDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* SpringArm;

	/** Camera component that will be our viewpoint */
	UPROPERTY(Category = Camera, VisibleDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* Camera;
public:

	AObjMainPawn();

	// Called when the game starts or when spawned
	//virtual void BeginPlay() override;

	// Begin AActor overrides
	virtual void Tick(float DeltaSeconds) override;
	virtual void NotifyHit(class UPrimitiveComponent* MyComp, class AActor* Other, class UPrimitiveComponent* OtherComp, bool bSelfMoved, FVector HitLocation, FVector HitNormal, FVector NormalImpulse, const FHitResult& Hit) override;
	// End AActor overrides

	// Begin APawn overrides
	virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override; // Allows binding actions/axes to functions
	// End APawn overrides

	UFUNCTION(BlueprintCallable, Category = "Action")
		/** Take SmpDmg point for point from outer>inner, field>shield>hull.  returns 0 if all damage has been dealt and the ship lives, or >0 as overkill points if ship has reached the point where it shoud be destroyed.*/
		int32 PlTakeSimpDamage(int32 val);



	UFUNCTION(BlueprintNativeEvent, Category = "Action")
	/** Calls skill bound to action slot 1 - Delete this when action slot system is functional */
	void UseActionSlot1();

	UFUNCTION(BlueprintCallable, Category = "Action")
	void UseActionSlot(int32 TmpActionSlot);


	/** Bound to the thrust axis */
	void ThrustForward(float Val);

	UFUNCTION(BlueprintCallable, Category = "Acceleration")
	/** Bound to the brake axis */
	void Brakes(float Val);//-currently not being used APR 2017
	UFUNCTION(BlueprintCallable, Category = "Acceleration")
		/** instantly sets forward speed to min */
	void SetToMinSpeed();
	//UFUNCTION(BlueprintCallable, Category = "Acceleration")
	/** Bound to the brake axis */
	//void EndBrakes();

	UFUNCTION(BlueprintCallable, Category = "Acceleration")
	/** start slow-to-optimal mode, your ship's forward speed decreases to the speed at which turn rates are optimal */
	void StartSlow();

	UFUNCTION(BlueprintCallable, Category = "Acceleration")
	/** ends slow-to-optimal mode */
	void EndSlow();

	/** Bound to the thrust axis */
	void ThrustUp(float Val);

	/** Bound to the thrust axis */
	void ThrustRight(float Val);

	/** Bound to the vertical axis */
	void PitchUp(float Val);

	/** Bound to the horizontal axis */
	void YawRight(float Val);

	/** roll right */
	void RollRight(float Val);

	UFUNCTION(BlueprintCallable, Category = "Orison")
	/** Gain a level and return new level number or -1 if there is a problem.  CURRENTLY bare bones, needs xp etc added in*/
	int32 LvlUp();

	UFUNCTION(BlueprintCallable, Category = "Weapons")
	void NextAttunement();

	UFUNCTION(BlueprintCallable, Category = "Weapons")
	void PreviousAttunement();

	UFUNCTION(BlueprintCallable, Category = "Weapons")
	/** Rather than making this a dynamic function, I have them pre-built per attunement for easily calling with a button click*/
	void SetAttunementCrystal();


	UFUNCTION(BlueprintCallable, Category = "Weapons")
		/**Make weapon1 the active weapon*/
		void SwitchToWeapon1();

	UFUNCTION(BlueprintCallable, Category = "Weapons")
		/**Make weapon1 the active weapon*/
		void SwitchToWeapon2();

	UFUNCTION(BlueprintCallable, Category = "Weapons")
		/**Make weapon1 the active weapon*/
		void SwitchToWeapon3();


	UFUNCTION(BlueprintCallable, Category = "HUD")
	/** true when hotbar needs to update*/
	void SetUpdateHotbarHUD(bool tmp);
	UFUNCTION(BlueprintCallable, Category = "Command")
		/** */
		bool GetDroneMod();
	
	UFUNCTION(BlueprintCallable, Category = "Stealth")
		/** */
		bool GetHasStealthed();
	UFUNCTION(BlueprintCallable, Category = "Thermal")
		/** */
		bool GetIsOverheated();


	UFUNCTION(BlueprintCallable, Category = "Command")
		/***/
		bool GetPayloadMod();
	UFUNCTION(BlueprintCallable, Category = "HUD")
	/** true when hotbar needs to update*/
	bool GetUpdateHotbarHUD();

	UFUNCTION(BlueprintCallable, Category = "HUD")
	/** get bIsCloaked*/
	bool GetCloakStatus();

	UFUNCTION(BlueprintCallable, Category = "HUD")
	/** set bIsCloaked*/
	void SetCloakStatus(bool tmp);

	UFUNCTION(BlueprintCallable, Category = "HUD")
	/** get bAreBrakesApplied*/
	bool GetBrakesApplied();

	UFUNCTION(BlueprintCallable, Category = "Weapons")
	void SetAttunementSapphire();

	UFUNCTION(BlueprintCallable, Category = "Weapons")
	void SetAttunementJade();


	UFUNCTION(BlueprintCallable, Category = "Weapons")
	EAttunementEnum GetAttunement();


	UFUNCTION(BlueprintCallable, Category = "Stealth")
	bool HasAttacked();

	UFUNCTION(BlueprintCallable, Category = "Movement")
	bool GetbDriftIsActive();
	UFUNCTION(BlueprintCallable, Category = "Acceleration")
	bool GetSlowIsActive();
	UFUNCTION(BlueprintCallable, Category = "Weapons")
		float GetLaserMaxRange();

	UFUNCTION(BlueprintCallable, Category = "Weapons")
		float GetCannonMaxRange();

	UFUNCTION(BlueprintCallable, Category = "Weapons")
		float GetTorpedoMaxRange();
	UFUNCTION(BlueprintCallable, Category = "Weapons")
		/** Returns number of torpedoes the player's vessel currently has ready to fire*/
		int32 GetCurrentTorps();

	UFUNCTION(BlueprintCallable, Category = "Weapons")
		/** sets number of torpedoes the player's vessel currently has ready to fire to tmpTorps*/
		void SetCurrentTorps(int32 tmpTorps);

	UFUNCTION(BlueprintCallable, Category = "Movement")
	void TogglebDriftIsActive();

	UFUNCTION(BlueprintCallable, Category = "Target")
		int32 GetTargetCurrentSP();

	UFUNCTION(BlueprintCallable, Category = "Target")
		int32 GetTargetMaxSP();

	UFUNCTION(BlueprintCallable, Category = "Defense")
		void AddSP(float tmpSP);

	UFUNCTION(BlueprintCallable, Category = "Target")
		int32 GetTargetCurrentFP();

	UFUNCTION(BlueprintCallable, Category = "Target")
		int32 GetTargetMaxFP();

	UFUNCTION(BlueprintCallable, Category = "Target")
		int32 GetTargetCurrentHP();

	UFUNCTION(BlueprintCallable, Category = "Target")
		int32 GetTargetMaxHP();

	UFUNCTION(BlueprintCallable, Category = "UI")
		bool IsMenuOpen();

	UFUNCTION(BlueprintCallable, Category = "UI")
		void SetMenuOpen(bool tmp);

	UFUNCTION(BlueprintCallable, Category = "Target")
	/*Sets bIsBooostOn*/
	void SetBoost(bool tmp);

	UFUNCTION(BlueprintCallable, Category = "Target")
		/*gets bIsBooostOn*/
		bool GetBoost();

	UFUNCTION(BlueprintCallable, Category = "Target")
	/*lock on is a complex action DESCRIBE: */
	void StartLockOn();

	UFUNCTION(BlueprintCallable, Category = "Target")
	/*lock on is a complex action DESCRIBE: */
	void EndLockOn();

	UFUNCTION(BlueprintCallable, Category = "Orison")
	float PW_CalcDmg();

	
	UFUNCTION(BlueprintCallable, Category = "Orison")
		/**Primary weapon does not have actions it has modes - these still need to be built - APR 20 2017
		returns true if weapon mode has successfully changed or kept the same, false if there's a problem
		@TmpMode - 1-mode1, 2-mode2 etc*/
	bool PW_ChangeWeaponMode(int32 TmpMode);



	UFUNCTION(BlueprintCallable, Category = "Orison")
	int32 GetXP();
	UFUNCTION(BlueprintCallable, Category = "Orison")
	int32 GetLvl();
	UFUNCTION(BlueprintCallable, Category = "Orison")
	void GetWeaponStats();//-currently not being used APR 2017

	UFUNCTION(BlueprintCallable, Category = "Weapons")
		/** Returns the primary weapona attunement, which is also the entire ship's attunement, since they are always the same for this game's design*/
	EAttunementEnum GetWPAttunement();

	UFUNCTION(BlueprintCallable, Category = "Orison")
		int32 GetCurrentSP();

	UFUNCTION(BlueprintCallable, Category = "Orison")
		int32 GetMaxSP();

	UFUNCTION(BlueprintCallable, Category = "Orison")
	void DmgSP(int32 Val);

	UFUNCTION(BlueprintCallable, Category = "Orison")
		void IncreaseSP(int32 Val);

	UFUNCTION(BlueprintCallable, Category = "Orison")
		int32 GetCurrentFP();

	UFUNCTION(BlueprintCallable, Category = "Orison")
		int32 GetMaxFP();

	UFUNCTION(BlueprintCallable, Category = "Orison")
		void DmgFP(int32 Val);

	UFUNCTION(BlueprintCallable, Category = "Orison")
		int32 GetCurrentHP();

	UFUNCTION(BlueprintCallable, Category = "Orison")
		int32 GetMaxHP();

	UFUNCTION(BlueprintCallable, Category = "Orison")
		float GetDistanceToTarget();

	UFUNCTION(BlueprintCallable, Category = "Orison")
	void DmgHP(int32 Val);

	UFUNCTION(BlueprintCallable, Category = "Orison")
		float GetCurrentEP();

	UFUNCTION(BlueprintCallable, Category = "Orison")
	AActor* GetDetectedTarget();
	
	UFUNCTION(BlueprintCallable, Category = "Orison")
	AActor* GetCoreTarget();
	
	UFUNCTION(BlueprintCallable, Category = "target")
	/** Sets the pointer CoreTarget to the core in the map - assumes exactly one core on map.  Returns true when found or false if something went wrong.*/
	bool SetCoreTarget(ATargetable* CoreTarg);


	//--chant points are spent on secondary fire actions and charged mostly through primary fire/Ship vials
	UFUNCTION(BlueprintCallable, Category = "Chant")
	int32 GetCurrentCP();

	UFUNCTION(BlueprintCallable, Category = "Chant")
	int32 GetMaxCP();

	UFUNCTION(BlueprintCallable, Category = "Chant")
		void SetCurrentCP(int32 TmpCP);

	UFUNCTION(BlueprintCallable, Category = "Chant")
		void SetMaxCP(int32 TmpCP);

	UFUNCTION(BlueprintCallable, Category = "Orison")
	void ActivateWeapon(int32 WeaponNumber);
	//--

	UFUNCTION(BlueprintCallable, Category = "Orison")
	/** Gets the active wepaon's base damage */
		int32 AW_CalcDmg();

	UFUNCTION(BlueprintCallable, Category = "Weapon")
	/** Returns the max range at which an attack will critical strike %100 of the time*/
	float AW_MaxCloseRange();

	UFUNCTION(BlueprintCallable, Category = "Weapon")
	/** Returns the max range at which an attack will Glance %50 of the time*/
	float AW_MaxMidRange();

	UFUNCTION(BlueprintCallable, Category = "Weapon")
	/** Returns the max range at which an attack will not miss %>0 of the time*/
	float AW_MaxLongRange();

	UFUNCTION(BlueprintCallable, Category = "Orison")
	/** Gets the secondary wepaon's base damage
	note - used to be AW if oyu ever see references to it, its switched to SW for Secondary weapon and repurposed, switching between active weapons is no longer a thing*/
	EActionEnum SW_GetAction();

	UFUNCTION(BlueprintCallable, Category = "Orison")
	/** Gets the secondary wepaon's base damage
	note - used to be AW if oyu ever see references to it, its switched to SW for Secondary weapon and repurposed, switching between active weapons is no longer a thing*/
	bool SW_SetAction(EActionEnum ActionForQueue);

	UFUNCTION(BlueprintCallable, Category = "Action")
	/** starts firing at a predermined rate when user holds down fire button*/
	void StartPrimaryFire();

	UFUNCTION(BlueprintCallable, Category = "Action")
		/** ends firing at a predermined rate when user holds down fire button */
		void EndPrimaryFire();

	UFUNCTION(BlueprintCallable, Category = "Action")
		/** starts firing at a predermined rate when user holds down fire button*/
		void StartCannonFire();

	UFUNCTION(BlueprintCallable, Category = "Action")
		/** ends firing at a predermined rate when user holds down fire button */
		void EndCannonFire();
	UFUNCTION(BlueprintCallable, Category = "Action")
		/** Modifying button which does no action on its own but is combined wiht other keys to select payload to fire with next seconday fire*/
		void StartPayloadMod();

	UFUNCTION(BlueprintCallable, Category = "Action")
		/**ends modifying input   */
		void EndPayloadMod();
	UFUNCTION(BlueprintCallable, Category = "Action")
		/** Modifying button which does no action on its own but is combined wiht other keys to select drone command*/
		void StartDroneMod();

	UFUNCTION(BlueprintCallable, Category = "Action")
		/** ends modifying input */
		void EndDroneMod();



	UFUNCTION(BlueprintNativeEvent, Category = "Engine")
	/** Start engine boost */
	void StartBoost();

	UFUNCTION(BlueprintCallable, Category = "Engine")
	void StartBrakes();

	UFUNCTION(BlueprintCallable, Category = "Engine")
	void EndBrakes();
	UFUNCTION(BlueprintNativeEvent, Category = "Engine")
	/** Retreat back x meters quickly */
	void Retreat();

	UFUNCTION(BlueprintNativeEvent, Category = "Engine")
	/** End engine boost */
	void EndBoost();

	UFUNCTION(BlueprintNativeEvent, Category = "Engine")
	/** BP related tasks to switch to fire mode */
	void StartFireMode();

	UFUNCTION(BlueprintNativeEvent, Category = "ShieldMode")
	/** MAY 2017 - replacing fire mode for testing, if I like it, there will only be a shield mode modifier and normal, no fire mode tied into firing.  BP related tasks to switch to shield mode */
	void StartShieldMode();

	UFUNCTION(BlueprintNativeEvent, Category = "ShieldMode")
		/** BP related tasks to switch to shield mode */
		void EndShieldMode();

	UFUNCTION(BlueprintCallable, Category = "Defenses")
		/* returns wheither the ship is in a shielded state, where it takes half damage.*/
		bool IsShielded();



	UFUNCTION(BlueprintCallable, Category = "Action")
	/** called by event weapon fire 1-8, needs to be in fire mode, then takes care of queueing action*/
	bool QueueAction(int TmpSlot);

	UFUNCTION(BlueprintCallable, Category = "Action")
	/** Calls skill bound to action slot 1 - EXPAND AND ADD STANCES */
	void StartW1Fire();

	UFUNCTION(BlueprintCallable, Category = "Action")
	/** Calls skill bound to action slot 1 - EXPAND AND ADD STANCES */
	void EndW1Fire();

	UFUNCTION(BlueprintCallable, Category = "Action")
		/** Calls skill bound to action slot 1 - EXPAND AND ADD STANCES */
		void StartW2Fire();

	UFUNCTION(BlueprintCallable, Category = "Action")
		/** Calls skill bound to action slot 1 - EXPAND AND ADD STANCES */
		void EndW2Fire();

	UFUNCTION(BlueprintCallable, Category = "Action")
		/** Calls skill bound to action slot 1 - EXPAND AND ADD STANCES */
		void StartW3Fire();

	UFUNCTION(BlueprintCallable, Category = "Action")
		/** Calls skill bound to action slot 1 - EXPAND AND ADD STANCES */
		void EndW3Fire();

	UFUNCTION(BlueprintCallable, Category = "Action")
		/** Calls skill bound to action slot 1 - EXPAND AND ADD STANCES */
		void StartW4Fire();

	UFUNCTION(BlueprintCallable, Category = "Action")
		/** Calls skill bound to action slot 1 - EXPAND AND ADD STANCES */
		void EndW4Fire();

	UFUNCTION(BlueprintCallable, Category = "Action")
		/** Calls skill bound to action slot 1 - EXPAND AND ADD STANCES */
		void StartW5Fire();

	UFUNCTION(BlueprintCallable, Category = "Action")
		/** Calls skill bound to action slot 1 - EXPAND AND ADD STANCES */
		void EndW5Fire();

	UFUNCTION(BlueprintCallable, Category = "Action")
		/** Calls skill bound to action slot 1 - EXPAND AND ADD STANCES */
		void StartW6Fire();

	UFUNCTION(BlueprintCallable, Category = "Action")
		/** Calls skill bound to action slot 1 - EXPAND AND ADD STANCES */
		void EndW6Fire();

	UFUNCTION(BlueprintCallable, Category = "Action")
		/** Calls skill bound to action slot 1 - EXPAND AND ADD STANCES */
		void StartW7Fire();

	UFUNCTION(BlueprintCallable, Category = "Action")
		/** Calls skill bound to action slot 1 - EXPAND AND ADD STANCES */
		void EndW7Fire();

	UFUNCTION(BlueprintCallable, Category = "Action")
		/** Calls skill bound to action slot 1 - EXPAND AND ADD STANCES */
		void StartW8Fire();

	UFUNCTION(BlueprintCallable, Category = "Action")
		/** Calls skill bound to action slot 1 - EXPAND AND ADD STANCES */
		void EndW8Fire();

	UFUNCTION(BlueprintNativeEvent, Category = "Menu")
	/** Open pause screen, for testing simply resets level */
	void PauseGame();

	UFUNCTION(BlueprintNativeEvent, Category = "Action")
	/** While active, camera focuses toward the hub/boss */
	void StartDrift();

	UFUNCTION(BlueprintNativeEvent, Category = "Action")
	/** While inactive, camera is in free look NOTE may not be necessary if player doesn't hold down button.  Need to see which feels better.*/
	void EndDrift();
	/** Returns CurrentUpSpeed (z-axis) pos = moving up, neg = moving down */
	UFUNCTION(BlueprintCallable, Category = "Movement")
	float GetUpSpeed();


	UFUNCTION(BlueprintCallable, Category = "Action")
	/** Returns true if weapon is ready to fire */
	bool WeaponIsReady();


	UFUNCTION(BlueprintCallable, Category = "GCD")
	/** Returns ticks incremented since last player gcd-bound action */
	int32 GetGCDTicks();

	UFUNCTION(BlueprintCallable, Category = "GCD")
	/*Listener for when GamemodeBP sends event tick dispatcher - readies weapon currently*/
	int32 HandleGCDTick();

	/** Returns CurrentRightSpeed (Y-axis), pos for right, neg for left */
	UFUNCTION(BlueprintCallable, Category = "Movement")
	float GetRightSpeed();

	/** Returns CurrentForwardSpeed (x-axis) pos = moving forward, neg = moving in reverse */
	UFUNCTION(BlueprintCallable, Category = "Movement")
	float GetForwardSpeed();


	/** Fire resonator, used for all attacks. */
	UFUNCTION(BlueprintNativeEvent, Category = "Action")
	void FirePrimary();

	/** Fire cannon */
	UFUNCTION(BlueprintNativeEvent, Category = "Action")
		void FireCannon();

	/** Fire torpedo if ammo available. */
	UFUNCTION(BlueprintNativeEvent, Category = "Action")
		void FireTorpedo();

	/** Fire resonator, used for all attacks. */
	UFUNCTION(BlueprintNativeEvent, Category = "Action")
	void UseSlot1();

	/** Fire resonator, used for all attacks. */
	UFUNCTION(BlueprintNativeEvent, Category = "Action")
	void UseSlot2();

	/** Fire resonator, used for all attacks. */
	UFUNCTION(BlueprintNativeEvent, Category = "Action")
	void UseSlot3();


	UFUNCTION(BlueprintNativeEvent, Category = "Action")
		void StopUsingSlot3();

	/** Fire resonator, used for all attacks. */
	UFUNCTION(BlueprintNativeEvent, Category = "Action")
	void UseSlot4();

	/** Fire resonator, used for all attacks. */

	UFUNCTION(BlueprintNativeEvent, Category = "Action")
	void UseSlot5();

	/** Fire resonator, used for all attacks. */
	UFUNCTION(BlueprintNativeEvent, Category = "Action")
	void UseSlot6();

	/** Fire resonator, used for all attacks. */
	UFUNCTION(BlueprintNativeEvent, Category = "Action")
	void UseSlot7();

	/** Fire resonator, used for all attacks. */
	UFUNCTION(BlueprintNativeEvent, Category = "Action")
	void UseSlot8();
	UFUNCTION(BlueprintCallable, Category = "Action")
	bool IsThereATargetAhead();

	UFUNCTION(BlueprintCallable, Category = "Action")
	bool RetreatIsActive();

	UFUNCTION(BlueprintCallable, Category = "Action")
	void SetRetreatStatus(bool bTmp);



	UFUNCTION(BlueprintCallable, Category = "Action")
	bool IsLockOnActive();

	UFUNCTION(BlueprintCallable, Category = "Action")
	void SetLockOnActive(bool bTmp);

	/** Gun muzzle's offset from the camera location */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Resonator")
	FVector MuzzleOffset;
	UFUNCTION(BlueprintCallable, Category = "Target")
	void StartTargetAhead();
	UFUNCTION(BlueprintCallable, Category = "Target")
	void EndTargetAhead();

	UFUNCTION(BlueprintCallable, Category = "Target")//DELETME? functionality replaced
	void CanTarget();

	UFUNCTION(BlueprintCallable, Category = "Weapons")
	void GCDFinished();

	UFUNCTION(BlueprintCallable, Category = "Status")
	/* Add a status effect and return true if successful - DOES NOT check if it is a buff/debuff - must ensure categorization elsewhere such as SimpleAddStatus*/
	bool AddStatus(EStatusEnum TmpStatus, int32 TmpIndex, bool bIsBuff);

	UFUNCTION(BlueprintCallable, Category = "Status")
	/* adds status to the first available slot - returns false if there's no room - Buffs are reserved from BuffStartIndex to MaxStatusEffects-1*/
	bool SimpleAddStatus(EStatusEnum TmpStatus, bool bIsBuff);

	UFUNCTION(BlueprintCallable, Category = "Status")

	bool ApplyStatus(EStatusEnum TmpStatus, int32 TmpIndex, bool bAlreadyActive);
TmpIndex);

	UFUNCTION(BlueprintCallable, Category = "Status")
	/*sets TmpIndex status to None*/
	bool RemoveStatus(int32 TmpIndex);

	UFUNCTION(BlueprintCallable, Category = "Status")
		/*Player is actively firing, lowering defenses and having a variety of effects for "fire mode" as opposed to "shield mode" which is on by default and always on when not firing*/
		bool FireModeIsActive();

	UFUNCTION(BlueprintCallable, Category = "ShiledMode")
		/*Player is actively firing, lowering defenses and having a variety of effects for "fire mode" as opposed to "shield mode" which is on by default and always on when not firing*/
		bool ShieldModeIsOn();

	UFUNCTION(BlueprintCallable, Category = "ShieldMode")
		/*Player is actively firing, lowering defenses and having a variety of effects for "fire mode" as opposed to "shield mode" which is on by default and always on when not firing*/
		void SetShieldModeOn(bool bTmp);


	UFUNCTION(BlueprintCallable, Category = "Status")
	/*Returns the time left on the given index or 0 if timer is up or -1 if something is wrong*/
	int32 GetStatusTicksRemaining(int32 TmpIndex);

	UFUNCTION(BlueprintCallable, Category = "Status")
	/*Returns the time left on the given index for the target or 0 if timer is up or -1 if something is wrong*/
	int32 GetTargStatusTicksRemaining(int32 TmpIndex);

	UFUNCTION(BlueprintCallable, Category = "Status")
	/* Returns status at index TmpIndex or none for out of range*/
	EStatusEnum GetStatus(int32 TmpIndex);

	UFUNCTION(BlueprintCallable, Category = "Status")
	/* Returns current target status at index TmpIndex or none for out of range or no current target*/
	EStatusEnum GetTargStatus(int32 TmpIndex);

	UFUNCTION(BlueprintCallable, Category = "Ward")
	/* Returns the  ward modifier which reduced damage taken by x(rawdmg)/WardMod
	@TmpAtt: the attunement whose modifier should be returned*/
	float GetWardMod(EAttunementEnum TmpAtt);

	UFUNCTION(BlueprintCallable, Category = "Movement")
	bool ShouldShipMove();

	UFUNCTION(BlueprintCallable, Category = "cloak")
		/*Returns bIsVanished*/
		bool GetVanishStatus();

	UFUNCTION(BlueprintCallable, Category = "cloak")
		/*sets bIsVanished*/
		void SetVanishStatus(bool bVanish);


	UFUNCTION(BlueprintCallable, Category = "Movement")
		void SetShouldShipMove(bool bTmp);

	UFUNCTION(BlueprintCallable, Category = "Weapons")
		/*Returns which of your weapons is active: 1, 2, or 3*/
		int32 GetActiveWeaponNum();

	UFUNCTION(BlueprintCallable, Category = "Weapons")
		/*Returns max range of weapon1...weapon8 1...8*/
		float GetWeaponMaxRange(int32 tmpWeaponNum);
	UFUNCTION(BlueprintCallable, Category = "Thermal")
		bool SetShipTemp(float temp);

	UFUNCTION(BlueprintCallable, Category = "Thermal")
		bool SetShipMaxTemp(float temp);
	UFUNCTION(BlueprintCallable, Category = "Thermal")
		float GetShipTemp();
	UFUNCTION(BlueprintCallable, Category = "Thermal")
		float GetShipMaxTemp();
	UFUNCTION(BlueprintCallable, Category = "Thermal")
		float GetMaxTempForStealth();
	UFUNCTION(BlueprintCallable, Category = "Thermal")
		bool SetMaxTempForStealth(float tmp);
	UFUNCTION(BlueprintCallable, Category = "cloak")
		void SetWantsToCloak(bool bTmp);
	UFUNCTION(BlueprintCallable, Category = "cloak")
		bool GetWantsToCloak();

protected:
	FTimerHandle TargetAheadTimer;//TODO: Try and get these into an array
	FTimerHandle PFireTimer;//TODO: Try and get these into an array
	FTimerHandle CannonFireTimer;
	FTimerHandle W1FireTimer;
	FTimerHandle W2FireTimer;
	FTimerHandle W3FireTimer;
	FTimerHandle W4FireTimer;
	FTimerHandle W5FireTimer;
	FTimerHandle W6FireTimer;
	FTimerHandle W7FireTimer;
	FTimerHandle W8FireTimer;
	FTimerHandle CanTargetTimer;
	//currently working on this
	FTimerHandle Status1Timer;
	UPROPERTY(EditAnywhere, Category = "Timer")
	/*Each index holds the number of ticks remaining on the associated status slot, or 0 if inactive*/
	TArray<int32> StatusTicks;

	UPROPERTY(EditAnywhere, Category = "Timer")
	/*An array holding timers associated with status slots using the same index*/
	//TArray<FTimerHandle> StatusTimers;
	//Global cooldown timer, time after one action (excluding primary fire) before another one can be triggered
	FTimerHandle GCDTimer;
	//time on the GCDTimer in seconds.

	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cooldown")
	/** turns since last GCD-bound action */
	int32 GCDTurns;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cooldown")

	float RollVal;

	

	void DiscreteRollRight();

	

	float CalcInertialDamper(float CurSpeed, float DampenStrenght);

	/*not set up yet, will be where raycast is launched from*/
	class ATargetable* GetTargetInView();

	/*not set up yet, should be forever right now*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gameplay")
	float MaxUseDistance;

	bool bHasNewFocus;
	bool bSlowIsActive;
	bool bFirstTarget;
	bool bPlayerHasTarget;
	
	bool bIsFireModeOn;
	bool bIsOverheated;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cooldown")
	/*player has input a GCD related action - GCD may not have ticked yet*/
	bool bGCDActionSet;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cooldown")
	/*GCD action is set and GCD has ticked - use at will*/
	bool bGCDActionReady;

	ATargetable* DetectedTarget;
	ATargetable* CoreTarget;
	/** Projectile class to spawn */
	UPROPERTY(EditAnywhere, Category = "Projectile")
	TSubclassOf<class AActor> ProjectileClass;
	UDefenseSysAC *OrisonDefenseSys;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pips")
		/*true if player has used her stealth (1 per encounter)*/
		bool bHasStealthed;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pips")
		/*true if player has used her stealth (1 per encounter)*/
		bool bEnginePipIsOn;
	//xmax 17 - thesea re all that will ever be used now.
	UWeaponAC *ActiveWeapon;//this will change to hold whatever weapon is needed
	UWeaponAC *Weapon1;
	UWeaponAC *Weapon2;
	UWeaponAC *Weapon3;
	//////////////////////////////
	int32 ActiveWeaponNum;//must be 1, 2 or 3

	UWeaponAC *Weapon4;
	UWeaponAC *Weapon5;
	UWeaponAC *Weapon6;
	UWeaponAC *Weapon7;
	UWeaponAC *Weapon8;

private:

	/** How quickly forward speed changes NOTE: move these to ship movement component DELETEME? Not currently used */
	UPROPERTY(Category="Acceleration", EditAnywhere)
	float FwdAcceleration;
	/** How effective the brakes are at reducing forward speed as a deceleration value*/
	UPROPERTY(Category = "Acceleration", EditAnywhere)
	float FwdBrakeDecel;

	UPROPERTY(Category = "Acceleration", EditAnywhere)
	float HorAcceleration;

	UPROPERTY(Category = "Acceleration", EditAnywhere)
	float VerAcceleration;

	UPROPERTY(Category = "Acceleration", EditAnywhere)
	/** Modifier for yaw speed (yaw rate) - the slower you go, the faster you yaw*/
	float YawFwdSpdMod;

	UPROPERTY(Category = "Acceleration", EditAnywhere)
	/** Modifier for pitch speed - the slower you go, the faster you pitch*/
	float PitchFwdSpdMod;

	UPROPERTY(Category = "Acceleration", EditAnywhere)
		/** Modifier for roll speed - the slower you go, the faster you roll*/
		float RollFwdSpdMod;


	UPROPERTY(Category = "Status", EditAnywhere)
	int32 MaxStatusEffects;

	UPROPERTY(Category = "Status", EditAnywhere)
	//This index onward reserved for buffs which benefit the actor. 0 to this index are debuffs which disadvantage the actor.
	int32 BuffStartIndex;

	UPROPERTY(Category = "Plane", EditAnywhere)
	float UpThrusterAcc;

	UPROPERTY(Category = "Plane", EditAnywhere)
	float RightThrusterAcc;
	/** How quickly pawn can steer */
	UPROPERTY(Category="Plane", EditAnywhere)
	float PitchSpeed;
	UPROPERTY(Category = "Plane", EditAnywhere)
	float YawSpeed;
	
	//UPROPERTY(Category = "Plane", EditAnywhere)
	float RollSpeed;

	/** Player ship cannot move faster than this under any circumstances */
	UPROPERTY(Category = "movement", EditAnywhere)
	float SpeedLimit;

	/** Max forward speed */
	UPROPERTY(Category = "movement", EditAnywhere)
	float FwdAccelLimit;
	
	UPROPERTY(Category = "movement", EditAnywhere)
	/** Max forward speed default value - look up CONST CORRECT stuff later*/
	float FwdAccelLimitDEF;

	/** Max forward speed out of cloak*/
	UPROPERTY(Category = "movement", EditAnywhere)
		float FwdAccelLimitUncloaked;
	UPROPERTY(Category = "movement", EditAnywhere)
		/** max fwd uncloaked speed defined*/
		float FwdAccelLimitUncloakedDEF;
	UPROPERTY(Category = "movement", EditAnywhere)
	float HorAccelLimit;

	UPROPERTY(Category = "movement", EditAnywhere)
	float VerAccelLimit;

	UPROPERTY(Category = "movement", EditAnywhere)
	bool bIsBoostOn;

	UPROPERTY(Category = "command", EditAnywhere)
		bool bIsDroneModOn;
	UPROPERTY(Category = "command", EditAnywhere)
		bool bIsPayloadModOn;

	UPROPERTY(Category = "weapon", EditAnywhere)
	bool bIsLockOnActive;
	UPROPERTY(Category = "movement", EditAnywhere)
	/*Modifier to be multiplied to accelerationwhen boost is active*/
	float BoostMod;

	UPROPERTY(Category = "movement", EditAnywhere)
	/*Modifier to be multiplied to accelerationwhen slow is active*/
	float SlowMod;

	UPROPERTY(Category = "movement", EditAnywhere)
	/*Modifier to be multiplied to acceleration limit when boost is active*/
	float BoostAccelLimitMod;

	UPROPERTY(Category = "movement", EditAnywhere)
	float HarpoonModeAccelLimit;//stores the increased max speed in harpoon mode

	UPROPERTY(Category = "movement", EditAnywhere)
	float HarpoonModeAcceleration;//stores the increased acceleration in harpoon mode

	UPROPERTY(Category = "movement", EditAnywhere)
	float TmpStoreAccelLimit;//stores the value of normal max speed when entering harpoon mode, to return to once the mode is over

	UPROPERTY(Category = "movement", EditAnywhere)
	float TmpStoreAcceleration;//stores the value of normal acceleration when entering harpoon mode, to return to once the mode is over
	
	UPROPERTY(Category = "movement", EditAnywhere)
	bool bIsHarpoonModeOn;

	/** Min forward speed */
	UPROPERTY(Category="movement", EditAnywhere)
	float MinSpeed;

	/** Min forward speed */
	UPROPERTY(Category = "movement", EditAnywhere)
	float CamFollowDistance;

	/** Current forward speed */
	float CurrentForwardSpeed;

	/** Accel limit when boosted */
	float FwdAccelLimitBoosted;


	/** Accel limit when boosted */
	float FwdAccelerationBoosted;

	/** Accel limit when boosted */
	float FwdAccelerationDEF;


	/** Current forward speed */
	float CurrentUpSpeed;
	/** Current forward speed */
	float CurrentRightSpeed;
	/** Current yaw speed */
	float CurrentYawSpeed;

	/** speed below which Orison is brought to a stop by having her speed set to zero */
	float StopThreshold;

	/** Current pitch speed */
	float CurrentPitchSpeed;

	/** Current roll speed */
	float CurrentRollSpeed;

	float CurrentSP;

	float MaxSP;

	/** Decrease in movement speed in the absense of thrust*/
	float InertialDamper;

	/** Decrease in movement speed in the absense of thrust, specifically when forward acceleration is not active*/
	float ForwardInertialDamper;

	/** Decrease in movement speed in the absense of thrust, specifically when forward acceleration is not active*/
	float DriftForwardInertialDamper;

	/** A condition required for firing sequence to begin*/
	bool bWantsToFirePrimary;

	/** A condition required for firing sequence to begin*/
	bool bWantsToFireSecondary;

	/** A condition required for firing sequence to begin.  Weapon 1 means action slot 1; Primary is different, call that one weapon 0 if you like*/
	bool bWantsToFireW1;

	/** A condition required for firing sequence to begin*/
	bool bWantsToFireW2;

	/** A condition required for firing sequence to begin*/
	bool bWantsToFireW3;

	/** A condition required for firing sequence to begin*/
	bool bWantsToFireW4;

	/** A condition required for firing sequence to begin*/
	bool bWantsToFireW5;

	/** A condition required for firing sequence to begin*/
	bool bWantsToFireW6;

	/** A condition required for firing sequence to begin*/
	bool bWantsToFireW7;

	/** A condition required for firing sequence to begin*/
	bool bWantsToFireW8;

	/** Wheither player has ever attacked or otherwise attracted the attnetion of the NPCs */
	bool bHasAttacked;

	/** Time in seconds between resonator firing*/
	float RateOfFire;

	/**Is shield mode on (hold down shieldmode button for this)*/
	bool bIsShieldModeOn;

	/**While out of combat for x seconds, player becomes cloaked, providing much greater top speed and recharging ship systems. striking an npc or getting to close turns it off, and it will automatically turn back on after x seconds or certain player actions such as flying beneath asteroids*/
	bool bIsCloaked;

	/*player may not be cloaked, but shoould try to cloak*/
	bool bWantsToCloak;

	/** A temp holding the action slot number used for firing and other actions.  -1=not set/error 1 to action slot limit = valid*/
	int32 SelectedActionSlot;

	bool bDriftIsActive; //while active, free look is very limited, game camera should hold the hub/boss in view. Experimentation will determine how strongly this is in place.

	bool bWantsToRoll;
	float RollDegrees;
	float WeakPointSpeed;
	float WeakPointBound; //A running tally of Weakpoint movement cannot exceed the absolute value of this bounds on both the x and y axis - in other words, weakpoint starts at 0 and will not move below -WeakPointBounds or above WeakPointBounds on X and Y resulting in a square in fron of the camera.
	float TotalYAxisVal;
	float TotalXAxisVal;
	FVector StoredVelocity;
	FVector RicochetOffset;
	//FRotator DefaultSpringArmRot; may need for coding cam centering later.
	UPROPERTY(Category = "movement", EditAnywhere)
	/** True the first time StartTargetAhead is called when the player holds down targetahead button - used to set the recursive timer without reseting it each time*/
	bool bFirstTargetAhead;
	bool bIsRetreatActive;
	bool bIsMenuOpen;//MAY1 2017- this is the correct bool for controlling menu, older one(s) were being weird I just started fresh.

	bool bUpdateHotbarHUD;//True when hotbar on hud bp needs to change.

	/** raw damage is divided by this if the attack is amplified crystal burst and the current defenseive attunement is crystal*/
	UPROPERTY(Category = "ward", EditAnywhere)
	float CrystalWardMod;

	/** Maximum number of torpedoes which can be stored on player's vessel*/
	UPROPERTY(Category = "weapons", EditAnywhere)
		int32 MaxTorps;

	/** current number of torpedoes which can be stored on player's vessel*/
	UPROPERTY(Category = "weapons", EditAnywhere)
		int32 CurrentTorps;

	/** raw damage is divided by this if the attack is amplified crystal burst and the current defenseive attunement is crystal*/
	UPROPERTY(Category = "ward", EditAnywhere)
		float SappWardMod;

	/** raw damage is divided by this if the attack is amplified crystal burst and the current defenseive attunement is crystal*/
	UPROPERTY(Category = "ward", EditAnywhere)
		float JadeWardMod;

	UPROPERTY(Category = "Chant", EditAnywhere)
	float CurrentCP;

	/** Max player Chant Points*/
	UPROPERTY(Category = "Chant", EditAnywhere)
	float MaxCP;
	//---------------------------------------

	/** Should this ship move at all*/
	UPROPERTY(Category = "movement", EditAnywhere)
	bool bShouldShipMove;
	UPROPERTY(Category = "movement", EditAnywhere)
	bool bAreBrakesApplied;

	/** Current heat stored in player's vessel*/
	UPROPERTY(Category = "Thermal", EditAnywhere)
		float ShipTemp;

	/** Overheating beyoind this point will automatically expel heat at an equal rate, safely below the point of damaging the vessel*/
	UPROPERTY(Category = "Thermal", EditAnywhere)
		float ShipMaxTemp;

	/** Heating beyond this point makes cloaking impossible*/
	UPROPERTY(Category = "Thermal", EditAnywhere)
		float MaxTempForStealth;

	UPROPERTY(Category = "Cloak", EditAnywhere)
		/*vanished is an active status that allows you to be undetected at any range as long as you don't fire. distinct from cloaked, a passive
		which kicked in when outside certain range.  It is limited in time and shows as an active effect*/
		bool bIsVanished;


public:
	/** Returns PlaneMesh subobject **/
	FORCEINLINE class UStaticMeshComponent* GetOrisonMesh() const { return OrisonMesh; } 
	/** Returns PlaneMesh subobject **/
	FORCEINLINE class UStaticMeshComponent* GetWeakPoint() const { return WeakPoint; }
	/** Returns PlaneMesh subobject **/
	FORCEINLINE class UStaticMeshComponent* GetHellBall() const { return HellBall; }
	/** Returns SpringArm subobject **/
	FORCEINLINE class USpringArmComponent* GetSpringArm() const { return SpringArm; }
	/** Returns Camera subobject **/
	FORCEINLINE class UCameraComponent* GetCamera() const { return Camera; }
};
