// Copyrighted - Pocket Sized Animations && Micah A. Parker - 2022

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Info.h"
#include "MissionInfo.generated.h"

UENUM(BlueprintType)
enum class ECountry : uint8
{
	Unknown,
	UnitedStates,
	Russia
};

/**
 * 
 */
UCLASS()
class TIERONE_API AMissionInfo : public AInfo
{
	GENERATED_BODY()
public:

	UPROPERTY(BlueprintReadWrite)
		FString Name;
	UPROPERTY(BlueprintReadWrite)
		FString Summary;
	UPROPERTY(BlueprintReadWrite)
		FString Region;
	UPROPERTY(BlueprintReadWrite)
		ECountry Country;

	UPROPERTY(BlueprintReadWrite)
		UTexture2D* PreviewImage;
	UPROPERTY()
		FName MapName;



	//===============================================================================
	//===================================FUNCTIONS===================================
	//===============================================================================
public:

	UFUNCTION()
		void LoadFromJSON(FString JsonData);
	UFUNCTION()
		ECountry GetCountryFromString(FString CountryString);
	UFUNCTION()
		void LoadPreviewImage(FString TexturePath);

	UFUNCTION(BlueprintPure)
		FName GetMapName();

};
