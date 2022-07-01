// Copyrighted - Pocket Sized Animations && Micah A. Parker - 2022

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "GameModes/T1GameBase.h"
#include "T1GameState.generated.h"

/**
 * 
 */
UCLASS()
class TIERONE_API AT1GameState : public AGameStateBase
{
	GENERATED_BODY()
public:


	UPROPERTY(Replicated)
		EGameState CurrentState;

	/*managers*/
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		class ULoadoutManagerComponent* LoadoutManager;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		class UOperatorManagerComponent* OperatorManager;

	//===============================================================
	//===========================FUNCTIONS===========================
	//===============================================================
public:
	AT1GameState(const FObjectInitializer& ObjectInitializer);
	
};
