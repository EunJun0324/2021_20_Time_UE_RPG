#include "Component/CWeaponComponent.h"
#include "Global.h"
#include "GameFramework/Character.h"
#include "Weapon/CDoAction.h"
#include "Weapon/CSubAction.h"
#include "Weapon/CWeaponAsset.h"
#include "Weapon/CWeaponData.h"
#include "Weapon/CAttachment.h"

UCWeaponComponent::UCWeaponComponent()
{ PrimaryComponentTick.bCanEverTick = true; }


void UCWeaponComponent::BeginPlay()
{
	Super::BeginPlay();

	OwnerCharacter = Cast<ACharacter>(GetOwner());
	for (int32 i = 0; i < (int32)EWeaponType::Max; i++)
	{
		if (DataAssets[i])
			DataAssets[i]->BeginPlay(OwnerCharacter, &Datas[i]);
	}

	CLog::Print(OwnerCharacter);

	for (int32 i = 0; i < (int32)EWeaponType::Max; i++)
		CLog::Print(Datas[i]);
}

void UCWeaponComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (IsUnarmedMode() == false)
	{
		if (GetSubAction())
			GetSubAction()->Tick(DeltaTime);
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

void UCWeaponComponent::SetWizardMode()
{ SetMode(EWeaponType::Wizard); }

void UCWeaponComponent::SetBowMode()
{ SetMode(EWeaponType::Bow); }

void UCWeaponComponent::DoAction()
{
	CheckTrue(Type == EWeaponType::Max);

	GetDoAction()->DoAction();
}

void UCWeaponComponent::SubAction_Pressed()
{
	CheckTrue(Type == EWeaponType::Max);

	GetSubAction()->Pressed();
}

void UCWeaponComponent::SubAction_Released()
{
	CheckTrue(Type == EWeaponType::Max);

	GetSubAction()->Released();
}


ACAttachment* UCWeaponComponent::GetAttachment()
{ return Datas[(int32)Type]->GetAttachment(); }

UCEquippment* UCWeaponComponent::GetEquipment()
{ return Datas[(int32)Type]->GetEquippment(); }

UCDoAction* UCWeaponComponent::GetDoAction()
{ return Datas[(int32)Type]->GetDoAction(); }

UCSubAction* UCWeaponComponent::GetSubAction()
{ return Datas[(int32)Type]->GetSubAction(); }

void UCWeaponComponent::SetMode(EWeaponType InType)
{
	if (Type == InType)
	{
		SetUnarmedMode();

		return;
	}
	else if (IsUnarmedMode() == false)
	{ Datas[(int32)Type]->GetEquippment()->Unequip(); }
	
	if (Datas[(int32)InType])
	{
		Datas[(int32)InType]->GetEquippment()->Equip();

		ChangeType(InType);
	}
}

void UCWeaponComponent::ChangeType(EWeaponType InType)
{
	Type = InType;

	if (OnWeaponTypeChanged.IsBound())
		OnWeaponTypeChanged.Broadcast(InType);
}

void UCWeaponComponent::RemoveAll()
{
	for (int32 i = 0; i < (int32)EWeaponType::Max; i++)
	{
		if (Datas[i])
		{
			if (Datas[i]->GetAttachment())
				Datas[i]->GetAttachment()->Destroy();
		}
	}
}