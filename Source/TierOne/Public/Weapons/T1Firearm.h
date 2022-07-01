// Copyrighted - Pocket Sized Animations && Micah A. Parker - 2022

#pragma once

#include "CoreMinimal.h"
#include "Actors/Firearm.h"
#include "T1Firearm.generated.h"

/**
 * 
 */
UCLASS(abstract)
class TIERONE_API AT1Firearm : public AFirearm
{
	GENERATED_BODY()
public:

	/*creates an automatic first person model for our items*/
	UPROPERTY(VisibleAnywhere)
		class UFirstPersonItemComponent* FirstPersonItemComponent;
	
	//===================================================================================
	//=====================================FUNCTIONS=====================================
	//===================================================================================
	AT1Firearm(const FObjectInitializer& ObjectInitializer);


	virtual void OnEquipBegin(AActor* Actor, UInventoryItemComponent* ItemComp, class UInventoryManagerComponent* InvManager, AActor* Equipper) override;


};
