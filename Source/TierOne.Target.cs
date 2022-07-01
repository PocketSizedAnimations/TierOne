// Copyrighted - Pocket Sized Animations && Micah A. Parker - 2022

using UnrealBuildTool;
using System.Collections.Generic;

public class TierOneTarget : TargetRules
{
	public TierOneTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Game;
		DefaultBuildSettings = BuildSettingsVersion.V2;

		ExtraModuleNames.AddRange( new string[] { "TierOne","EquipmentModule","FirstPersonModule", "HealthAndStaminaModule","InteractionsModule", "InventoryModule","WeaponsModule", "Json" } );
	}
}
