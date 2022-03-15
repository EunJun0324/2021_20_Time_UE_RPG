#include "Widget/Title/CWidget_Title.h"
#include "Global.h"
#include "Components/Button.h"
#include "Widget/CWidgetController.h"
#include "CWidget_Exit.h"

UCWidget_Title::UCWidget_Title(const FObjectInitializer& ObjInitializer)
{
	CHelpers::GetClass<UCWidget_Exit>(&Class_ExitWidget, "");
}


void UCWidget_Title::NativeConstruct()
{
	Super::NativeConstruct();

	Button_Play->OnClicked.AddDynamic(this, &UCWidget_Title::PlayButtonClicked);
	Button_Exit->OnClicked.AddDynamic(this, &UCWidget_Title::ExitButtonClicked);
}

void UCWidget_Title::PlayButtonClicked()
{ UGameplayStatics::OpenLevel(this, "PlayMap"); }

void UCWidget_Title::ExitButtonClicked()
{ WidgetController->CreateClosable(Class_ExitWidget); }