// Copyrighted - Pocket Sized Animations && Micah A. Parker - 2022


#include "Players/T1PlayerController.h"

/*replication*/
#include "Net/UnrealNetwork.h"


/*ui*/
#include "Blueprint/UserWidget.h"




void AT1PlayerController::ClientInitBriefingWidget_Implementation(TSubclassOf<class UUserWidget> WidgetClass, bool bOpen)
{
	if (!WidgetClass)
		return;

	if(BriefingWidget == nullptr || BriefingWidget->GetClass() != WidgetClass)
		BriefingWidget = CreateWidget<UUserWidget>(this, WidgetClass);
	
	if (bOpen)
		ClientOpenBriefingWidget();
}


void AT1PlayerController::ClientOpenBriefingWidget_Implementation()
{
	/*safety check*/
	if (!BriefingWidget)
		return;

	BriefingWidget->AddToViewport();
	SetInputMode(FInputModeUIOnly());
	bShowMouseCursor = true;
}

void AT1PlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	InputComponent->BindAxis("Pitch", this, &AT1PlayerController::Pitch);
	InputComponent->BindAxis("Rotate", this, &AT1PlayerController::Rotate);
}

void AT1PlayerController::Pitch(float Value)
{
	if (Value == 0.0f)
		return;

	AddPitchInput(Value);
}

void AT1PlayerController::Rotate(float Value)
{
	if (Value == 0.0f)
		return;

	AddYawInput(Value);
}
