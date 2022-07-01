// Copyrighted - Pocket Sized Animations && Micah A. Parker - 2022


#include "Missions/MissionManager.h"
#include "Missions/MissionInfo.h"


void AMissionManager::BeginPlay()
{
	Super::BeginPlay();

	LoadMissionsList();
}

void AMissionManager::LoadMissionsList()
{
	IFileManager& FileManager = IFileManager::Get();

	TArray<FString> MissionsJson;
	TArray<FString> FileResults;
	FileManager.FindFilesRecursive(FileResults, *(GetMissionsDirectory()),*("/*" + FileExtension), true, false);

	UE_LOG(LogTemp, Warning, TEXT("SEARCHING FOR MISSIONS...."));
	for (auto Mission : FileResults)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s"), *Mission);
		FString FileData = "";
		FFileHelper::LoadFileToString(FileData, *Mission);

		MissionsList.Add(GetMissionInfo(FileData));
		UE_LOG(LogTemp, Warning, TEXT("%s"), *FileData);
	}
}

FString AMissionManager::GetMissionsDirectory()
{

	return FPaths::ProjectContentDir() + "Missions";
}

AMissionInfo* AMissionManager::GetMissionInfo(FString JsonData)
{
	if (JsonData.IsEmpty())
		return nullptr;

	AMissionInfo* NewMissionInfo = GetWorld()->SpawnActor<AMissionInfo>(AMissionInfo::StaticClass());
	NewMissionInfo->LoadFromJSON(JsonData);

	return NewMissionInfo;
}
