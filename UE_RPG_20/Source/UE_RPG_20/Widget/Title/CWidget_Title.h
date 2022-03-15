#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CWidget_Title.generated.h"

UCLASS()
class UE_RPG_20_API UCWidget_Title : public UUserWidget
{
	GENERATED_BODY()
	
private :
	UPROPERTY(meta = (BindWidget))
	class UButton* Button_Play;

	UPROPERTY(meta = (BindWidget))
	class UButton* Button_Exit;

	UPROPERTY(meta = (BindWidget))
	class UCWidgetController* WidgetController;

private :
	TSubclassOf<class UCWidget_Exit> Class_ExitWidget;

public :
	UCWidget_Title(const FObjectInitializer& ObjInitializer);

protected :
	virtual void NativeConstruct() override;

private :
	UFUNCTION()
		void PlayButtonClicked();

	UFUNCTION()
		void ExitButtonClicked();
};
