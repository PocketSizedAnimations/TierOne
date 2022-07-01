// Copyrighted - Pocket Sized Animations && Micah A. Parker - 2022

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Info.h"
#include "OperatorInfo.generated.h"

UENUM(BlueprintType)
enum class EOperatorStatus : uint8
{
	Available,
	Injured,
	Deceased,
	Locked
};

UENUM(BlueprintType)
enum class EOperatorStat : uint8 {
	Assault,
	Stealth,
	Marksmanship,
	Demolitions,
	Electronics,
	Grenades,
	Aggression,
	Leadership,
	Stamina
};

USTRUCT(BlueprintType)
struct FOperatorStats
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float Assault;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float Stealth;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float Marksmanship;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float Demolitions;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float Electronics;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float Grenades;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float Aggression;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float Leadership;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float Stamina;
};

/**
 * 
 */
UCLASS()
class TIERONE_API AOperatorInfo : public AInfo
{
	GENERATED_BODY()
public:

	/*general-info*/
	UPROPERTY(BlueprintReadWrite)
		FString FirstName;
	UPROPERTY(BlueprintReadWrite)
		FString LastName;
	UPROPERTY(BlueprintReadWrite)
		FString Nationality;
	UPROPERTY(BlueprintReadWrite)
		uint8 Age;
	UPROPERTY(BlueprintReadWrite, meta=(DisplayName="ID Tag"))
		FString IDTag;
	UPROPERTY(BlueprintReadWrite)
		EOperatorStatus Status;
	UPROPERTY(BlueprintReadWrite)
		FOperatorStats Stats;

	/*loadout info*/
	UPROPERTY(BlueprintReadWrite, Category = "Loadout")
		class UWeaponSelectionDataAsset* PrimaryWeapon;
	UPROPERTY(BlueprintReadWrite, Category = "Loadout")
		class UWeaponSelectionDataAsset* AlternativeWeapon;
	UPROPERTY(BlueprintReadWrite, Category = "Loadout")
		class UWeaponSelectionDataAsset* SecondaryWeapon;

	/*gameplay info*/
	UPROPERTY(BlueprintReadWrite)
		class ASquadInfo* Squad;
	UPROPERTY(BlueprintReadOnly)
		APawn* Pawn;


	//===============================================================================================
	//===========================================FUNCTIONS===========================================
	//===============================================================================================
public:
	AOperatorInfo();


	//===========================
	//==========LOADOUT==========
	//===========================
	UFUNCTION()
		TSubclassOf<AActor> GetPrimaryWeaponClass();


	UFUNCTION()
		void LoadFromJSON(FString JsonData);

};
