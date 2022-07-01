// Copyrighted - Pocket Sized Animations && Micah A. Parker - 2022

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/WorldSubsystem.h"
#include "MissionPlannerSubsystem.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnSquadChange,ASquadInfo*,SquadInfo);

/**
 * 
 */
UCLASS()
class TIERONE_API UMissionPlannerSubsystem : public UWorldSubsystem
{
	GENERATED_BODY()
private:

	/*roster*/
	UPROPERTY()
		TArray<class AOperatorInfo*> Roster;

	/*squad configurations*/

	UPROPERTY()
		ASquadInfo* CurrentSelectedSquad;
	UPROPERTY()
		TArray<class ASquadInfo*> Squads;



	/*the operator we're currently trying to modify*/
	UPROPERTY()
		class AOperatorInfo* CurrentSelectedOperator;


	/*file-search*/
	const FString FileExtension = ".json";


	/*bindable events*/
public:
	/*called any time a Squad has a structural change (added/removed operator)*/
	UPROPERTY(BlueprintAssignable)
		FOnSquadChange OnSquadChange;

	//===================================================================================================================
	//=====================================================FUNCTIONS=====================================================
	//===================================================================================================================
public:
	// USubsystem implementation Begin
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;
	// USubsystem implementation End



	//==============================
	//============ROSTER============
	//==============================
	UFUNCTION()
		void InitializeRoster();
	UFUNCTION(BlueprintPure, Category = "Roster")
		TArray<AOperatorInfo*>& GetRoster();
	UFUNCTION()
		void UpdateRoster(TArray<AOperatorInfo*>& NewRoster);

	//==================================
	//==============SQUADS==============
	//==================================
	UFUNCTION()
		void InitializeSquads();
	UFUNCTION(BlueprintPure, Category = "Squads")
		ASquadInfo* GetCurrentSquad();
	UFUNCTION(BlueprintCallable, Category = "Squads")
		void SetCurrentSquad(ASquadInfo* Squad);
	UFUNCTION()
		void AddSquad(class ASquadInfo* Squad);
	UFUNCTION(BlueprintPure,Category = "Squads")
		TArray<class ASquadInfo*>& GetSquads();
	UFUNCTION(BlueprintCallable, Category = "Squads")
		ASquadInfo* GetSquadByIndex(uint8 index);
	UFUNCTION()
		void OnSquadUpdated(ASquadInfo* Squad);

	/*simply returns true if there is at least 1 operator assigned across all squads*/
	UFUNCTION(BlueprintPure, BlueprintCallable, Category = "Squads")
		bool SquadsHaveAnyOperators();
	
	//=================================
	//============OPERATORS============
	//=================================
	UFUNCTION(BlueprintPure, Category = "Operators")
		AOperatorInfo* GetCurrentOperator();
	UFUNCTION(BlueprintCallable, Category = "Operators")
		void SetCurrentOperator(AOperatorInfo* Operator);


	//==============================
	//===========LOADOUTS===========
	//==============================
	
	/*quick function that grabs the current operators current primary weapon*/
	UFUNCTION(BlueprintPure, Category = "Loadouts")
		class UWeaponSelectionDataAsset* GetCurrentPrimary();

	

	//================================
	//===========SAVE FILES===========
	//================================

	UFUNCTION(BlueprintCallable)
		FString GetOperatorSaveDirectory();
	UFUNCTION()
		class AOperatorInfo* GetOperatorInfoFromJSON(FString JsonString);
	UFUNCTION()
		void LoadRosterFromDisk();



};
