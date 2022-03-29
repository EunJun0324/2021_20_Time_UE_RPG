#include "Widget/PlayerWidget/StautusWidget/CWidget_Status.h"
#include "Global.h"
#include "Characters/CPlayer.h"
#include "Components/ScrollBox.h"
#include "CWidget_StatusRow.h"


UCWidget_Status::UCWidget_Status(const FObjectInitializer& ObjInitializer) : Super(ObjInitializer)
{
	CHelpers::GetClass<UCWidget_StatusRow>(&StatusRow_Class, "WidgetBlueprint'/Game/Widget/PlayerWidget/Status/BP_CWidget_StatusRow.BP_CWidget_StatusRow_C'");
}

void UCWidget_Status::NativeConstruct()
{
	Super::NativeConstruct();

	TArray<FStatusRowData*> data;

	DT_StatusRowData->GetAllRows<FStatusRowData>("", data);

	ACharacter* player = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
	UCStatusComponent* status = CHelpers::GetComponent<UCStatusComponent>(player);

	for (uint32 i = 0; i < (int32)EStatusType::Max; i++)
	{
		Rows.Add(CreateWidget<UCWidget_StatusRow>(this, StatusRow_Class));

		(Rows[i])->InitializeRow(*(data[i]));

		ScrollBox_List->AddChild(Rows[i]);
	}

	Rows[(int32)EStatusType::Hp]->OnClickPlusButton.AddDynamic(status, &UCStatusComponent::AddMaxHealth);
	Rows[(int32)EStatusType::Hp]->OnClickMinusButton.AddDynamic(status, &UCStatusComponent::SubMaxHealth);
}