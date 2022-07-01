// Copyrighted - Pocket Sized Animations && Micah A. Parker - 2022


#include "Missions/MissionInfo.h"
#include "EngineUtils.h"
#include "Engine/Texture2D.h"


void AMissionInfo::LoadFromJSON(FString JsonData)
{
	if (JsonData.IsEmpty())
		return;

	TSharedRef<TJsonReader<TCHAR>> JsonReader = TJsonReaderFactory<TCHAR>::Create(JsonData);
	TSharedPtr<FJsonObject> JsonObject = MakeShareable(new FJsonObject);

	if (FJsonSerializer::Deserialize(JsonReader, JsonObject) && JsonObject.IsValid())
	{
		Name = JsonObject->GetStringField("name");
		Summary = JsonObject->GetStringField("summary");
		MapName = (FName)JsonObject->GetStringField("mapName");
		LoadPreviewImage(JsonObject->GetStringField("previewImgURL"));

		TSharedPtr<FJsonObject> LocationObject = JsonObject->GetObjectField("location");
		if (LocationObject)
		{
			Region = LocationObject->GetStringField("region");
			Country = GetCountryFromString(LocationObject->GetStringField("country"));
		}
	}
}

ECountry AMissionInfo::GetCountryFromString(FString CountryString)
{
	if (CountryString == "United States" || CountryString == "US" || CountryString == "United States of America")
		return ECountry::UnitedStates;

	if (CountryString == "Russia" || CountryString == "RU")
		return ECountry::Russia;


	return ECountry();
}


void AMissionInfo::LoadPreviewImage(FString TexturePath)
{
	if (TexturePath.IsEmpty())
		return;

	UE_LOG(LogTemp, Warning, TEXT("Looking for Preview Image..."));

	TArray<UObject*> Objs;
	EngineUtils::FindOrLoadAssetsByPath(TexturePath, Objs, EngineUtils::ATL_Regular);
	for (auto asset : Objs)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s"), *GetNameSafe(asset));

		if (UTexture2D* Texture = Cast<UTexture2D>(asset))
			PreviewImage = Texture;
	}
}

FName AMissionInfo::GetMapName()
{
	return MapName;	
}

//UPausScene::UPausScene(const class FObjectInitializer& OI) : Super(OI)
//{
//	TArray<UObject*> MeshAssets;
//	EngineUtils::FindOrLoadAssetsByPath(TEXT("/Game/UI/Artwork/Weapons/ComboImages"), MeshAssets, EngineUtils::ATL_Regular);
//	for (auto asset : MeshAssets)
//	{
//		UTexture2D* texture = Cast<UTexture2D>(asset);
//		if (texture != nullptr)
//			// do something with the mesh, create a component with it, etc.
//			FoundComboTextures.Add(texture);
//	}
//}