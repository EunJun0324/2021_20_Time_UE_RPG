#include "Widget/CWidgetController.h"
#include "Global.h"

#include "Components/CanvasPanel.h"


void UCWidgetController::ResetInputMode(bool bForceChange)
{
	if (bForceChange || (AllocatedClosable.Num() == 0))
	{
		switch (DefalutInputMode)
		{
		case EInputModeType::IM_GameOnly:
			PlayerController->SetInputMode(FInputModeGameOnly());
			break;
		case EInputModeType::IM_UIOnly:
			PlayerController->SetInputMode(FInputModeUIOnly());
			break;
		case EInputModeType::IM_GameAndUI:
			PlayerController->SetInputMode(FInputModeGameAndUI());
			break;
		}
	}
}

void UCWidgetController::SaveWidgetPosition(const class UCUserWidget_Closable* closable)
{
}
void UCWidgetController::InitWidgetController()
{
	PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	DefalutInputMode = EInputModeType::IM_GameOnly;
}
class UCUserWidget_Closable* UCWidgetController::CreateClosable(TSubclassOf<UCUserWidget_Closable> wndClass, bool bUsePrevPosition, EInputModeType changeInputMode, bool bShowMoseCursor, float alignmentX, float alignmentY, float anchorMinX, float anchorMinY, float anchorMaxX, float anchorMaxY)
{

}
void UCWidgetController::CloseClosable(bool bAllClose, class UCUserWidget_Closable* closable)
{

}
void UCWidgetController::AddChildWidget(class UUserWidget* childWidget, EInputModeType changeInputMod, bool bShowMoseCursor, float widtg, float height)
{

}
void UCWidgetController::CloseChildWidget(class UUserWidget* childWidget)
{

}
void UCWidgetController::SetHighestPriorityWidget(class UCUserWidget_Closable* closable)
{

}