#include "Notifies/CAnimNotify_Begin_DoAction.h"

#include "Global.h"
// #include "CSword.h"
// #include "Characters/CPlayer.h"
#include "Component/CWeaponComponent.h"
#include "Weapon/CDoAction.h"

FString UCAnimNotify_Begin_DoAction::GetNotifyName_Implementation() const
{
	return "Begin DoAction";
}

void UCAnimNotify_Begin_DoAction::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	Super::Notify(MeshComp, Animation);

	CheckNull(MeshComp);
	CheckNull(MeshComp->GetOwner());

	//ACPlayer* player = Cast<ACPlayer>(MeshComp->GetOwner());
	//CheckNull(player);

	//player->GetSword()->Begin_Action();

	UCWeaponComponent* weapon = CHelpers::GetComponent<UCWeaponComponent>(MeshComp->GetOwner());
	CheckNull(weapon);

	weapon->GetDoAction()->Begin_DoAction();
}