#include "Level/CLevelScript_Title.h"
#include "Global.h"
#include "Widget/Title/CWidget_Title.h"

ACLevelScript_Title::ACLevelScript_Title()
{ CHelpers::GetClass<UCWidget_Title>(&BP_CWidget_Title, "WidgetBlueprint'/Game/Widget/BP_CWidget_Title.BP_CWidget_Title_C'"); }

void ACLevelScript_Title::BeginPlay()
{
	Super::BeginPlay();

	CreateWidget<UCWidget_Title>(GetWorld(), BP_CWidget_Title)->AddToViewport();

	UGameplayStatics::GetPlayerController(GetWorld(), 0)->SetInputMode(FInputModeUIOnly());
	UGameplayStatics::GetPlayerController(GetWorld(), 0)->bShowMouseCursor = true;
}