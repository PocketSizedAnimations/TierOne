// Copyrighted - Pocket Sized Animations && Micah A. Parker - 2022


#include "GameModes/T1GameState.h"

/*managers*/
#include "Gamemodes/Components/LoadoutManagerComponent.h"
#include "GameModes/Components/OperatorManagerComponent.h"

/*replication*/
#include "Net/UnrealNetwork.h"


void AT1GameState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AT1GameState, CurrentState);
	DOREPLIFETIME(AT1GameState, LoadoutManager);
	DOREPLIFETIME(AT1GameState, OperatorManager);
}


AT1GameState::AT1GameState(const FObjectInitializer& ObjectInitializer)
 :Super(ObjectInitializer)
{
	LoadoutManager = ObjectInitializer.CreateDefaultSubobject<ULoadoutManagerComponent>(this, TEXT("LoadoutManager"));

	OperatorManager = ObjectInitializer.CreateDefaultSubobject<UOperatorManagerComponent>(this, TEXT("OperatorManager"));
}
