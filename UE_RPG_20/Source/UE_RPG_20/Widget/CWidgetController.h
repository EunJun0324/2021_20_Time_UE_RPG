#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CUserWidget_Closable.h"
#include "CWidgetController.generated.h"

UCLASS()
class UE_RPG_20_API UCWidgetController : public UUserWidget
{
	GENERATED_BODY()

private :
	UPROPERTY(meta = (BindWidget))
		class UCanvasPanel* CanvasPanel_Closable;

	UPROPERTY(meta = (BindWidget))
		class UCanvasPanel* CanvasPanel_Widget;

private :
	void ResetInputMode(bool bForceChange = false);

	void ChanageInputMode(EInputModeType inputMode);

	void SaveWidgetPosition(const class UCUserWidget_Closable* closable);

public :
	void InitWidgetController();

	class UCUserWidget_Closable* CreateClosable(
		TSubclassOf<UCUserWidget_Closable> wndClass,
		bool bUsePrevPosition = false,
		EInputModeType changeInputMode = EInputModeType::IM_UIOnly,
		bool bShowMoseCursor = true,
		float alignmentX = 0.5f, float alignmentY = 0.5f,
		float anchorMinX = 0.5f, float anchorMinY = 0.5f,
		float anchorMaxX = 0.5f, float anchorMaxY = 0.5f);

	void CloseClosable(bool bAllClose = false, class UCUserWidget_Closable* closable = nullptr);

	void AddChildWidget(class UUserWidget* childWidget,
		EInputModeType changeInputMode = EInputModeType::IM_UIOnly,
		bool bShowMoseCursor = true,
		float width = 1920.0f, float height = 1080.0f);
	
	void CloseChildWidget(class UUserWidget* childWidget);

	void SetHighestPriorityWidget(class UCUserWidget_Closable* closable);

private :
	EInputModeType DefalutInputMode;

	class APlayerController* PlayerController;

	TArray<class UCUserWidget_Closable*> AllocatedClosable;

	TArray<class UUserWidget*> AllocatedWidget;

	TMap<FString, FVector2D> PrevClosedWndPositions;


};
