// Copyrighted - Pocket Sized Animations && Micah A. Parker - 2022


#include "Operators/OperatorInfo.h"

/*loadout*/
#include "Weapons/Assets/WeaponSelectionDataAsset.h"
#include "WeaponsModule/Public/Actors/Weapon.h"
#include "WeaponsModule/Public/Actors/Firearm.h"

/*json*/
#include "Serialization/JsonSerializer.h"
#include "JsonObjectConverter.h"
#include "Dom/JsonObject.h"
#include "Serialization/JsonReader.h"
#include "Templates/SharedPointer.h"

AOperatorInfo::AOperatorInfo()
{
	/*replication*/
	bReplicates = true;
}

TSubclassOf<AActor> AOperatorInfo::GetPrimaryWeaponClass()
{
	if(!PrimaryWeapon)
		return TSubclassOf<AActor>();

	return PrimaryWeapon->WeaponBlueprintClass;
}

void AOperatorInfo::LoadFromJSON(FString JsonData)
{
	if (JsonData.IsEmpty())
		return;

	TSharedRef<TJsonReader<TCHAR>> JsonReader = TJsonReaderFactory<TCHAR>::Create(JsonData);
	TSharedPtr<FJsonObject> JsonObject = MakeShareable(new FJsonObject);

	if (FJsonSerializer::Deserialize(JsonReader, JsonObject) && JsonObject.IsValid())
	{
		FirstName = JsonObject->GetStringField("firstname");
		LastName = JsonObject->GetStringField("lastname");
		Nationality = JsonObject->GetStringField("nationality");
		IDTag = JsonObject->GetStringField("id");
		Age = (uint8)JsonObject->GetNumberField("age");

		/*status*/
		FString _status = JsonObject->GetStringField("status");
		if (_status == "Injured")
			Status = EOperatorStatus::Injured;
		else if (_status == "Deceased")
			Status = EOperatorStatus::Deceased;
		else if (_status == "Locked")
			Status = EOperatorStatus::Locked;
		else
			Status = EOperatorStatus::Available;

		TSharedPtr<FJsonObject> _stats = JsonObject->GetObjectField("stats");
		if (_stats)
		{
			Stats.Assault = _stats->GetNumberField("assault");
			Stats.Stealth = _stats->GetNumberField("stealth");
			Stats.Marksmanship = _stats->GetNumberField("marksmanship");
			Stats.Demolitions = _stats->GetNumberField("demolitions");
			Stats.Electronics = _stats->GetNumberField("electronics");
			Stats.Grenades = _stats->GetNumberField("grenades");
			Stats.Aggression = _stats->GetNumberField("aggression");
			Stats.Leadership = _stats->GetNumberField("leadership");
			Stats.Stamina = _stats->GetNumberField("stamina");
		}

		UE_LOG(LogTemp, Warning, TEXT("FIRSTNAME : %s"), *FirstName);
		UE_LOG(LogTemp, Warning, TEXT("LASTNAME : %s"), *LastName);		
		UE_LOG(LogTemp, Warning, TEXT("status : %s"), *_status);

		/*TArray<TSharedPtr<FJsonValue>> JsonValueArray = JsonObject->GetArrayField("firstname");

		for (int32 i = 0; i < JsonValueArray.Num(); i++)
		{
			TSharedPtr<FJsonValue> JsonValue = JsonValueArray[i];
			TSharedPtr<FJsonObject> JsonValueObject = JsonValue->AsObject();

			AOperatorInfo* NewOperator;
			NewOperator->FirstName = JsonValueObject->GetStringField(TEXT("firstname"));
		}*/
	}
	
}
