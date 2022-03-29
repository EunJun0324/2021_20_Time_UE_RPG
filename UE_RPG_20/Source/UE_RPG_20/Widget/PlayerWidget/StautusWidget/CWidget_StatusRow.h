#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Engine/DataTable.h"
#include "CWidget_StatusRow.generated.h"

USTRUCT(BlueprintType)
struct FStatusRowData : public FTableRowBase
{
	GENERATED_BODY()

public :
	UPROPERTY(EditAnywhere)
		FSoftObjectPath StatImage;

	UPROPERTY(EditAnywhere)
		FText Stat;
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FStatusButtonClicked);

UCLASS()
class UE_RPG_20_API UCWidget_StatusRow : public UUserWidget
{
	GENERATED_BODY()

private:
	UPROPERTY(meta = (BindWidget))
		class UImage* Image_Icon;

	UPROPERTY(meta = (BindWidget))
		class UTextBlock* Text_StatName;

	UPROPERTY(meta = (BindWidget))
		class UTextBlock* Text_Stat;

	UPROPERTY(meta = (BindWidget))
		class UButton* Button_Plus;

	UPROPERTY(meta = (BindWidget))
		class UButton* Button_Minus;

protected:
	virtual void NativeConstruct() override;

public:
	void InitializeRow(FStatusRowData data);

	FORCEINLINE void SetStat(int32 stat) { Stat = stat; };

private :
	UFUNCTION()
		void OnPlusButtonClicked();

	UFUNCTION()
		void OnMinusButtonClicked();

public :
	FStatusButtonClicked OnClickPlusButton;
	FStatusButtonClicked OnClickMinusButton;

private :
	uint32 Stat;

};
