// Copyrighted - Pocket Sized Animations && Micah A. Parker - 2022


#include "GameModes/T1GameBase.h"
#include "GameModes/T1GameState.h"
#include "Players/T1PlayerController.h"
#include "Players/T1Character.h"
#include "..\..\Public\GameModes\T1GameBase.h"
#include "Engine/PlayerStartPIE.h"
#include "GameFramework/PlayerStart.h"
#include "Engine/World.h"
#include "EngineUtils.h"
#include "GameModes/Components/OperatorManagerComponent.h"
#include "MissionPlanner/Subsystem/MissionPlannerSubsystem.h"
#include "Operators/SquadInfo.h"
#include "Operators/OperatorInfo.h"
#include "Players/T1Character.h"

/*inventory*/
#include "InventoryModule/Public/Components/InventoryManagerComponent.h"
#include "InventoryModule/Public/Components/InventoryItemComponent.h"
#include "InventoryModule/Public/Misc/InventoryTemplate.h"


AT1GameBase::AT1GameBase()
{
	PlayerControllerClass = AT1PlayerController::StaticClass();
	GameStateClass = AT1GameState::StaticClass();
	DefaultPawnClass = AT1Character::StaticClass();

	bUseSeamlessTravel = true;
	bStartPlayersAsSpectators = true;
}

void AT1GameBase::StartOperation()
{
	SpawnSquads();
	HavePlayersPossessOperators();
}

void AT1GameBase::SpawnSquads()
{
	for (auto Squad : GetWorld()->GetSubsystem<UMissionPlannerSubsystem>()->GetSquads())
	{		
		AActor* PlayerStart = FindSquadStart(Squad);
		for (auto Operator : Squad->Operators)
		{
			FActorSpawnParameters SpawnParams;
			AT1Character* OpChar = GetWorld()->SpawnActor<AT1Character>(DefaultPawnClass, PlayerStart->GetTransform(), SpawnParams);

			Operator->Pawn = OpChar;

			/*spawn inventory/loadout*/
			SpawnLoadout(OpChar, Operator);

			//GetGameState<AT1GameState>()->OperatorManager->RegisterOperatorPawn(OpChar);
		}
	}	
}

void AT1GameBase::SpawnLoadout(AT1Character* Operator, AOperatorInfo* OperatorInfo)
{
	if (!Operator || !OperatorInfo)
		return;

	/*populate and spawn inventory from template*/
	if (UInventoryTemplate* InvTemplate = NewObject<UInventoryTemplate>())
	{
		InvTemplate->Inventory.Add(OperatorInfo->GetPrimaryWeaponClass());


		Operator->InventoryManagerComponent->SpawnInventoryFromTemplate(InvTemplate);
	}


}

AActor* AT1GameBase::FindSquadStart(ASquadInfo* Squad)
{
	UWorld* World = GetWorld();

	/*loop through all player starts*/
	for (TActorIterator<APlayerStart> It(World); It; ++It)
	{
		APlayerStart* Start = *It;
		
		return Start;
	}
	
	return nullptr;
}



//=============================================================
//=======================PLAYER HANDLING=======================
//=============================================================
void AT1GameBase::HandleStartingNewPlayer_Implementation(APlayerController* NewPlayer)
{
	Super::HandleStartingNewPlayer_Implementation(NewPlayer);

	OpenBriefingWidget(NewPlayer);
}

void AT1GameBase::HavePlayersPossessOperators()
{
	for (FConstPlayerControllerIterator Iterator = GetWorld()->GetPlayerControllerIterator(); Iterator; ++Iterator)
	{
		APlayerController* PC = Iterator->Get();
		
		/*skip if non-existant or possessing something already*/
		if (PC == false || PC->GetPawn() != nullptr)
			continue;

		for (auto Squad : GetWorld()->GetSubsystem<UMissionPlannerSubsystem>()->GetSquads())
		{
			for (auto Operator : Squad->Operators)
			{
				if (Operator->Pawn && Operator->Pawn->GetController() == nullptr)
					PC->Possess(Operator->Pawn);
			}
		}
	}
}




//==================================================
//========================UI========================
//==================================================

void AT1GameBase::OpenBriefingWidget(APlayerController* Player)
{
	if (AT1PlayerController* PC = Cast<AT1PlayerController>(Player))
	{
		PC->ClientInitBriefingWidget(BriefingWidgetClass, true);
	}	
}
