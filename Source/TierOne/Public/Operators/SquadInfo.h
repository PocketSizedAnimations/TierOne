// Copyrighted - Pocket Sized Animations && Micah A. Parker - 2022

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Info.h"
#include "SquadInfo.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnRosterChange, ASquadInfo*,SquadInfo);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnOperatorAdded);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnOperatorRemoved);

/**
 * 
 */
UCLASS()
class TIERONE_API ASquadInfo : public AInfo
{
	GENERATED_BODY()
public:


	UPROPERTY(BlueprintReadOnly)
		TArray<class AOperatorInfo*> Operators;

	/*delegates/events*/
public:
	UPROPERTY(BlueprintAssignable)
		FOnRosterChange OnRosterChange;
	UPROPERTY(BlueprintAssignable)
		FOnOperatorAdded OnOperatorAdded;
	UPROPERTY(BlueprintAssignable)
		FOnOperatorRemoved OnOperatorRemoved;

	//=======================================================================
	//===============================FUNCTIONS===============================
	//=======================================================================
	ASquadInfo();

public:

	UFUNCTION(BlueprintCallable, Category = "Operators")
		virtual bool AddOperator(AOperatorInfo* Operator);

	UFUNCTION(BlueprintCallable, Category = "Operators")
		class AOperatorInfo* GetOperator(uint8 Index);

};
