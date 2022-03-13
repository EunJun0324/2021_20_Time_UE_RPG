#include "Notifies/CAnimNotifyState_Equip.h"
#include "Global.h"
// #include "CSword.h"
// #include "Characters/CPlayer.h"

#include "Component/CWeaponComponent.h"
#include "Weapon/CEquippment.h"

FString UCAnimNotifyState_Equip::GetNotifyName_Implementation() const
{ return "Equip"; }

void UCAnimNotifyState_Equip::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration)
{
	Super::NotifyBegin(MeshComp, Animation, TotalDuration);

	CheckNull(MeshComp);
	CheckNull(MeshComp->GetOwner());

	//ACPlayer* player = Cast<ACPlayer>(MeshComp->GetOwner());
	//CheckNull(player);

	//player->GetSword()->Begin_Equip();

	UCWeaponComponent* weapon = CHelpers::GetComponent<UCWeaponComponent>(MeshComp->GetOwner());
	CheckNull(weapon);

	weapon->GetEquipment()->Begin_Equip();
}
void UCAnimNotifyState_Equip::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	Super::NotifyEnd(MeshComp, Animation);

	CheckNull(MeshComp);
	CheckNull(MeshComp->GetOwner());

	// ACPlayer* player = Cast<ACPlayer>(MeshComp->GetOwner());
	// CheckNull(player);

	// player->GetSword()->End_Equip();

	UCWeaponComponent* weapon = CHelpers::GetComponent<UCWeaponComponent>(MeshComp->GetOwner());
	CheckNull(weapon);

	weapon->GetEquipment()->End_Equip();


}
