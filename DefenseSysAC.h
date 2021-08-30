// EXAMPLE code

#pragma once

#include "Components/ActorComponent.h"
#include "DefenseSysAC.generated.h"

UENUM(BlueprintType)	
enum class EStatusEnum : uint8
{
	StatE_Mesmerize 	UMETA(DisplayName = "Mesmerize"),
	StatE_Slow	UMETA(DisplayName = "Slow"),
	StatE_Root	UMETA(DisplayName = "Root"),
	StatE_Sleep	UMETA(DisplayName = "Sleep"),
	StatE_Corrode	UMETA(DisplayName = "Corrode"),
	StatE_DampenField	UMETA(DisplayName = "DampenField"),
	StatE_Boost	UMETA(DisplayName = "Boost"),
	StatE_Regenerate	UMETA(DisplayName = "Regenerate"),
	StatE_Focus	UMETA(DisplayName = "Focus"),
	StatE_Agility	UMETA(DisplayName = "Agility"),
	StatE_None	UMETA(DisplayName = "None")
};

USTRUCT(BlueprintType)
struct FItemStruct
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly)
		int32 ItemID;

	UPROPERTY(BlueprintReadOnly)
		int32 ItemVal1;

	//Set
	void SetID(const int32 NewValue)
	{
		ItemID = NewValue;
	}

	//Get
	int32 GetID()
	{
		return ItemID;
	}

	//Check
	bool IsValidID() const
	{
		if (ItemID > 0)
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	//Constructor
	FItemStruct()
	{

		ItemID = 666;
		ItemVal1 = 777;
	}
};


//DefenseSysAC is an actor component comprising all vessel/base systems and inventory, relating to defensive stats and outfitting
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ObjMAIN_API UDefenseSysAC : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UDefenseSysAC();

	// Called when the game starts
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction ) override;
	
	UFUNCTION(BlueprintCallable, Category = "Defense")
		/**If it returns zero, the shields are down.*/
	int32 GetCurrentSP();

	UFUNCTION(BlueprintCallable, Category = "Defense")
	int32 GetMaxSP();

	//UFUNCTION(BlueprintCallable, Category = "Defense")
	//float GetMaxSP();
	UFUNCTION(BlueprintCallable, Category = "Defense")
	/**subtracts DmgAmt from CurrentSheild, returns the amount of dmg left if shield falls to zero, or else returns 0*/
	int32 DmgSP(int32 DmgAmt);

	UFUNCTION(BlueprintCallable, Category = "Defense")
		/**subtracts DmgAmt from CurrentSheild, returns the amount of dmg left if shield falls to zero, or else returns 0*/
		void IncreaseSP(int32 Amt);

	UFUNCTION(BlueprintCallable, Category = "Defense")
	/**Delivers SimpDmg damage point-for point to defenses, working down field to empty, then shield to empty, then hull to empty, returns any remainder of SimpDmg*/
	int32 TakeSimpleDamage(int32 SimpDmg);

	UFUNCTION(BlueprintCallable, Category = "Defense")
	int32 GetCurrentFP();
	UFUNCTION(BlueprintCallable, Category = "Defense")
	void SetCurrentFP(int32 tmp);

	UFUNCTION(BlueprintCallable, Category = "Defense")
	int32 GetMaxFP();

	UFUNCTION(BlueprintCallable, Category = "Defense")
		/**subtracts DmgAmt from CurrentField, returns the amount of dmg left if field falls to zero, or else returns 0, meaning all damage points have been spent*/
	int32 DmgFP(int32 DmgAmt);

	UFUNCTION(BlueprintCallable, Category = "Defense")
		/***/
		void AddFP(int32 AddAmt);

	UFUNCTION(BlueprintCallable, Category = "Defense")
	int32 GetCurrentHP();

	UFUNCTION(BlueprintCallable, Category = "Defense")
	int32 GetMaxHP();

	UFUNCTION(BlueprintCallable, Category = "Defense")
	/**subtracts DmgAmt from CurrentHull,returns the remainder as overkill points.  If return float is >0.f, ship hull has been reduced to 0*/
	int32 DmgHP(int32 DmgAmt);

	UFUNCTION(BlueprintCallable, Category = "Defense")
	float GetCurrentEP();

	UFUNCTION(BlueprintCallable, Category = "Defense")
	float GetMaxEP();

	/**adds ChangeAmt from CurrentEP, returns Current EP after Addition*/
	UFUNCTION(BlueprintCallable, Category = "Defense")
	float ChangeEP(float ChangeAmt);

	UFUNCTION(BlueprintCallable, Category = "Defense")
	float GetCurrentOP();

	UFUNCTION(BlueprintCallable, Category = "Defense")
	float GetMaxOP();

	UFUNCTION(BlueprintCallable, Category = "Orison")
		int32 GetCurrentXP();
	UFUNCTION(BlueprintCallable, Category = "Orison")
		int32 GetCurrentLvl();
	
	/**Sets the level, returns the new level number or -1 for error*/
	UFUNCTION(BlueprintCallable, Category = "Orison")
	int32 SetLvl(int32 NewLvl);

	UFUNCTION(BlueprintCallable, Category = "Status")
	/* Add a status effect and return true if successful*/
	bool AddStatus(EStatusEnum TmpStatus, int32 TmpIndex);

	UFUNCTION(BlueprintCallable, Category = "Status")
	/* Returns status at index TmpIndex or none for out of range*/
	EStatusEnum GetStatus(int32 TmpIndex);

	UFUNCTION(BlueprintCallable, Category = "Status")
	/* Returns number of instances of given status currently applied to player*/
	int32 CheckForStatus(EStatusEnum TmpStatus);

	UFUNCTION(BlueprintCallable, Category = "Status")
	/* Take out the status effect update status list array so that there are no gaps, returning true if successfully removed OR if there was nothing needed, false if problem*/
	bool RemoveStatus(int32 TmpIndex);
	
	UFUNCTION(BlueprintCallable, Category = "Setup")
	/* Set current and max FP, SP, HP to numbers specified, except if 0, in which case max is set to 1 and current to 0 to avoid divide by zero issues
	@TmpFP - Current and max FP numbers
	@TmpSP - Current and max SP numbers
	@TmpHP - Current and max HP numbers*/
	void SetDefensePoints(int32 TmpFP, int32 TmpSP, int32 TmpHP);

	//bool IsStatusActive(int32 TmpIndex);
	UFUNCTION(BlueprintCallable, Category = "Status")
	/* Returns the total number of possible status effects that can be active at once.*/
	int32 GetMaxStatusEffects();
private:
	/** Player's current field points*/
	int32 CurrentFieldPoints;
	/**Player's maximum field points*/
	int32 MaxFieldPoints;

	/** Player's current field points*/
	int32 CurrentShieldPoints;
	/**Player's maximum field points*/
	int32 MaxShieldPoints;

	/** Player's current field points*/
	int32 CurrentHullPoints;
	/**Player's maximum field points*/
	int32 MaxHullPoints;


	UPROPERTY(EditAnywhere, Category = "Enum")
		/*returns status where index is the status slot*/
	TArray<EStatusEnum> StatusList;

	int32 MaxStatusEffects;
	/**Max number of seconds a status effect can last*/
	int32 MaxStatusTime;
	/** Total experience points*/
	int32 XP;
	/** Current character level*/
	int32 Lvl;
};
