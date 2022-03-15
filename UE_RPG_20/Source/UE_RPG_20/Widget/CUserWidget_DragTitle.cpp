#include "Widget/CUserWidget_DragTitle.h"

#include "Components/TextBlock.h"
#include "Components/Button.h"
#include "Components/CanvasPanelSlot.h"

#include "Blueprint/WidgetLayoutLibrary.h"


void UCUserWidget_DragTitle::NativePreConstruct()
{
	Super::NativePreConstruct();

	Text_Title->SetText(TitleText);
}

void UCUserWidget_DragTitle::NativeConstruct()
{
	Super::NativeConstruct();

	Button_Draggable->OnPressed.AddDynamic(this, &UCUserWidget_DragTitle::OnWidgetDragStarted);
	Button_Draggable->OnReleased.AddDynamic(this, &UCUserWidget_DragTitle::OnWidgetDragFinished);
}

void UCUserWidget_DragTitle::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	DragWidget();
}

void UCUserWidget_DragTitle::DragWidget()
{
	if (!bIsDragging) return;

	if (!IsValid(TargetWidget)) return;

	FVector2D mousePosition = UWidgetLayoutLibrary::GetMousePositionOnViewport(this);

	UCanvasPanelSlot* slot = Cast<UCanvasPanelSlot>(TargetWidget->Slot);
	
	slot->SetPosition(PrevWidgetPosition + (mousePosition - PrevInputPosition));

	PrevInputPosition = mousePosition;

	PrevWidgetPosition = slot->GetPosition();
}

void UCUserWidget_DragTitle::OnWidgetDragStarted()
{
	if (!IsValid(TargetWidget)) return;

	PrevInputPosition = UWidgetLayoutLibrary::GetMousePositionOnViewport(this);

	PrevWidgetPosition = Cast<UCanvasPanelSlot>(TargetWidget->Slot)->GetPosition();

	if (OnDraggingStart.IsBound())
		OnDraggingStart.Broadcast();

	bIsDragging = true;
}

void UCUserWidget_DragTitle::OnWidgetDragFinished()
{
	if (!IsValid(TargetWidget)) return;

	bIsDragging = false;
}