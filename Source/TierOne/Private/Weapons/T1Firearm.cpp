// Copyrighted - Pocket Sized Animations && Micah A. Parker - 2022


#include "Weapons/T1Firearm.h"

/*components*/
#include "FirstPersonModule/Public/Components/FirstPersonItemComponent.h"
#include "InventoryModule/Public/Components/InventoryItemComponent.h"

AT1Firearm::AT1Firearm(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{
	FirstPersonItemComponent = ObjectInitializer.CreateDefaultSubobject<UFirstPersonItemComponent>(this, TEXT("First Person Item Component"));
	if (FirstPersonItemComponent)
	{

	}
}

void AT1Firearm::OnEquipBegin(AActor* Actor, UInventoryItemComponent* ItemComp, UInventoryManagerComponent* InvManager, AActor* Equipper)
{
	Super::OnEquipBegin(Actor, ItemComp, InvManager, Equipper);

	/*tells the component to go ahead and attach to the first person view model*/
	FirstPersonItemComponent->AttachFirstPersonMesh();
}
