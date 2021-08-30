// EXAMPLE code
#pragma once

#include "GameFramework/Pawn.h"
#include "DefenseSysAC.h"
#include "WeaponAC.h"
#include "Targetable.generated.h"

UCLASS()
class ObjMAIN_API ATargetable : public APawn
{
	GENERATED_BODY()
public:

	UFUNCTION(BlueprintImplementableEvent)
		bool StartHilight();

	UFUNCTION(BlueprintImplementableEvent)
		bool EndHilight();/

	// Sets default values for this pawn's properties
	ATargetable();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable, Category = "Action")
		float TakeSimpDamage(float val);

	UFUNCTION(BlueprintCallable, Category = "Defenses")
	float GetTargCurrentSP();
	UFUNCTION(BlueprintCallable, Category = "Defenses")
	float GetTargMaxSP();
	UFUNCTION(BlueprintCallable, Category = "Defenses")
	void TargDmgSP(float Val);


	UFUNCTION(BlueprintCallable, Category = "Defenses")
	float GetTargCurrentFP();
	UFUNCTION(BlueprintCallable, Category = "Defenses")
	float GetTargMaxFP();

	UFUNCTION(BlueprintCallable, Category = "Defenses")
	float GetTargCurrentHP();
	UFUNCTION(BlueprintCallable, Category = "Defenses")
	float GetTargMaxHP();

	UFUNCTION(BlueprintCallable, Category = "Defenses")
	void TargDmgHP(float Val);

	UFUNCTION(BlueprintCallable, Category = "Defenses")
	float GetDistanceToPlayer();

	UFUNCTION(BlueprintCallable, Category = "Status")
		bool GetIsCorroded();

	UFUNCTION(BlueprintCallable, Category = "Status")
		bool GetIsDampened();

	UFUNCTION(BlueprintCallable, Category = "Status")
		bool GetIsMesmerized();

	UFUNCTION(BlueprintCallable, Category = "Defenses")
	/** The minimum distance the NPC wants to be from the player.  returns false if the value is out of possible ranges*/
	bool SetMinDesiredRange(float val);

	UFUNCTION(BlueprintCallable, Category = "Defenses")
		/** The maxumum distance the NPC wants to be from the player.  Logically this hsould be the same or less than the longest effective range for attack.*/
	bool SetMaxDesiredRange(float val);

	UFUNCTION(BlueprintCallable, Category = "Defenses")
	/** The minimum distance the NPC wants to be from the player.  returns false if the value is out of possible ranges*/
	float GetMinDesiredRange();

	UFUNCTION(BlueprintCallable, Category = "Defenses")
	float GetMaxDesiredRange();
	UFUNCTION(BlueprintCallable, Category = "Weapons")
	//aw not really necessary, this is the maximum possible range, weapon should not fire if player is farther than this.
	float GetAWMaxRange();
	UFUNCTION(BlueprintCallable, Category = "Weapons")
	//aw not really necessary, this is the falloff value
	float GetAWFalloff();
	UFUNCTION(BlueprintCallable, Category = "Weapons")
	float GetAWMaxOptimal();

	UFUNCTION(BlueprintCallable, Category = "AI")
	/** */
	void BecomeAwareOfPlayer();

	UFUNCTION(BlueprintCallable, Category = "AI")
		/** */
		void BecomeUnwareOfPlayer();

	UFUNCTION(BlueprintCallable, Category = "AI")
	/**  */
	bool GetAwarenessOfPlayer();

	UFUNCTION(BlueprintCallable, Category = "AI")
		/**  */
	bool WithinWeaponRangeToPl();

	UFUNCTION(BlueprintCallable, Category = "Target")
	/**Returns true if this actor is ready to be targeted, false if not  */
	bool GetCanTarget();

	UFUNCTION(BlueprintCallable, Category = "Target")
	/** sets the status of bCanBeTargeted */
	void SetCanTarget(bool bCanTarget);
	//STATUS STUFF
	//--------------------------
	EStatusEnum GetStatus(int32 TmpIndex);


	UFUNCTION(BlueprintCallable, Category = "Status")
	/* Add a status effect and return true if successful - DOES NOT check if it is a buff/debuff - must ensure categorization elsewhere such as SimpleAddStatus*/
	bool AddStatus(EStatusEnum TmpStatus, int32 TmpIndex, bool bIsBuff);

	UFUNCTION(BlueprintCallable, Category = "Status")
	/* adds status to the first available slot - returns false if there's no room - Buffs are reserved from BuffStartIndex to MaxStatusEffects-1*/
	bool SimpleAddStatus(EStatusEnum TmpStatus, bool bIsBuff);

	UFUNCTION(BlueprintCallable, Category = "Status")
	/* Applies TmpStatus effects indicated in this function every tick
	- If a single status is called multiple  times, the logic here applies stacks if applicable.
	returns true if the status will be applied next tick and false if not
	@ is needed to apply StatusTicks[someindex] in the same place as everything else is applied
	bAlreadyActive: true if status is already on and just needs to refresh, if newly applied, should be false*/
	bool ApplyStatus(EStatusEnum TmpStatus, int32 TmpIndex, bool bAlreadyActive);

	UFUNCTION(BlueprintCallable, Category = "Status")
	/*sets TmpIndex status to None*/
	bool RemoveStatus(int32 TmpIndex);

	UFUNCTION(BlueprintCallable, Category = "Status")
	/*Returns the time left on the given index or 0 if timer is up or -1 if something is wrong*/
	int32 GetStatusTicksRemaining(int32 TmpIndex);
	//-----------TICKS
	UFUNCTION(BlueprintCallable, Category = "GCD")
	/** Returns ticks incremented since last player gcd-bound action */
	int32 GetGCDTicks();

	UFUNCTION(BlueprintCallable, Category = "GCD")
		/** Sets GCDTicks to NewTicks param */
		void SetGCDTicks(int32 NewTicks);

	UFUNCTION(BlueprintCallable, Category = "GCD")
	/*Listener for when GamemodeBP sends event tick dispatcher - readies weapon currently*/
	int32 HandleGCDTick();

	UFUNCTION(BlueprintCallable, Category = "GCD")

		bool SelectPreset(int32 ShipPreset);

	UFUNCTION(BlueprintCallable, Category = "Status")
		/* Returns status at index TmpIndex or none for out of range*/
		EStatusEnum GetNPCStatus(int32 TmpIndex);

