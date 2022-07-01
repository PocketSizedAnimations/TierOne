// Copyrighted - Pocket Sized Animations && Micah A. Parker - 2022


#include "Players/T1Character.h"

/*first person view*/
#include "FirstPersonModule/Public/Components/FirstPersonViewComponent.h"
/*health*/
#include "HealthAndStaminaModule/Public/Components/SimpleHealthComponent.h"
/*interactives*/
#include "InteractionsModule/Public/Components/InteractiveManagerComponent.h"
/*inventory*/
#include "InventoryModule/Public/Components/InventoryManagerComponent.h"
/*movement*/
#include "GameFramework/CharacterMovementComponent.h"



// Sets default values
AT1Character::AT1Character(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{
 	
	HealthComponent = ObjectInitializer.CreateDefaultSubobject<USimpleHealthComponent>(this, TEXT("Health Component"));
	InventoryManagerComponent = ObjectInitializer.CreateDefaultSubobject<UInventoryManagerComponent>(this, TEXT("Inventory Manager"));
	if (InventoryManagerComponent)
	{
		//InventoryManagerComponent->bCanEquipItems = true;
	}
	InteractiveManagerComponent = ObjectInitializer.CreateDefaultSubobject<UInteractiveManagerComponent>(this, TEXT("Interactive Manager"));
	FirstPersonComponent = ObjectInitializer.CreateDefaultSubobject<UFirstPersonViewComponent>(this, TEXT("First Person"));
	
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AT1Character::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AT1Character::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AT1Character::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward", this, &AT1Character::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AT1Character::MoveRight);
}

void AT1Character::MoveForward(float Value)
{
	if (Value == 0.0f || !GetCharacterMovement())
		return;

	FVector InputVector = GetActorForwardVector() * Value;
	GetCharacterMovement()->AddInputVector(InputVector);
}

void AT1Character::MoveRight(float Value)
{
	if (Value == 0.0f || !GetCharacterMovement())
		return;

	FVector InputVector = GetActorRightVector() * Value;
	GetCharacterMovement()->AddInputVector(InputVector);
}

