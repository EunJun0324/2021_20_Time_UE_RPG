#include "Widget/PlayerWidget/StautusWidget/CWidget_StatusRow.h"
#include "Global.h"
#include "Engine/AssetManager.h"
#include "Engine/StreamableManager.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "Components/Button.h"


void UCWidget_StatusRow::NativeConstruct()
{
	Super::NativeConstruct();

	Button_Plus->OnClicked.AddDynamic(this, &UCWidget_StatusRow::OnPlusButtonClicked);
	Button_Minus->OnClicked.AddDynamic(this, &UCWidget_StatusRow::OnMinusButtonClicked);
}

void UCWidget_StatusRow::InitializeRow(FStatusRowData data)
{
	Text_StatName->SetText(data.Stat);
	
	UTexture2D* image = Cast<UTexture2D>(UAssetManager::GetStreamableManager().LoadSynchronous(data.StatImage));

	Image_Icon->SetBrushFromTexture(image);
}

void UCWidget_StatusRow::OnPlusButtonClicked()
{
	if (OnClickPlusButton.IsBound())
		OnClickPlusButton.Broadcast();

	++Stat;
	Text_Stat->SetText(FText::FromString(FString::FromInt(Stat)));

}

void UCWidget_StatusRow::OnMinusButtonClicked()
{
	if (OnClickMinusButton.IsBound())
		OnClickMinusButton.Broadcast();

	--Stat;
	Text_Stat->SetText(FText::FromString(FString::FromInt(Stat)));
}
