#include "Component/CWidgetComponent.h"
#include "Global.h"
#include "Characters/CPlayer.h"
#include "Widget/CWidgetController.h"
#include "Widget/CUserWidget_Closable.h"
#include "Widget/PlayerWidget/CPlayerWidget.h"
#include "Widget/PlayerWidget/StautusWidget/CWidget_Status.h"

UCWidgetComponent::UCWidgetComponent()
{
	CHelpers::GetClass<UCWidgetController>(&WidgetControllerClass, "WidgetBlueprint'/Game/Widget/BP_CWidgetController.BP_CWidgetController_C'"); 
	CHelpers::GetClass<UCPlayerWidget>(&PlayerWidgetClass, "WidgetBlueprint'/Game/Widget/PlayerWidget/BP_PlayerWidget.BP_PlayerWidget_C'");
	CHelpers::GetClass<UCWidget_Status>(&StatusWidgetClass, "WidgetBlueprint'/Game/Widget/PlayerWidget/Status/BP_CWidget_Status.BP_CWidget_Status_C'");
}


void UCWidgetComponent::BeginPlay()
{
	Super::BeginPlay();

	APlayerController* playerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);

	WidgetController = CreateWidget<UCWidgetController>(playerController, WidgetControllerClass);
	WidgetController->InitWidgetController();
	WidgetController->AddToViewport();

	PlayerWidget = CreateWidget<UCPlayerWidget>(playerController, PlayerWidgetClass);

	WidgetController->AddChildWidget(PlayerWidget, EInputModeType::IM_GameOnly, false);
}

void UCWidgetComponent::OpenStatus()
{
	if (IsValid(StatusWidget)) return;

	StatusWidget = Cast<UCWidget_Status>(WidgetController->CreateClosable(
		StatusWidgetClass, true, EInputModeType::IM_GameAndUI));

	StatusWidget->OnWndCloseEvent.AddLambda(
		[this](class UCUserWidget_Closable* closable)
		{  StatusWidget = nullptr;  });

}

void UCWidgetComponent::CloseStatus()
{
	if (IsValid(StatusWidget))
	{
		StatusWidget->CloseThisWidget();
		StatusWidget = nullptr;
	}
}

void UCWidgetComponent::ToggleStatus()
{
	if (IsValid(StatusWidget)) CloseStatus();
	else OpenStatus();
}