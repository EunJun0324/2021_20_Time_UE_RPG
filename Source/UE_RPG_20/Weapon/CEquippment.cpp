#include "Weapon/CEquippment.h"
#include "Global.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Component/CStateComponent.h"
#include "Component/CStatusComponent.h"

UCEquippment::UCEquippment() {}

void UCEquippment::BeginPlay(class ACharacter* InOwner, const FEquipmentData& InData)
{
	OwnerCharacter = InOwner;
	Data = InData;

	State = CHelpers::GetComponent<UCStateComponent>(OwnerCharacter);
	Status = CHelpers::GetComponent<UCStatusComponent>(OwnerCharacter);
}

void UCEquippment::Equip_Implementation()
{
	State->SetEquipMode();

	if (!Data.bCanMove) Status->Stop();

	if (Data.Montage) OwnerCharacter->PlayAnimMontage(Data.Montage, Data.PlayRatio);
	else
	{
		Begin_Equip();
		End_Equip();
	}

	if (Data.bLookForward)
	{
		OwnerCharacter->bUseControllerRotationYaw = true;
		OwnerCharacter->GetCharacterMovement()->bOrientRotationToMovement = false;
	}
}


void UCEquippment::Begin_Equip_Implementation()
{
	if (OnEquip.IsBound())
		OnEquip.Broadcast();
}

void UCEquippment::End_Equip_Implementation()
{
	State->SetIdleMode();
	Status->Move();

	bEquipping = true;
}

void UCEquippment::Unequip_Implementation()
{
	bEquipping = false;

	OwnerCharacter->bUseControllerRotationYaw = false;
	OwnerCharacter->GetCharacterMovement()->bOrientRotationToMovement = true;


	if (OnUnequip.IsBound())
		OnUnequip.Broadcast();
}
