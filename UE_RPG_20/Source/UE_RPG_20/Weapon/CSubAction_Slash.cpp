#include "Weapon/CSubAction_Slash.h"
#include "Global.h"
#include "GameFramework/Character.h"
#include "Component/CStateComponent.h"
#include "CSkill_SwordSlash.h"


UCSubAction_Slash::UCSubAction_Slash()
{

}
void UCSubAction_Slash::Pressed()		 
{
	CheckFalse(State->IsIdleMode());
	CheckTrue(State->IsSubActionMode());

	Super::Pressed();

	State->SetActionMode();
	State->OnSubActionMode();

	ActionData.PlayMontage(OwnerCharacter);
}			
void UCSubAction_Slash::Begin_SubAction()
{
	Super::Begin_SubAction();

	ActionData.PlayEffect(World, OwnerCharacter);

	if (SkillClass)
	{
		FActorSpawnParameters params;
		params.Owner = OwnerCharacter;

		FTransform transform = SkillTransform;
		transform.AddToTranslation(OwnerCharacter->GetActorLocation());
		transform.SetRotation(FQuat(OwnerCharacter->GetActorRotation()));

		ACSkill* skill = World->SpawnActorDeferred<ACSkill_SwordSlash>(SkillClass, transform, OwnerCharacter);
		skill->SetHitData(HitData);
		UGameplayStatics::FinishSpawningActor(skill, transform);
	}
} 
void UCSubAction_Slash::End_SubAction()
{
	Super::End_SubAction();

	State->OffSubActionMode();
	ActionData.EndAction(OwnerCharacter);
}