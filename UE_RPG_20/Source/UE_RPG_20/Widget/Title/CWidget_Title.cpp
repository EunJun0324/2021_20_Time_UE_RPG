#include "Widget/Title/CWidget_Title.h"
#include "Global.h"
#include "Components/Button.h"
#include "Widget/CWidgetController.h"
#include "CWidget_Exit.h"

UCWidget_Title::UCWidget_Title(const FObjectInitializer& ObjInitializer) :
	Super(ObjInitializer)
{
	CHelpers::GetClass<UCWidget_Exit>(&Class_ExitWidget, "WidgetBlueprint'/Game/Widget/BP_CWidget_Exit.BP_CWidget_Exit_C'");
}


void UCWidget_Title::NativeConstruct()
{
	Super::NativeConstruct();

	Button_Play->OnClicked.AddDynamic(this, &UCWidget_Title::PlayButtonClicked);
	Button_Exit->OnClicked.AddDynamic(this, &UCWidget_Title::ExitButtonClicked);

	WidgetController->InitWidgetController();
}

void UCWidget_Title::PlayButtonClicked()
{ UGameplayStatics::OpenLevel(this, "PlayMap"); }

void UCWidget_Title::ExitButtonClicked()
{ WidgetController->CreateClosable(Class_ExitWidget); }