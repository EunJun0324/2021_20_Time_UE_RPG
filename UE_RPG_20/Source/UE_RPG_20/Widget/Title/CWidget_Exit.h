#pragma once

#include "CoreMinimal.h"
#include "Widget/CUserWidget_Closable.h"
#include "CWidget_Exit.generated.h"

UCLASS()
class UE_RPG_20_API UCWidget_Exit : public UCUserWidget_Closable
{
	GENERATED_BODY()
	
private :
	UPROPERTY(meta = (BindWidget))
		class UButton* Button_OK;

	UPROPERTY(meta = (BindWidget))
		class UButton* Button_Quit;

protected :
	virtual void NativeConstruct() override;

private :
	UFUNCTION()
		void OnOKButtonClicked();

	UFUNCTION()
		void OnQuitButtonClicked();
};
