#include "Weapon/CDoAction_Wizard.h"
#include "Global.h"
#include "GameFramework/Character.h"
#include "Component/CStateComponent.h"

UCDoAction_Wizard::UCDoAction_Wizard()
{

}

void UCDoAction_Wizard::BeginPlay(class ACAttachment* InAttachment, class ACharacter* InOwner, const TArray<FDoActionData>& InActionDatas, const TArray<FHitData>& InHitDatas)
{
	Super::BeginPlay(InAttachment, InOwner, InActionDatas, InHitDatas);

}

void UCDoAction_Wizard::Tick(float InDeltaTime)
{
	Super::Tick(InDeltaTime);
}


void UCDoAction_Wizard::DoAction()
{
	Super::DoAction();

	CheckFalse(ActionDatas.Num() > 0);
	CheckFalse(State->IsIdleMode());

	ActionDatas[0].PlayMontage(OwnerCharacter);
}

void UCDoAction_Wizard::Begin_DoAction()
{
	Super::Begin_DoAction();
}

void UCDoAction_Wizard::End_DoAction()
{
	Super::End_DoAction();

	ActionDatas[0].EndAction(OwnerCharacter);
}

void UCDoAction_Wizard::OnFireballBeginOverlap(class AActor* InAttackCauser, class ACharacter* InOtherCharacter)
{
	HitDatas[0].SendDamage(OwnerCharacter, InAttackCauser, InOtherCharacter);
}
