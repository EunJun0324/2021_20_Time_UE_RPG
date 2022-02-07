#include "Component/CWeaponComponent.h"
#include "Global.h"
#include "GameFramework/Character.h"
#include "Weapon/CDoAction.h"
#include "Weapon/CWeaponAsset.h"

UCWeaponComponent::UCWeaponComponent()
{ PrimaryComponentTick.bCanEverTick = true; }


void UCWeaponComponent::BeginPlay()
{
	Super::BeginPlay();

	OwnerCharacter = Cast<ACharacter>(GetOwner());
	for (int32 i = 0; i < (int32)EWeaponType::Max; i++)
	{
		if (DataAssets[i])
			DataAssets[i]->BeginPlay(OwnerCharacter);
	}
}


void UCWeaponComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (IsUnarmedMode() == false)
	{
		if (GetDoAction())
			GetDoAction()->Tick(DeltaTime);
	}

}


void UCWeaponComponent::SetUnarmedMode()
{
	GetEquipment()->Unequip();
	ChangeType(EWeaponType::Max);
}

void UCWeaponComponent::SetFistMode()
{ SetMode(EWeaponType::Fist); }

void UCWeaponComponent::SetOneHandMode()
{ SetMode(EWeaponType::OneHand); }

void UCWeaponComponent::SetTwoHandMode()
{ SetMode(EWeaponType::TwoHand); }

void UCWeaponComponent::SetWarpMode()
{ SetMode(EWeaponType::Warp); }

void UCWeaponComponent::SetFireStormMode()
{ SetMode(EWeaponType::FireStorm); }

void UCWeaponComponent::SetIceBallMode()
{ SetMode(EWeaponType::IceBall); }

void UCWeaponComponent::SetBowMode()
{ SetMode(EWeaponType::Bow); }

void UCWeaponComponent::DoAction()
{
	CheckTrue(Type == EWeaponType::Max);

	GetDoAction()->DoAction();
}


ACAttachment* UCWeaponComponent::GetAttachment()
{ return DataAssets[(int32)Type]->GetAttachment(); }

UCEquippment* UCWeaponComponent::GetEquipment()
{ return DataAssets[(int32)Type]->GetEquippment(); }

UCDoAction* UCWeaponComponent::GetDoAction()
{ return DataAssets[(int32)Type]->GetDoAction(); }

void UCWeaponComponent::SetMode(EWeaponType InType)
{
	if (Type == InType)
	{
		SetUnarmedMode();

		return;
	}
	else if (IsUnarmedMode() == false)
	{ GetEquipment()->Unequip(); }
	
	if (DataAssets[(int32)InType])
	{
		DataAssets[(int32)InType]->GetEquippment()->Equip();

		ChangeType(InType);
	}
}

void UCWeaponComponent::ChangeType(EWeaponType InType)
{
	Type = InType;

	if (OnWeaponTypeChanged.IsBound())
		OnWeaponTypeChanged.Broadcast(InType);
}

