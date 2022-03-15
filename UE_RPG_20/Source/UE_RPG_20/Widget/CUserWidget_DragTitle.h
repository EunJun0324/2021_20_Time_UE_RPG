#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CUserWidget_DragTitle.generated.h"

DECLARE_MULTICAST_DELEGATE(FDraggingEvent)

UCLASS()
class UE_RPG_20_API UCUserWidget_DragTitle : public UUserWidget
{
	GENERATED_BODY()

public :
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Title Text")
		FText TitleText;

private :
	UPROPERTY(meta = (BindWidget))
		class UButton* Button_Draggable;

	UPROPERTY(meta = (BindWidget))
		class UButton* Button_Close;

	UPROPERTY(meta = (BindWidget))
		class UTextBlock* Text_Title;

private :
	UPROPERTY()
		bool bIsDragging;

	UPROPERTY()
	    class UUserWidget* TargetWidget;

protected :
	virtual void NativePreConstruct() override;
	virtual void NativeConstruct() override;
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

public :
	FORCEINLINE void SetTargetWidget(class UUserWidget* targetWidget)
	{ TargetWidget = targetWidget; }

	FORCEINLINE class UButton* GetCloseButton() const
	{ return Button_Close; }

private :
	void DragWidget();

private :
	UFUNCTION()
		void OnWidgetDragStarted();
	UFUNCTION()
		void OnWidgetDragFinished();

public :
	FDraggingEvent OnDraggingStart;

private :
	FVector2D PrevInputPosition;
	FVector2D PrevWidgetPosition;
};
