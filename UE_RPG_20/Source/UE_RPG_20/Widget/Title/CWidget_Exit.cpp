#include "Widget/Title/CWidget_Exit.h"
#include "Global.h"
#include "Components/Button.h"

void UCWidget_Exit::NativeConstruct()
{
	Super::NativeConstruct();

	WndSize = FVector2D(500.0f, 200.0f);

	Button_OK->OnClicked.AddDynamic(this, &UCWidget_Exit::OnOKButtonClicked);
	Button_Quit->OnClicked.AddDynamic(this, &UCWidget_Exit::OnQuitButtonClicked);
}

void UCWidget_Exit::OnOKButtonClicked()
{
	UKismetSystemLibrary::QuitGame(
		GetWorld(),
		UGameplayStatics::GetPlayerController(GetWorld(), 0),
		EQuitPreference::Quit,
		false
	);
}

void UCWidget_Exit::OnQuitButtonClicked()
{ CloseThisWidget(); } 