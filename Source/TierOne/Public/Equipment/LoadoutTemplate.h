// Copyrighted - Pocket Sized Animations && Micah A. Parker - 2022

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "LoadoutTemplate.generated.h"

/**
 * 
 */
UCLASS()
class TIERONE_API ULoadoutTemplate : public UPrimaryDataAsset
{
	GENERATED_BODY()
public:

	UPROPERTY(EditAnywhere, Category = "Weapons|Primary")
		TArray<class UWeaponSelectionDataAsset*> AssaultRifles;
	UPROPERTY(EditAnywhere, Category = "Weapons|Primary")
		TArray<class UWeaponSelectionDataAsset*> SubmachineGuns;
};
