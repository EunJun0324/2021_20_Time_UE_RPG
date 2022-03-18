#include "Widget/PlayerWidget/CWidget_PlayerState.h"
#include "Global.h"
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"
#include "Characters/CPlayer.h"
#include "Component/CStatusComponent.h"

void UCWidget_PlayerState::NativePreConstruct()
{
	Super::NativePreConstruct();

	Text_Name->SetText(Name);
}

void UCWidget_PlayerState::NativeConstruct()
{
	Super::NativeConstruct();
	
	ACPlayer* owner = Cast<ACPlayer>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));

	UCStatusComponent* status = CHelpers::GetComponent<UCStatusComponent>(owner);

	status->OnChangeHpEvent.AddDynamic(this, &UCWidget_PlayerState::SetHpPercent);

	SetLevel(1);
	SetHpPercent(1.0f);
	SetMpPercent(1.0f);
	SetExpPercent(1.0f);
}

void UCWidget_PlayerState::SetLevel(int Level)
{ Text_Level->SetText(FText::FromString(FString(TEXT("Lv ")) + FString::FromInt(Level))); }

void UCWidget_PlayerState::SetHpPercent(float percent)
{ ProgressBar_Hp->SetPercent(percent); }

void UCWidget_PlayerState::SetMpPercent(float percent)
{ ProgressBar_Mp->SetPercent(percent); }

void UCWidget_PlayerState::SetExpPercent(float percent)
{ ProgressBar_Exp->SetPercent(percent); }
