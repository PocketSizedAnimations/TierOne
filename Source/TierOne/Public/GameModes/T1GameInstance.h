// Copyrighted - Pocket Sized Animations && Micah A. Parker - 2022

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "T1GameInstance.generated.h"

/**
 * 
 */
UCLASS(abstract)
class TIERONE_API UT1GameInstance : public UGameInstance
{
	GENERATED_BODY()
public:

	UPROPERTY(EditDefaultsOnly, Category = "Equipment")
		class ULoadoutTemplate* DefaultWeaponLoadout;

};
