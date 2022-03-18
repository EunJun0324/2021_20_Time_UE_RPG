#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CWidget_PlayerState.generated.h"

UCLASS()
class UE_RPG_20_API UCWidget_PlayerState : public UUserWidget
{
	GENERATED_BODY()

public :
	UPROPERTY(EditAnywhere, BlueprintReadWrite, category = "Name")
		FText Name;

private :
	UPROPERTY(meta = (BindWidget))
		class UTextBlock* Text_Level;

	UPROPERTY(meta = (BindWidget))
		class UTextBlock* Text_Name;

	UPROPERTY(meta = (BindWidget))
		class UProgressBar* ProgressBar_Hp;

	UPROPERTY(meta = (BindWidget))
		class UProgressBar* ProgressBar_Mp;

	UPROPERTY(meta = (BindWidget))
		class UProgressBar* ProgressBar_Exp;

protected :
	virtual void NativePreConstruct() override;
	virtual void NativeConstruct()    override;

private :
	void SetLevel(int Level);
	void SetHpPercent(float percent);
	void SetMpPercent(float percent);
	void SetExpPercent(float percent);

};
