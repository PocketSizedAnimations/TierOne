// Copyrighted - Pocket Sized Animations && Micah A. Parker - 2022


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


void UMissionPlannerSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);

	InitializeRoster();
	InitializeSquads();
}

void UMissionPlannerSubsystem::Deinitialize()
{
	Super::Deinitialize();
}


//==============================
//============ROSTER============
//==============================

void UMissionPlannerSubsystem::InitializeRoster()
{
	/*server-check*/
	if (GetWorld()->GetNetMode() == NM_Client)
		return;

	LoadRosterFromDisk();
}

TArray<AOperatorInfo*>& UMissionPlannerSubsystem::GetRoster()
{
	return Roster;
}

void UMissionPlannerSubsystem::UpdateRoster(TArray<AOperatorInfo*>& NewRoster)
{
	Roster = NewRoster;
}

//==================================
//==============SQUADS==============
//==================================

void UMissionPlannerSubsystem::InitializeSquads()
{
	/*server-check*/
	if (GetWorld()->GetNetMode() == NM_Client)
		return;

	/*create default squad (so we have at least one)*/
	AddSquad(GetWorld()->SpawnActor<ASquadInfo>(ASquadInfo::StaticClass()));
	SetCurrentSquad(GetSquadByIndex(0));
}

ASquadInfo* UMissionPlannerSubsystem::GetCurrentSquad()
{
	return CurrentSelectedSquad;
}

void UMissionPlannerSubsystem::SetCurrentSquad(ASquadInfo* Squad)
{
	CurrentSelectedSquad = Squad;
}

void UMissionPlannerSubsystem::AddSquad(ASquadInfo* Squad)
{	
	if (!Squad)
		return;

	Squads.Add(Squad);
	Squad->OnRosterChange.AddDynamic(this, &UMissionPlannerSubsystem::OnSquadUpdated);
}

TArray<class ASquadInfo*>& UMissionPlannerSubsystem::GetSquads()
{
	return Squads;
}

ASquadInfo* UMissionPlannerSubsystem::GetSquadByIndex(uint8 index)
{
	if (Squads.IsValidIndex(index))
		return Squads[index];
	else
		return nullptr;
}

void UMissionPlannerSubsystem::OnSquadUpdated(ASquadInfo* Squad)
{
	
	if (OnSquadChange.IsBound())
		OnSquadChange.Broadcast(Squad);
}

bool UMissionPlannerSubsystem::SquadsHaveAnyOperators()
{
	if (Squads.Num() <= 0)
		return false;

	for (auto Squad : Squads)
	{
		if (Squad->Operators.Num() > 0)
			return true;
	}

	return false;
}


//=================================
//============OPERATORS============
//=================================

AOperatorInfo* UMissionPlannerSubsystem::GetCurrentOperator()
{
	return CurrentSelectedOperator;
}



void UMissionPlannerSubsystem::SetCurrentOperator(AOperatorInfo* Operator)
{
	if(Operator != nullptr)
		CurrentSelectedOperator = Operator;
}


//==============================
//===========LOADOUTS===========
//==============================


UWeaponSelectionDataAsset* UMissionPlannerSubsystem::GetCurrentPrimary()
{
	if (!GetCurrentOperator())
		return nullptr;

	return GetCurrentOperator()->PrimaryWeapon;
}


//================================
//===========SAVE FILES===========
//================================

FString UMissionPlannerSubsystem::GetOperatorSaveDirectory()
{
	return FPaths::ProjectSavedDir() + "Operators";
}

AOperatorInfo* UMissionPlannerSubsystem::GetOperatorInfoFromJSON(FString JsonString)
{
	if (JsonString.IsEmpty())
		return nullptr;

	AOperatorInfo* NewOperatorInfo = GetWorld()->SpawnActor<AOperatorInfo>(AOperatorInfo::StaticClass());
	NewOperatorInfo->LoadFromJSON(JsonString);

	return NewOperatorInfo;
}

void UMissionPlannerSubsystem::LoadRosterFromDisk()
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
		Roster.Add(GetOperatorInfoFromJSON(FileData));
		UE_LOG(LogTemp, Warning, TEXT("%s"), *FileData);
	}

	//return OperatorJson;
}
