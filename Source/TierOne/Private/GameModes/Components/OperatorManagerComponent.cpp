// Copyrighted - Pocket Sized Animations && Micah A. Parker - 2022


#include "GameModes/Components/OperatorManagerComponent.h"
#include "MissionPlanner/Subsystem/MissionPlannerSubsystem.h"

/*operators*/
#include "Operators/OperatorInfo.h"
#include "Operators/SquadInfo.h"

/*file-directory*/
#include "Misc/FileHelper.h"
#include "HAL/FileManagerGeneric.h"

/*json*/
#include "Serialization/JsonSerializer.h"
#include "JsonObjectConverter.h"
#include "Dom/JsonObject.h"
#include "Serialization/JsonReader.h"

#include "Templates/SharedPointer.h"

/*network*/
#include "Net/UnrealNetwork.h"


void UOperatorManagerComponent::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(UOperatorManagerComponent, OperatorRoster);
	DOREPLIFETIME(UOperatorManagerComponent, Squads);
}

// Sets default values for this component's properties
UOperatorManagerComponent::UOperatorManagerComponent()
{
	/*ticking*/
	PrimaryComponentTick.bCanEverTick = false;
	/*replication*/
	SetIsReplicatedByDefault(true);	
}


void UOperatorManagerComponent::BeginPlay()
{
	Super::BeginPlay();		

	/*create default squad (so we have at least one)*/	
	/*if (GetOwner()->HasAuthority())
		Squads.Add(GetWorld()->SpawnActor<ASquadInfo>(ASquadInfo::StaticClass()));*/

	/*if (Squads[0])
		Squads[0]->OnRosterChange.AddDynamic(this, &UOperatorManagerComponent::OnReceiveSquadChange);*/
	
	//UE_LOG(LogTemp, Warning, TEXT("FILEPATH : %s"), *GetOperatorSaveDirectory());
//	TArray<FString> OperatorFiles = GetOperatorsJson();
}



void UOperatorManagerComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

FString UOperatorManagerComponent::GetOperatorSaveDirectory()
{
	return FPaths::ProjectSavedDir() + "Operators";
}

TArray<FString> UOperatorManagerComponent::GetOperatorsJson()
{
	IFileManager& FileManager = IFileManager::Get();	
	
	TArray<FString> OperatorJson;
	TArray<FString> FileResults;
	FileManager.FindFiles(FileResults, *(GetOperatorSaveDirectory() + "/*" + FileExtension), true, false);
	UE_LOG(LogTemp, Warning, TEXT("SEARCHING FOR OPERATORS...."));
	for (auto OperatorFileName : FileResults)
	{		
		UE_LOG(LogTemp, Warning, TEXT("%s"), *OperatorFileName);
		FString FilePath = GetOperatorSaveDirectory() + "/" + OperatorFileName;
		FString FileData = "";
		FFileHelper::LoadFileToString(FileData, *FilePath);

		OperatorJson.Add(FileData);
		OperatorRoster.Add(GetOperatorInfo(FileData));
		UE_LOG(LogTemp, Warning, TEXT("%s"), *FileData);
	}

	return OperatorJson;
}

AOperatorInfo* UOperatorManagerComponent::GetOperatorInfo(FString JsonString)
{
	if (JsonString.IsEmpty())
		return nullptr;
	
	AOperatorInfo* NewOperatorInfo = GetWorld()->SpawnActor<AOperatorInfo>(AOperatorInfo::StaticClass());
	NewOperatorInfo->LoadFromJSON(JsonString);	
	
	return NewOperatorInfo;	
}

bool UOperatorManagerComponent::AddOperatorToSquad(AOperatorInfo* Operator, ASquadInfo* Squad)
{
	if (!Operator || !Squad)
		return false;

	/*find the appropriate squad*/
	int32 SquadIndex;
	Squads.Find(Squad, SquadIndex);

	if (SquadIndex > -1) 
	{
		if(Squads[SquadIndex]->AddOperator(Operator))
			return true;
	}		

	return false;
}

/*SquadsHaveAnyOperators() - simply returns true if there is at least 1 operator assigned across all squads*/
bool UOperatorManagerComponent::SquadsHaveAnyOperators()
{
	if (Squads.Num() <= 0)
		return false;

	for (auto Squad : Squads)
	{
		if(Squad->Operators.Num() > 0)
			return true;
	}
	
	return false;
}

ASquadInfo* UOperatorManagerComponent::GetSquad(int32 Index)
{
	if(Squads.IsValidIndex(Index))
		return Squads[Index];
	else
		return nullptr;
}

void UOperatorManagerComponent::OnReceiveSquadChange()
{
	
	
	//if (OnSquadChange.IsBound())
	//	OnSquadChange.Broadcast();

	//GetWorld()->GetSubsystem<UMissionPlannerSubsystem>()->UpdateRoster(OperatorRoster);
}

void UOperatorManagerComponent::OnRep_RosterUpdated()
{
	OnReceiveSquadChange();
}



//=====================================
//================PAWNS================
//=====================================

bool UOperatorManagerComponent::RegisterOperatorPawn(AT1Character* Pawn)
{
	OperatorPawns.AddUnique(Pawn);
	
	return true;
}

TArray<AT1Character*> UOperatorManagerComponent::GetOperatorPawns()
{
	return OperatorPawns;
}