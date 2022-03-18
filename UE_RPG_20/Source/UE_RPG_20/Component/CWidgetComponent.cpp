#include "Component/CWidgetComponent.h"
#include "Global.h"
#include "Characters/CPlayer.h"
#include "Widget/CWidgetController.h"
#include "Widget/CUserWidget_Closable.h"
#include "Widget/PlayerWidget/CPlayerWidget.h"

UCWidgetComponent::UCWidgetComponent()
{
	CHelpers::GetClass<UCWidgetController>(&WidgetControllerClass, "WidgetBlueprint'/Game/Widget/BP_CWidgetController.BP_CWidgetController_C'"); 
	CHelpers::GetClass<UCPlayerWidget>(&PlayerWidgetClass, "WidgetBlueprint'/Game/Widget/PlayerWidget/BP_PlayerWidget.BP_PlayerWidget_C'");
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


