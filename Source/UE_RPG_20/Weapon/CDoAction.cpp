#include "Weapon/CDoAction.h"
#include "Global.h"
#include "GameFramework/Character.h"
#include "Component/CStateComponent.h"

UCDoAction::UCDoAction() {}

void UCDoAction::BeginPlay(class ACAttachment* InAttachment, class ACharacter* InOwner, const TArray<FDoActionData>& InActionDatas, const TArray<FHitData>& InHitDatas)
{
	ActionDatas = InActionDatas;
	HitDatas = InHitDatas;

	OwnerCharacter = InOwner;
	World = OwnerCharacter->GetWorld();

	State = CHelpers::GetComponent<UCStateComponent>(OwnerCharacter);
}