// Copyrighted - Pocket Sized Animations && Micah A. Parker - 2022

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "OperatorManagerComponent.generated.h"


//DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnSquadChange);


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TIERONE_API UOperatorManagerComponent : public UActorComponent
{
	GENERATED_BODY()
public:

	UPROPERTY(Replicated, ReplicatedUsing="OnRep_RosterUpdated", BlueprintReadWrite)
		TArray<class AOperatorInfo*> OperatorRoster;


	UPROPERTY(Replicated, BlueprintReadWrite)
		TArray<class ASquadInfo*> Squads;

private:
	UPROPERTY(Replicated)
		TArray<class AT1Character*> OperatorPawns;


	/*events/delegates*/
public:
	/*called any time a Squad has a structural change (added/removed operator)*/
	//UPROPERTY(BlueprintAssignable)
	//	FOnSquadChange OnSquadChange;


	/*file-search*/
	const FString FileExtension = ".json";

	//=========================================================
	//========================FUNCTIONS========================
	//=========================================================
	
public:	
	// Sets default values for this component's properties
	UOperatorManagerComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	


	//=======json data loading========
	UFUNCTION(BlueprintCallable)
		FString GetOperatorSaveDirectory();
	UFUNCTION(BlueprintCallable)
		TArray<FString> GetOperatorsJson();
	
	class AOperatorInfo* GetOperatorInfo(FString JsonString);


	UFUNCTION(BlueprintCallable, Category = "Squads")
		bool AddOperatorToSquad(AOperatorInfo* Operator, ASquadInfo* Squad);
	/*simply returns true if there is at least 1 operator assigned across all squads*/
	UFUNCTION(BlueprintPure, BlueprintCallable, Category = "Squads")
		bool SquadsHaveAnyOperators();

	UFUNCTION()
		void OnReceiveSquadChange();
	UFUNCTION()
		void OnRep_RosterUpdated();

	UFUNCTION(BlueprintCallable, Category = "Squads")
		ASquadInfo* GetSquad(int32 Index);

	//=====================================
	//================PAWNS================
	//=====================================
public:
	UFUNCTION()
		virtual bool RegisterOperatorPawn(class AT1Character* Pawn);
	UFUNCTION()
		TArray<class AT1Character*> GetOperatorPawns();
};
