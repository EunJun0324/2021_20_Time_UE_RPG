#include "Widget/CUserWidget_Closable.h"

#include "Components/CanvasPanelSlot.h"
#include "Components/Button.h"

#include "CWidgetController.h"

void UCUserWidget_Closable::NativeConstruct()
{
	Super::NativeConstruct();

	SetCloseButton(CloseButton);
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
	closeButton->OnClicked.AddDynamic(this, &UCUserWidget_Closable::CloseThisWidget);
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