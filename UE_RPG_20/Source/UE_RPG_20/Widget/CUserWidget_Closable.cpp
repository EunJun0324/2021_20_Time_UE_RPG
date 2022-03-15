#include "Widget/CUserWidget_Closable.h"

#include "Components/CanvasPanelSlot.h"
#include "Components/Button.h"

#include "CWidgetController.h"
#include "CUserWidget_DragTitle.h"

void UCUserWidget_Closable::NativeConstruct()
{
	Super::NativeConstruct();

	WndSize = FVector2D(500.0f, 600.0f);

	DragTitle->SetTargetWidget(this);

	DragTitle->OnDraggingStart.AddLambda(
		[this]() { WidgetController->SetHighestPriorityWidget(this); });

	SetCloseButton(DragTitle->GetCloseButton());
}

void UCUserWidget_Closable::CloseThisWidget()
{
	if (bClose) return;

	WidgetController->CloseClosable(false, this);
}

UCUserWidget_Closable* UCUserWidget_Closable::CreateChildClosableWidget(TSubclassOf<UCUserWidget_Closable> widgetClass, bool bUsePrevPostion, EInputModeType changeInputMode, bool bShowMouseCursor)
{
	auto child = WidgetController->CreateClosable(widgetClass, bUsePrevPostion, changeInputMode, bShowMouseCursor);

	child->ParentWnd = this;

	ChildClosable.Add(child);

	return child;
}

void UCUserWidget_Closable::SetCloseButton(class UButton* closeButton)
{
	(CloseButton = closeButton)->OnClicked.AddDynamic(this, &UCUserWidget_Closable::CloseThisWidget);
}

void UCUserWidget_Closable::CloseAllChildWidget()
{
	if (ChildClosable.Num() == 0) return;

	for (auto child : ChildClosable)
	{
		if (IsValid(child))
		{
			if (child->bClose) continue;

			WidgetController->CloseClosable(false, child);
		}
	}

	ChildClosable.Empty();
}

void UCUserWidget_Closable::DetachFromParent()
{
	if (IsValid(ParentWnd))
		ParentWnd->ChildClosable.Remove(this);
}

UCanvasPanelSlot* UCUserWidget_Closable::GetCanvasPanelSlot() const
{ return Cast<UCanvasPanelSlot>(Slot); }