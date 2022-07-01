// Copyrighted - Pocket Sized Animations && Micah A. Parker - 2022

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "T1Character.generated.h"

UCLASS()
class TIERONE_API AT1Character : public ACharacter
{
	GENERATED_BODY()
public:


	UPROPERTY(VisibleAnywhere)
		class USimpleHealthComponent* HealthComponent;
	UPROPERTY(VisibleAnywhere)
		class UInventoryManagerComponent* InventoryManagerComponent;
	UPROPERTY(VisibleAnywhere)
		class UInteractiveManagerComponent* InteractiveManagerComponent;
	UPROPERTY(VisibleAnywhere)
		class UFirstPersonViewComponent* FirstPersonComponent;



	//===============================================================================================
	//===========================================FUNCTIONS===========================================
	//===============================================================================================
public:
	// Sets default values for this character's properties
	AT1Character(const FObjectInitializer& ObjectInitializer);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;




	//==========================================
	//=================MOVEMENT=================
	//==========================================
public:
	UFUNCTION()
		virtual void MoveForward(float Value);
	UFUNCTION()
		virtual void MoveRight(float Value);


};
