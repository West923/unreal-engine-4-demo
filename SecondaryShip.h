#pragma once

#include "Targetable.h"
#include "SecondaryShip.generated.h"

UCLASS()
class ObjMAIN_API ASecondaryShip : public ATargetable
{
	GENERATED_BODY()


	/** StaticMesh component that will be the visuals for our flying pawn */
	UPROPERTY(Category = Mesh, VisibleDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class UStaticMeshComponent* XMesh;

public:
	ASecondaryShip();

	virtual void BeginPlay() override;


	UFUNCTION(BlueprintNativeEvent, Category = "Action")
	/** Calls skill bound to action slot 1 - EXPAND AND ADD STANCES */
	void UseActionSlot1();


	/** roll right */
	void RollRight(float Val);

	UFUNCTION(BlueprintCallable, Category = "Shield")
	float GetSPRatio();

	UFUNCTION(BlueprintCallable, Category = "Shield")
	float DmgSP(float tmpDmg);

	UFUNCTION(BlueprintNativeEvent, Category = "Action")
	/** Primary fire integrates with blueprints to handle projectile pack */
	void PrimaryFire();

	UFUNCTION(BlueprintNativeEvent, Category = "Action")
	/** Primary fire integrates with blueprints to handle projectile pack */
	void AIUpdate();

	UFUNCTION(BlueprintCallable, Category = "Timer")
		/** Enemy begins firing at player on a loop with specified delay */
		void SetPFireActive(float PFireDelay);

	UFUNCTION(BlueprintCallable, Category = "Timer")
		/** Enemy begins firing at player on a loop with specified delay */
	void SetAIUpdateActive(float AIUpdateDelay);

private:

	//UPROPERTY(Category = "Plane", EditAnywhere)
	float MaxRollSpeed;

	/** Current roll speed */
	float CurrentRollSpeed;

	/** Player's current shield points MOVED currentSP and MaxSP to Targetable*/ 
	//float CurrentSP;

	/** Result of damage forumla to be applied*/
	float DmgAmmount;

	/** Player's maximum shield points*/
	//float MaxSP;

	/** Whether the enemy is firing primary at player on a loop*/
	bool bIsPFireActive;

	/** Sainstlayer will fire at player according to this handler*/
	FTimerHandle timerPrimaryFire;

	/** Whether the enemy is firing primary at player on a loop*/
	bool bIsAIActive;

	/** Sainstlayer will fire at player according to this handler*/
	FTimerHandle timerAIUpdate;

	bool bShouldFacePlayer;


	//time until AI attempts to face player again
	FTimerHandle timerFacePlayer;
	//time on the GCDTimer in seconds.
	float FacePlayerTime;

};


