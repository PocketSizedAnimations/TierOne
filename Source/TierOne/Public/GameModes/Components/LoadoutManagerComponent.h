// Copyrighted - Pocket Sized Animations && Micah A. Parker - 2022

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "LoadoutManagerComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TIERONE_API ULoadoutManagerComponent : public UActorComponent
{
	GENERATED_BODY()
public:

	UPROPERTY(BlueprintReadOnly, Category = "Weapons")
		TArray<TSubclassOf<class AFirearm>> PrimaryWeapons;
	UPROPERTY(BlueprintReadOnly, Category = "Weapons")
		TArray<TSubclassOf<class AFirearm>> AlternativeWeapons;
	UPROPERTY(BlueprintReadOnly, Category = "Weapons")
		TArray<TSubclassOf<class AFirearm>> SecondaryWeapons;

	//=============================================================================================================
	//==================================================FUNCTIONS==================================================
	//=============================================================================================================

public:	
	// Sets default values for this component's properties
	ULoadoutManagerComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
