// EXAMPLE code

#pragma once

#include "Components/ActorComponent.h"
#include "WeaponAC.generated.h"

UENUM(BlueprintType)		//"BlueprintType" is essential to include
enum class EAttunementEnum : uint8
{
AE_Sapphire 	UMETA(DisplayName = "Sapphire"),
AE_Jade 	UMETA(DisplayName = "Jade"),
AE_Crystal	UMETA(DisplayName = "Crystal"),
AE_Onyx	UMETA(DisplayName = "Onyx"),
AE_None	UMETA(DisplayName = "None")
};
UENUM(BlueprintType)		//"BlueprintType" is essential to include
enum class EActionEnum : uint8
{
	ActE_Default	UMETA(DisplayName = "Default"),
	ActE_Pl_Burst 	UMETA(DisplayName = "Pl Burst"),
	ActE_Pl_LightBurst 	UMETA(DisplayName = "Pl Light Burst"),
	ActE_Pl_HeavyBurst 	UMETA(DisplayName = "Pl Heavy Burst"),
	ActE_Pl_SupressiveBurst 	UMETA(DisplayName = "Pl Supressive Burst"),
	ActE_Pl_AmplifiedBurst	UMETA(DisplayName = "Pl Amplified Burst"),
	ActE_Pl_Heal	UMETA(DisplayName = "Pl Heal"),
	ActE_Pl_Cure	UMETA(DisplayName = "Pl Cure"),
	ActE_Pl_Infect	UMETA(DisplayName = "Pl Infect"),
	ActE_Pl_OverclockedBurst	UMETA(DisplayName = "Pl OverclockedBurst"),
	ActE_Pl_HullRend	UMETA(DisplayName = "Pl Hull Rend"),
	ActE_Pl_Gale	UMETA(DisplayName = "Pl Gale"),
	ActE_Pl_Action12	UMETA(DisplayName = "Pl Action12"),
	ActE_Pl_Action13	UMETA(DisplayName = "Pl Action13"),
	ActE_Pl_Action14	UMETA(DisplayName = "Pl Action14"),
	ActE_Pl_Action15	UMETA(DisplayName = "Pl Action15"),
	ActE_Pl_Action16	UMETA(DisplayName = "Pl Action16"),
	ActE_Pl_Action17	UMETA(DisplayName = "Pl Action17"),
	ActE_Pl_Action18	UMETA(DisplayName = "Pl Action18"),
	ActE_Pl_Action19	UMETA(DisplayName = "Pl Action19"),
	ActE_Pl_Action20	UMETA(DisplayName = "Pl Action20"),
	ActE_Pl_Action21	UMETA(DisplayName = "Pl Action21"),
	ActE_Pl_Action22	UMETA(DisplayName = "Pl Action22"),
	ActE_Pl_Action23	UMETA(DisplayName = "Pl Action23"),
	ActE_Pl_Action24	UMETA(DisplayName = "Pl Action24"),
	ActE_Pl_Action25	UMETA(DisplayName = "Pl Action25"),
	ActE_Pl_Action26	UMETA(DisplayName = "Pl Action26"),
	ActE_Pl_Action27	UMETA(DisplayName = "Pl Action27"),
	ActE_Pl_Action28	UMETA(DisplayName = "Pl Action28"),
	ActE_Pl_Action29	UMETA(DisplayName = "Pl Action29"),
	ActE_Pl_Action30	UMETA(DisplayName = "Pl Action30"),
	ActE_Pl_Action31	UMETA(DisplayName = "Pl Action31"),
	ActE_Pl_Action32	UMETA(DisplayName = "Pl Action32"),
	ActE_Pl_Action33	UMETA(DisplayName = "Pl Action33"),
	ActE_Pl_Action34	UMETA(DisplayName = "Pl Action34"),
	ActE_Pl_Action35	UMETA(DisplayName = "Pl Action35"),
	ActE_Pl_Action36	UMETA(DisplayName = "Pl Action36"),
	ActE_Pl_Action37	UMETA(DisplayName = "Pl Action37"),
	ActE_Pl_Action38	UMETA(DisplayName = "Pl Action38"),
	ActE_Pl_Action39	UMETA(DisplayName = "Pl Action39"),
	ActE_Pl_Action40	UMETA(DisplayName = "Pl Action40"),
	ActE_Pl_Action41	UMETA(DisplayName = "Pl Action41"),
	ActE_Pl_Action42	UMETA(DisplayName = "Pl Action42"),
	ActE_Pl_Action43	UMETA(DisplayName = "Pl Action43"),
	ActE_Pl_Action44	UMETA(DisplayName = "Pl Action44"),
	ActE_Pl_Action45	UMETA(DisplayName = "Pl Action45"),
	ActE_Pl_Action46	UMETA(DisplayName = "Pl Action46"),
	ActE_Pl_Action47	UMETA(DisplayName = "Pl Action47"),
	ActE_Pl_Action48	UMETA(DisplayName = "Pl Action48"),
	ActE_Pl_Action49	UMETA(DisplayName = "Pl Action49"),
	ActE_Pl_Action50	UMETA(DisplayName = "Pl Action50"),
	ActE_None	UMETA(DisplayName = "None")
};


