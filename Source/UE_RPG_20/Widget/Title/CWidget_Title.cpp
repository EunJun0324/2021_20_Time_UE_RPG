#include "Widget/Title/CWidget_Title.h"
#include "Global.h"
#include "Components/Button.h"

void UCWidget_Title::NativeConstruct()
{
	Super::NativeConstruct();

	Button_Play->OnClicked.AddDynamic(this, &UCWidget_Title::PlayButtonClicked);
	Button_Exit->OnClicked.AddDynamic(this, &UCWidget_Title::ExitButtonClicked);
}

void UCWidget_Title::PlayButtonClicked()
{ UGameplayStatics::OpenLevel(this, "PlayMap"); }

void UCWidget_Title::ExitButtonClicked()
{
	UKismetSystemLibrary::QuitGame(
		GetWorld(),
		UGameplayStatics::GetPlayerController(GetWorld(), 0),
		EQuitPreference::Quit,
		false
	);
}