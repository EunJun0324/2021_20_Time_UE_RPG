#include "Component/CMontageComponent.h"
#include "Global.h"
#include "GameFramework/Character.h"

UCMontageComponent::UCMontageComponent() {}


void UCMontageComponent::BeginPlay()
{
	Super::BeginPlay();

	OwnerCharacter = Cast<ACharacter>(GetOwner());

	TArray<FMontageData*> datas;

	DataTable->GetAllRows<FMontageData>("", datas);

	for (int32 i = 0; i < (int32)EStateType::Max; i++)
	{
		for (FMontageData* data : datas)
		{
			if ((EStateType)i == data->Type) Datas[i] = data;
		}
	}
}

void UCMontageComponent::PlayHittedMode()
{ PlayAnimMontage(EStateType::Hitted); }

void UCMontageComponent::PlayDeadMode()
{ PlayAnimMontage(EStateType::Dead); }

void UCMontageComponent::PlayAnimMontage(EStateType InType)
{
	CheckNull(OwnerCharacter);

	const FMontageData* data = Datas[(int32)InType];
	if (data && data->Montage)
		OwnerCharacter->PlayAnimMontage(data->Montage, data->PlayRatio, data->SectionName);
}


