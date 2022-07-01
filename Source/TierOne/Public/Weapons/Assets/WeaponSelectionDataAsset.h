// Copyrighted - Pocket Sized Animations && Micah A. Parker - 2022

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "WeaponSelectionDataAsset.generated.h"

/**
 * 
 */
UCLASS()
class TIERONE_API UWeaponSelectionDataAsset : public UPrimaryDataAsset
{
	GENERATED_BODY()
public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TSubclassOf<class AFirearm> WeaponBlueprintClass;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FName WeaponName;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FName WeaponDescription;
};
