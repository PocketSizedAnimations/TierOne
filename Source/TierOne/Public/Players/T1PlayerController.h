// Copyrighted - Pocket Sized Animations && Micah A. Parker - 2022

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "T1PlayerController.generated.h"

/**
 * 
 */
UCLASS()
class TIERONE_API AT1PlayerController : public APlayerController
{
	GENERATED_BODY()
public:


	/*ui*/
	UPROPERTY()
		class UUserWidget* BriefingWidget;
	UPROPERTY()
		class UUserWidget* RosterWidet;

	//=============================================================================================
	//==========================================FUNCTIONS==========================================
	//=============================================================================================
	
	//=============================
	//============INPUT============
	//=============================
	virtual void SetupInputComponent();

	UFUNCTION()
		virtual void Pitch(float Value);
	UFUNCTION()
		virtual void Rotate(float Value);

	//==============================
	//==============UI==============
	//==============================
	UFUNCTION(Client, Reliable, BlueprintCallable, Category = "UI")
		void ClientInitBriefingWidget(TSubclassOf<class UUserWidget> WidgetClass, bool bOpen = true);
	UFUNCTION(Client, Reliable, BlueprintCallable, Category = "UI")
		void ClientOpenBriefingWidget();
};
