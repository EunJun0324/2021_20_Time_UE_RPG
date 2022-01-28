#include "Notifies/CAnimNotifyState_Combo.h"

#include "Global.h"
// #include "CSword.h"
// #include "Characters/CPlayer.h"

#include "Component/CWeaponComponent.h"
#include "Weapon/CDoAction_Combo.h"

FString UCAnimNotifyState_Combo::GetNotifyName_Implementation() const
{
	return "Combo";
}

void UCAnimNotifyState_Combo::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration)
{
	Super::NotifyBegin(MeshComp, Animation, TotalDuration);

	CheckNull(MeshComp);
	CheckNull(MeshComp->GetOwner());

	// ACPlayer* player = Cast<ACPlayer>(MeshComp->GetOwner());
	// CheckNull(player);

	// player->GetSword()->Enable_Combo();

	UCWeaponComponent* weapon = CHelpers::GetComponent<UCWeaponComponent>(MeshComp->GetOwner());
	CheckNull(weapon);

	UCDoAction_Combo* combo = Cast<UCDoAction_Combo>(weapon->GetDoAction());
	combo->Enable_Combo();

}
void UCAnimNotifyState_Combo::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	Super::NotifyEnd(MeshComp, Animation);

	CheckNull(MeshComp);
	CheckNull(MeshComp->GetOwner());

	//ACPlayer* player = Cast<ACPlayer>(MeshComp->GetOwner());
	//CheckNull(player);

	//player->GetSword()->Disable_Combo();

	UCWeaponComponent* weapon = CHelpers::GetComponent<UCWeaponComponent>(MeshComp->GetOwner());
	CheckNull(weapon);

	UCDoAction_Combo* combo = Cast<UCDoAction_Combo>(weapon->GetDoAction());
	combo->Disable_Combo();

}
