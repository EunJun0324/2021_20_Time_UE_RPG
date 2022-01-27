#include "Weapon/CDoAction_Combo.h"
#include "Global.h"
#include "GameFramework/Character.h"
#include "Component/CStateComponent.h"

void UCDoAction_Combo::DoAction()
{
	Super::DoAction();

	CheckFalse(ActionDatas.Num() > 0);

	if (bEnable == true)
	{
		bExist = true;
		bEnable = false;

		return;
	}

	CheckFalse(State->IsIdleMode());
	State->SetActionMode();

	ActionDatas[Index].PlayMontage(OwnerCharacter);
}
void UCDoAction_Combo::Begin_DoAction()
{
	Super::Begin_DoAction();

	CheckFalse(bExist);
	bExist = false;

	Index++;

	ActionDatas[Index].PlayMontage(OwnerCharacter);

}
void UCDoAction_Combo::End_DoAction()
{
	Super::End_DoAction();
	ActionDatas[Index].EndAction(OwnerCharacter);
	Index = 0;
}
void UCDoAction_Combo::OnAttachmentBeginOverlap(class ACharacter* InAttacker, class AActor* InAttackCauser, class ACharacter* InOtherCharacter)
{
	Super::OnAttachmentBeginOverlap(InAttacker, InAttackCauser, InOtherCharacter);

	CheckFalse(State->IsActionMode());
	CheckNull(InOtherCharacter);

	for (ACharacter* hitted : Hitted)
		CheckTrue(hitted == InOtherCharacter); 

	Hitted.AddUnique(InOtherCharacter);

	HitDatas[Index].SendDamage(InAttacker, InAttackCauser, InOtherCharacter);
}
void UCDoAction_Combo::OffAttachmentCollision()
{
	Super::OffAttachmentCollision();

	CheckFalse(State->IsActionMode());

	Hitted.Empty();
}