#include "Weapon/CSubAction_Meteor.h"
#include "Global.h"
#include "CSkill_Thron.h"
#include "GameFramework/Character.h"
#include "Component/CStateComponent.h"

UCSubAction_Meteor::UCSubAction_Meteor() {}

void UCSubAction_Meteor::Pressed()
{
	CheckFalse(State->IsIdleMode());
	CheckTrue(State->IsSubActionMode());

	Super::Pressed();

	State->SetActionMode();
	State->OnSubActionMode();

	ActionData.PlayMontage(OwnerCharacter);
}

void UCSubAction_Meteor::Begin_SubAction()
{
	Super::Begin_SubAction();

	if (SkillClass)
	{
		FActorSpawnParameters params;
		params.Owner = OwnerCharacter;

		FTransform transform = SkillTransform;

		FVector location = OwnerCharacter->GetActorLocation();
		location += OwnerCharacter->GetActorRotation().RotateVector(transform.GetLocation());
		
		transform.SetLocation(location);

		transform.SetRotation(FQuat(OwnerCharacter->GetActorRotation()));

		ACSkill* skill = World->SpawnActorDeferred<ACSkill_Thron>(SkillClass, transform, OwnerCharacter);
		skill->SetHitData(HitData);
		UGameplayStatics::FinishSpawningActor(skill, transform);
	}
}

void UCSubAction_Meteor::End_SubAction()
{
	Super::End_SubAction();

	State->OffSubActionMode();
	ActionData.EndAction(OwnerCharacter);
}
