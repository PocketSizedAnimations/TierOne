// Copyrighted - Pocket Sized Animations && Micah A. Parker - 2022

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Info.h"
#include "MissionManager.generated.h"



/**
 * 
 */
UCLASS()
class TIERONE_API AMissionManager : public AInfo
{
	GENERATED_BODY()
public:

	UPROPERTY(BlueprintReadOnly)
		TArray<class AMissionInfo*> MissionsList;

	const FString FileExtension = ".json";

	//===================================================================================================
	//=============================================FUNCTIONS=============================================
	//===================================================================================================

	virtual void BeginPlay() override;


	UFUNCTION()
		void LoadMissionsList();
	UFUNCTION()
		FString GetMissionsDirectory();

	UFUNCTION()
		AMissionInfo* GetMissionInfo(FString JsonData);
};
