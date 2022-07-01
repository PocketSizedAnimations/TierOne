// Copyrighted - Pocket Sized Animations && Micah A. Parker - 2022

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "EntryLevelGameMode.generated.h"

/**
 * 
 */
UCLASS()
class TIERONE_API AEntryLevelGameMode : public AGameModeBase
{
	GENERATED_BODY()
public:

	//=========================================================================================
	//========================================FUNCTIONS========================================
	//=========================================================================================
	UFUNCTION(BlueprintCallable, Category = "Game")
		virtual void ServerTravel(const FString& URL, bool bAbsolute = false);
	
};
