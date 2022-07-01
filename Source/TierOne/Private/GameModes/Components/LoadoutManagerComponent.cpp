// Copyrighted - Pocket Sized Animations && Micah A. Parker - 2022


#include "GameModes/Components/LoadoutManagerComponent.h"

// Sets default values for this component's properties
ULoadoutManagerComponent::ULoadoutManagerComponent()
{
	
	
	/*replication*/
	SetIsReplicatedByDefault(true);
	/*ticking*/
	PrimaryComponentTick.bCanEverTick = false;
}


// Called when the game starts
void ULoadoutManagerComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void ULoadoutManagerComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

