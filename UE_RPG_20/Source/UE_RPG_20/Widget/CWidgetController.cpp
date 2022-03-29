#include "Widget/CWidgetController.h"
#include "Global.h"

#include "Components/CanvasPanel.h"
#include "Components/CanvasPanelSlot.h"


void UCWidgetController::ResetInputMode(bool bForceChange)
{
	if (bForceChange || (AllocatedClosable.Num() == 0))
	{
		switch (DefalutInputMode)
		{
		case EInputModeType::IM_GameOnly:
			PlayerController->SetInputMode(FInputModeGameOnly());
			PlayerController->bShowMouseCursor = false;
			break;
		case EInputModeType::IM_UIOnly:
			PlayerController->SetInputMode(FInputModeUIOnly());
			PlayerController->bShowMouseCursor = true;
			break;
		case EInputModeType::IM_GameAndUI:
			PlayerController->SetInputMode(FInputModeGameAndUI());
			PlayerController->bShowMouseCursor = true;
			break;
		}
	}
}

void UCWidgetController::ChanageInputMode(EInputModeType inputMode)
{
	switch (inputMode)
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

void UCWidgetController::SaveWidgetPosition(const class UCUserWidget_Closable* closable)
{
	FString wndClsName = closable->GetClass()->GetName();
	FVector2D wndPosition = closable->GetCanvasPanelSlot()->GetPosition();

	if (PrevClosedWndPositions.Contains(wndClsName))
		PrevClosedWndPositions[wndClsName] = wndPosition;
	else PrevClosedWndPositions.Add(wndClsName, wndPosition);

}
void UCWidgetController::InitWidgetController()
{
	PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	DefalutInputMode = EInputModeType::IM_GameOnly;
}
class UCUserWidget_Closable* UCWidgetController::CreateClosable(TSubclassOf<UCUserWidget_Closable> wndClass, bool bUsePrevPosition, EInputModeType changeInputMode, bool bShowMoseCursor, float alignmentX, float alignmentY, float anchorMinX, float anchorMinY, float anchorMaxX, float anchorMaxY)
{
	UCUserWidget_Closable* newClosable = CreateWidget<UCUserWidget_Closable>(this, wndClass);
	newClosable->SetWidgetController(this);

	AllocatedClosable.Add(newClosable);

	CanvasPanel_Closable->AddChild(newClosable);

	auto canvasPanelSlot = newClosable->GetCanvasPanelSlot();
	canvasPanelSlot->SetAnchors(FAnchors(anchorMinX, anchorMinY, anchorMaxX, anchorMaxY));
	canvasPanelSlot->SetAlignment(FVector2D(alignmentX, alignmentY));
	canvasPanelSlot->SetSize(newClosable->GetWndSize());

	if (bUsePrevPosition)
	{
		if (PrevClosedWndPositions.Contains(wndClass->GetName()))
			canvasPanelSlot->SetPosition(PrevClosedWndPositions[wndClass->GetName()]);
	}

	ChanageInputMode(changeInputMode);
	PlayerController->bShowMouseCursor = bShowMoseCursor;

	return newClosable;
}
void UCWidgetController::CloseClosable(bool bAllClose, class UCUserWidget_Closable* closable)
{
	if (AllocatedClosable.Num() == 0) return;

	if (bAllClose)
	{
		for (UCUserWidget_Closable* elem : AllocatedClosable)
		{
			if (elem->bClose) continue;
			
			elem->bClose = true;

			if (elem->OnWndCloseEvent.IsBound())
				elem->OnWndCloseEvent.Broadcast(elem);

			elem->CloseAllChildWidget();

			SaveWidgetPosition(elem);

			elem->DetachFromParent();

			CanvasPanel_Closable->RemoveChild(elem);
		}

		AllocatedClosable.Empty();
	}
	else
	{
		closable = (closable != nullptr) ?
			closable :
			AllocatedClosable[AllocatedClosable.Num() - 1];

		if (!closable->bClose)
		{
			closable->bClose = true;

			if (closable->OnWndCloseEvent.IsBound())
				closable->OnWndCloseEvent.Broadcast(closable);

			AllocatedClosable.Remove(closable);

			closable->DetachFromParent();

			CanvasPanel_Closable->RemoveChild(closable);
		}
	}

	ResetInputMode();
}
void UCWidgetController::AddChildWidget(class UUserWidget* childWidget, EInputModeType changeInputMode, bool bShowMoseCursor, float width, float height)
{
	if (childWidget == nullptr) return;

	CanvasPanel_Closable->AddChild(childWidget);

	Cast<UCanvasPanelSlot>(childWidget->Slot)->SetSize(FVector2D(width, height));

	ChanageInputMode(changeInputMode);
	PlayerController->bShowMouseCursor = bShowMoseCursor;

	AllocatedWidget.Add(childWidget);
}
void UCWidgetController::CloseChildWidget(class UUserWidget* childWidget)
{
	if (childWidget == nullptr) return;

	AllocatedWidget.Remove(childWidget);

	CanvasPanel_Closable->RemoveChild(childWidget);

	ResetInputMode();
}
void UCWidgetController::SetHighestPriorityWidget(UCUserWidget_Closable* closable)
{
	UCanvasPanelSlot* slot = closable->GetCanvasPanelSlot();

	if (CanvasPanel_Closable->GetChildIndex(closable) !=
		CanvasPanel_Closable->GetSlots().Num() - 1)
	{
		FVector2D prevPostion   = slot->GetPosition();
		FAnchors  prevAnchors   = slot->GetAnchors();
		FVector2D prevAlignment = slot->GetAlignment();

		CanvasPanel_Closable->AddChild(closable);

		slot = closable->GetCanvasPanelSlot();
		slot->SetAnchors(prevAnchors);
		slot->SetAlignment(prevAlignment);
		slot->SetPosition(prevPostion);
		slot->SetSize(closable->GetWndSize());
	}
}