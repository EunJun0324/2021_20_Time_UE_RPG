#include "Widget/CUserWidget_Closable.h"
#include "Components/Button.h"

void UCUserWidget_Closable::NativeConstruct()
{
	Super::NativeConstruct();

	SetCloseButton(CloseButton);
}

void UCUserWidget_Closable::CloseThisWidget()
{
}

UCUserWidget_Closable* UCUserWidget_Closable::CreateChildClosableWidget(TSubclassOf<UCUserWidget_Closable> widgetClass, bool bUsePrevPostion, EInputModeType changeInputMode, bool bShowMouseCursor)
{

}

void UCUserWidget_Closable::SetCloseButton(class UButton* closeButton)
{
	closeButton->OnClicked.AddDynamic(this, &UCUserWidget_Closable::CloseThisWidget);
}

void UCUserWidget_Closable::CloseAllChildWidget()
{

}