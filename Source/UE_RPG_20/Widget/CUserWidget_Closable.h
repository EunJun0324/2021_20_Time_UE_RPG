#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CUserWidget_Closable.generated.h"

UENUM(BlueprintType)
enum class EInputModeType : uint8
{ IM_Defalut , IM_GameOnly, IM_UIOnly, IM_GameAndUI };

DECLARE_MULTICAST_DELEGATE_OneParam(FWndEventSignature, class UCUserWidget_Closable*)

UCLASS()
class UE_RPG_20_API UCUserWidget_Closable : public UUserWidget
{
	GENERATED_BODY()

public :
	UPROPERTY()
		UCUserWidget_Closable* ParentWnd;

	UPROPERTY()
		bool bClose;

protected :
	UPROPERTY(meta = (BindWidget))
		class UButton* CloseButton;

protected :
	virtual void NativeConstruct() override;

public :
	UFUNCTION()
		void CloseThisWidget();

	UCUserWidget_Closable* CreateChildClosableWidget(
		TSubclassOf<UCUserWidget_Closable> widgetClass,
		bool bUsePrevPostion = false,
		EInputModeType changeInputMode = EInputModeType::IM_Defalut,
		bool bShowMouseCursor = true);

public :
	void SetCloseButton(class UButton* closeButton);
	
	void CloseAllChildWidget();

public:
	FWndEventSignature OnWndCloseEvent;
};
