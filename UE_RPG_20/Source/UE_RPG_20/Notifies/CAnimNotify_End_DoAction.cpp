#include "Notifies/CAnimNotify_End_DoAction.h"
#include "Global.h"
//#include "CSword.h"
//#include "Characters/CPlayer.h"

#include "Component/CWeaponComponent.h"
#include "Weapon/CDoAction.h"

FString UCAnimNotify_End_DoAction::GetNotifyName_Implementation() const
{
	return "End DoAction";
}

void UCAnimNotify_End_DoAction::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	Super::Notify(MeshComp, Animation);

	CheckNull(MeshComp);
	CheckNull(MeshComp->GetOwner());

	//ACPlayer* player = Cast<ACPlayer>(MeshComp->GetOwner());
	//CheckNull(player);

	//player->GetSword()->End_Action();

	UCWeaponComponent* weapon = CHelpers::GetComponent<UCWeaponComponent>(MeshComp->GetOwner());
	CheckNull(weapon);

	weapon->GetDoAction()->End_DoAction();

}