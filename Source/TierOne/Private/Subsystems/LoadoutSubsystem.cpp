// Copyrighted - Pocket Sized Animations && Micah A. Parker - 2022


#include "Subsystems/LoadoutSubsystem.h"
#include "GameModes/T1GameInstance.h"
#include "Equipment/LoadoutTemplate.h"

void ULoadoutSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);

	if (UT1GameInstance* GI = Cast<UT1GameInstance>(GetGameInstance()))
	{
		if (GI->DefaultWeaponLoadout)
		{
			for (auto Weapon : GI->DefaultWeaponLoadout->AssaultRifles)
			{
				PrimaryWeapons.Add(Weapon);
			}
		}
	}
}

void ULoadoutSubsystem::Deinitialize()
{
	Super::Deinitialize();
}
