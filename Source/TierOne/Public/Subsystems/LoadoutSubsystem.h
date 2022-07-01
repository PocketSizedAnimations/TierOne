// Copyrighted - Pocket Sized Animations && Micah A. Parker - 2022

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "LoadoutSubsystem.generated.h"

/**
 * 
 */
UCLASS()
class TIERONE_API ULoadoutSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()
public:


	UPROPERTY(BlueprintReadOnly, Category = "Weapons")
		TArray<class UWeaponSelectionDataAsset*> PrimaryWeapons;
	UPROPERTY(BlueprintReadOnly, Category = "Weapons")
		TArray<TSubclassOf<class AFirearm>> AlternativeWeapons;
	UPROPERTY(BlueprintReadOnly, Category = "Weapons")
		TArray<TSubclassOf<class AFirearm>> SecondaryWeapons;




	
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;	
	virtual void Deinitialize() override;


};
