#include "Weapon/CWeaponAsset.h"
#include "Global.h"
#include "CAttachment.h"
#include "CEquippment.h"
#include "CDoAction.h"
#include "CSubAction.h"
#include "CWeaponData.h"
#include "GameFramework/Character.h"

UCWeaponAsset::UCWeaponAsset()							
{
	CHelpers::GetClass<UCEquippment>(&EquipmentClass, "Blueprint'/Game/Weapons/BP_CEquipment.BP_CEquipment_C'");

	DoActionClass  = UCDoAction::StaticClass();
	SubActionClass = UCSubAction::StaticClass();
}

void UCWeaponAsset::BeginPlay(class ACharacter* InOwner, class UCWeaponData** OutAction)
{
	ACAttachment* attachment = nullptr;
	if (AttachmentClass)
	{
		FActorSpawnParameters params;
		params.Owner = InOwner;

		attachment = InOwner->GetWorld()->SpawnActor<ACAttachment>(AttachmentClass, params);
	}
	UCEquippment* equippment = nullptr;
	if (EquipmentClass)
	{
		equippment = NewObject<UCEquippment>(this, EquipmentClass);
		equippment->BeginPlay(InOwner, EquipmentData);

		if (attachment)
		{
			equippment->OnEquip.AddDynamic(attachment, &ACAttachment::OnEquip);
			equippment->OnUnequip.AddDynamic(attachment, &ACAttachment::OnUnequip);
		}
	}
	UCDoAction* doAction = nullptr;
	if (DoActionClass)
	{
		doAction = NewObject<UCDoAction>(this, DoActionClass);
		doAction->BeginPlay(attachment, InOwner, DoActionDatas, HitDatas);

		if (equippment)
		{
			doAction->SetEquipping(equippment->IsEquipping());
			equippment->OnEquip.AddDynamic(doAction, &UCDoAction::OnEquip);
			equippment->OnUnequip.AddDynamic(doAction, &UCDoAction::OnUnequip);
		}
		if (attachment)
		{
			attachment->OnAttachmentBeginOverlap.AddDynamic(doAction, &UCDoAction::OnAttachmentBeginOverlap);
			attachment->OnAttachmentEndOverlap.AddDynamic(doAction, &UCDoAction::OnAttachmentEndOverlap);

			attachment->OnAttachmentCollision.AddDynamic(doAction, &UCDoAction::OnAttachmentCollision);
			attachment->OffAttachmentCollision.AddDynamic(doAction, &UCDoAction::OffAttachmentCollision);
		}
	}

	UCSubAction* subAction = nullptr;
	if (SubActionClass)
	{
		subAction = NewObject<UCSubAction>(this, SubActionClass);
		subAction->BeginPlay(InOwner);

		if (attachment)
		{
			attachment->OnAttachmentBeginOverlap.AddDynamic(subAction, &UCSubAction::OnAttachmentBeginOverlap);
			attachment->OnAttachmentEndOverlap.AddDynamic(subAction, &UCSubAction::OnAttachmentEndOverlap);

			attachment->OnAttachmentCollision.AddDynamic(subAction, &UCSubAction::OnAttachmentCollision);
			attachment->OffAttachmentCollision.AddDynamic(subAction, &UCSubAction::OffAttachmentCollision);
		}
	}

	*OutAction = NewObject<UCWeaponData>();
	(*OutAction)->Attachment = attachment;
	(*OutAction)->Equippment = equippment;
	(*OutAction)->DoAction   = doAction;
	(*OutAction)->SubAction  = subAction;
}

void UCWeaponAsset::EndPlay()
{
}