protected:
	UDefenseSysAC *TargDefenseSys;
	UWeaponAC *TargWeapon1;
	UFUNCTION(BlueprintCallable, Category = "Defenses")
	void SetTargCurrentSP(float Val);

	UFUNCTION(BlueprintCallable, Category = "Defenses")
		void SetTargCurrentHP(float Val);

	UFUNCTION(BlueprintCallable, Category = "Defenses")
		void SetTargCurrentFP(float Val);

	UFUNCTION(BlueprintCallable, Category = "Defenses")
	void SetTargMaxSP(float Val);

	TArray<int32> StatusTicks;
	//----------TICK STUFF
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cooldown")

		FTimerHandle GCDTimer;
	//time on the GCDTimer in seconds.


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cooldown")
		/** Ticks since last GCD-bound action */
		int32 GCDTicks;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cooldown")
		/*player has input a GCD related action - GCD may not have ticked yet*/
		bool bGCDActionSet;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cooldown")
		/*GCD action is set and GCD has ticked - use at will*/
		bool bGCDActionReady;
private:

	UPROPERTY(VisibleAnywhere, Category = "SP")
	float CurrentSP;

	UPROPERTY(VisibleAnywhere, Category = "SP")
	float MaxSP;


	UPROPERTY(VisibleAnywhere, Category = "test")

	int32 TestNum;

	UPROPERTY(VisibleAnywhere, Category = "Status")
	bool bIsStunned;
	UPROPERTY(VisibleAnywhere, Category = "Status")
		bool bIsMesmerized;
	UPROPERTY(VisibleAnywhere, Category = "Status")
		bool bIsCorroded;
	UPROPERTY(VisibleAnywhere, Category = "Status")
		bool bIsDampened;

	UPROPERTY(VisibleAnywhere, Category = "DistanceToPlayer")
	float DistanceToPlayer;

	UPROPERTY(VisibleAnywhere, Category = "DistanceToPlayer")
	float MinDesiredRange;

	UPROPERTY(VisibleAnywhere, Category = "DistanceToPlayer")
	float MaxDesiredRange;

	UPROPERTY(VisibleAnywhere, Category = "SP")
	bool bIsAwareOfPlayer;
	
	UPROPERTY(VisibleAnywhere, Category = "Terget")
	/*Player should only target this npc if this is true. false when killed to avoid crashing due to a reference to a destroyed actor*/
	bool bCanBeTargeted;

	UPROPERTY(Category = "Status", EditAnywhere)
	int32 MaxStatusEffects;

	UPROPERTY(Category = "Status", EditAnywhere)
	//This index onward reserved for buffs which benefit the actor. 0 to this index are debuffs which disadvantage the actor.
	int32 BuffStartIndex;
	
};