UENUM(BlueprintType)		
enum class NPCActionEnum : uint8
{
	ActNPC_Default	UMETA(DisplayName = "Default"),
	ActNPC_Burst 	UMETA(DisplayName = "NPC Burst"),
	ActNPC_LightBurst 	UMETA(DisplayName = "NPC Light Burst"),
	ActNPC_HeavyBurst 	UMETA(DisplayName = "NPC Heavy Burst"),
	ActNPC_SupressiveBurst 	UMETA(DisplayName = "NPC Supressive Burst"),
	ActNPC_AmplifiedBurst	UMETA(DisplayName = "NPC Amplified Burst"),
	ActNPC_Heal	UMETA(DisplayName = "NPC Heal"),
	ActNPC_Cure	UMETA(DisplayName = "NPC Cure"),
	ActNPC_Infect	UMETA(DisplayName = "NPC Infect"),
	ActNPC_OverclockedBurst	UMETA(DisplayName = "NPC OverclockedBurst"),
	ActNPC_HullRend	UMETA(DisplayName = "NPC Hull Rend"),
	ActNPC_Gale	UMETA(DisplayName = "NPC Gale"),
	ActNPC_Action12	UMETA(DisplayName = "NPC Action12"),
	ActNPC_Action13	UMETA(DisplayName = "NPC Action13"),
	ActNPC_Action14	UMETA(DisplayName = "NPC Action14"),
	ActNPC_Action15	UMETA(DisplayName = "NPC Action15"),
	ActNPC_Action16	UMETA(DisplayName = "NPC Action16"),
	ActNPC_Action17	UMETA(DisplayName = "NPC Action17"),
	ActNPC_Action18	UMETA(DisplayName = "NPC Action18"),
	ActNPC_Action19	UMETA(DisplayName = "NPC Action19"),
	ActNPC_Action20	UMETA(DisplayName = "NPC Action20"),
	ActNPC_Action21	UMETA(DisplayName = "NPC Action21"),
	ActNPC_Action22	UMETA(DisplayName = "NPC Action22"),
	ActNPC_Action23	UMETA(DisplayName = "NPC Action23"),
	ActNPC_Action24	UMETA(DisplayName = "NPC Action24"),
	ActNPC_Action25	UMETA(DisplayName = "NPC Action25"),
	ActNPC_Action26	UMETA(DisplayName = "NPC Action26"),
	ActNPC_Action27	UMETA(DisplayName = "NPC Action27"),
	ActNPC_Action28	UMETA(DisplayName = "NPC Action28"),
	ActNPC_Action29	UMETA(DisplayName = "NPC Action29"),
	ActNPC_Action30	UMETA(DisplayName = "NPC Action30"),
	ActNPC_Action31	UMETA(DisplayName = "NPC Action31"),
	ActNPC_Action32	UMETA(DisplayName = "NPC Action32"),
	ActNPC_Action33	UMETA(DisplayName = "NPC Action33"),
	ActNPC_Action34	UMETA(DisplayName = "NPC Action34"),
	ActNPC_Action35	UMETA(DisplayName = "NPC Action35"),
	ActNPC_Action36	UMETA(DisplayName = "NPC Action36"),
	ActNPC_Action37	UMETA(DisplayName = "NPC Action37"),
	ActNPC_Action38	UMETA(DisplayName = "NPC Action38"),
	ActNPC_Action39	UMETA(DisplayName = "NPC Action39"),
	ActNPC_Action40	UMETA(DisplayName = "NPC Action40"),
	ActNPC_Action41	UMETA(DisplayName = "NPC Action41"),
	ActNPC_Action42	UMETA(DisplayName = "NPC Action42"),
	ActNPC_Action43	UMETA(DisplayName = "NPC Action43"),
	ActNPC_Action44	UMETA(DisplayName = "NPC Action44"),
	ActNPC_Action45	UMETA(DisplayName = "NPC Action45"),
	ActNPC_Action46	UMETA(DisplayName = "NPC Action46"),
	ActNPC_Action47	UMETA(DisplayName = "NPC Action47"),
	ActNPC_Action48	UMETA(DisplayName = "NPC Action48"),
	ActNPC_Action49	UMETA(DisplayName = "NPC Action49"),
	ActNPC_Action50	UMETA(DisplayName = "NPC Action50"),
	ActNPC_None	UMETA(DisplayName = "NPCNone")
};


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ObjMAIN_API UWeaponAC : public UActorComponent
{
	GENERATED_BODY()

public:	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Enum)
	EAttunementEnum AttunementEnum;
	// Sets default values for this component's properties
	UWeaponAC();

	// Called when the game starts
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction ) override;
	
	UFUNCTION(BlueprintCallable, Category = "Weapon")
	void SetAction(EActionEnum TmpEnum);

	UFUNCTION(BlueprintCallable, Category = "Weapon")
	float CalcTotalDmg();
	UFUNCTION(BlueprintCallable, Category = "Weapon")
	float GetMaxRange();

	UFUNCTION(BlueprintCallable, Category = "Weapon")
	EAttunementEnum GetAttunement();
	UFUNCTION(BlueprintCallable, Category = "Weapon")
	EActionEnum GetAction();
	UFUNCTION(BlueprintCallable, Category = "Weapon")

	UFUNCTION(BlueprintCallable, Category = "Weapon")
	bool FireWeapon(int32 ActionPKey);

	UFUNCTION(BlueprintCallable, Category = "Weapon")
	float MaxCloseRange();
	UFUNCTION(BlueprintCallable, Category = "Weapon")
	/** Returns the max range at which an attack will Glance %50 of the time*/
	float MaxMidRange();
	UFUNCTION(BlueprintCallable, Category = "Weapon")
	/** Returns the max range at which an attack will not miss %>0 of the time*/
	float MaxLongRange();
	//--------------------------------------

	UFUNCTION(BlueprintCallable, Category = "Weapon")
	/**maximum optimal range in uu*/
	float MaxOptimalRange();

	UFUNCTION(BlueprintCallable, Category = "Weapon")
	/** Maximum falloff before falloff is 100%*/
	float MaxFalloffRange();

	UFUNCTION(BlueprintCallable, Category = "Weapon")
	/** now MaxOptimalRange Returns the max range at which an attack will critical strike %100 of the time*/
	float MaxRange();

	UFUNCTION(BlueprintCallable, Category = "Weapon")
		void SetMaxOptimalRange(float tmp);

	UFUNCTION(BlueprintCallable, Category = "Weapon")
		void SetMaxFalloffRange(float tmp);


	UFUNCTION(BlueprintCallable, Category = "Weapon")
		void SetMaxRange(float tmp);
	
	UFUNCTION(BlueprintCallable, Category = "Weapon")
		void GenerateWeaponPreset(int32 PresetNum);

private:
	EActionEnum ActionEnum;
	float baseDmg;
	bool bSlowsNPC;
	//Range: currently the closer you are when firing, the more a) accurate and/or b)effective the weapon is.
	//visualised as three spheres around the gun, the radius of the smallest is RangeOptimal(in other words, maximum distance where optimal is in effect)
	//with this sphere being %100 crit chance and being called Close Range in game terms
	//outside that being Optimal+falloff (the average here will glance %50, hit/crit the rest) or Mid Range in game terms
	//the largest sphere is >%0 of not missing (glance, hit, critical strike), Long Range in game terms and everything outside that will always miss
	//--------------------
	float RangeOptimal;//maxumum range in CM to deliver optimal damage
	float RangeFalloff;
	float RangeMax;//maximum range in CM to deliver any damage.  Should be the same as Max desired range of NPC found in targetable

};
