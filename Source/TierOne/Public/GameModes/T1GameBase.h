// Copyrighted - Pocket Sized Animations && Micah A. Parker - 2022

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "T1GameBase.generated.h"

UENUM(BlueprintType)
enum class EGameState : uint8 {
	PreGame,
	Briefing,
	Planning,
	InProgress,
	PostGame
};

/**
 * 
 */
UCLASS(abstract)
class TIERONE_API AT1GameBase : public AGameModeBase
{
	GENERATED_BODY()
public:
	

	/*ui*/
	UPROPERTY(EditDefaultsOnly, Category = "Briefing")
		bool bMissionPrePlanning = false;
	UPROPERTY(EditDefaultsOnly, Category = "Brief")
		TSubclassOf<class UUserWidget> BriefingWidgetClass;



	//=======================================================================================================
	//===============================================FUNCTIONS===============================================
	//=======================================================================================================
public:
	AT1GameBase();


	//==============================================================
	//======================OPERATION HANDLING======================
	//==============================================================
public:
	UFUNCTION(BlueprintCallable, Category = "Operation")
		virtual void StartOperation();
	UFUNCTION()
		virtual void SpawnSquads();
	UFUNCTION()
		virtual void SpawnLoadout(AT1Character* Operator, AOperatorInfo* OperatorInfo);
	UFUNCTION()
		AActor* FindSquadStart(class ASquadInfo* Squad);


	//=============================================================
	//=======================PLAYER HANDLING=======================
	//=============================================================
public:

	void HandleStartingNewPlayer_Implementation(APlayerController* NewPlayer) override;

	/*looks through all current players, and if they're not already possessing a character - pushes them to possess one*/
	UFUNCTION()
		virtual void HavePlayersPossessOperators();

	//==================================================
	//========================UI========================
	//==================================================
	UFUNCTION(BlueprintCallable, Category = "UI")
		virtual void OpenBriefingWidget(APlayerController* Player);

};
