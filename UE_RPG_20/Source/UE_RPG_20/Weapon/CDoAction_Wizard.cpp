#include "Weapon/CDoAction_Wizard.h"
#include "Global.h"
#include "GameFramework/Character.h"
#include "Component/CStateComponent.h"
#include "CAttachment.h"
#include "CProjectile.h"

UCDoAction_Wizard::UCDoAction_Wizard()
{
	CHelpers::GetClass<ACProjectile>(&FireBallClass, "Blueprint'/Game/Weapons/BP_CProjectile_FireBall.BP_CProjectile_FireBall_C'");
}

void UCDoAction_Wizard::BeginPlay(class ACAttachment* InAttachment, class ACharacter* InOwner, const TArray<FDoActionData>& InActionDatas, const TArray<FHitData>& InHitDatas)
{
	Super::BeginPlay(InAttachment, InOwner, InActionDatas, InHitDatas);

}

void UCDoAction_Wizard::CreateFireBall()
{
	FTransform transform;

	TArray<AActor*> ignoreActors;
	ignoreActors.Add(OwnerCharacter);

	ACProjectile* fireBall = World->SpawnActorDeferred<ACProjectile>(FireBallClass, transform, NULL, NULL, ESpawnActorCollisionHandlingMethod::AlwaysSpawn);
	FAttachmentTransformRules rule = FAttachmentTransformRules(EAttachmentRule::KeepRelative, true);
	fireBall->AttachToComponent(OwnerCharacter->GetMesh(), rule, "Hand_FireBall_Projectile");

	FireBalls.Add(fireBall);
	UGameplayStatics::FinishSpawningActor(fireBall, transform);
}

void UCDoAction_Wizard::FireBallHit(AActor* InCauser, ACharacter* InOtherCharacter)
{ HitDatas[0].SendDamage(OwnerCharacter, InCauser, InOtherCharacter); }

void UCDoAction_Wizard::FireBallDestroy(ACProjectile* InDestroyer)
{ FireBalls.Remove(InDestroyer); }


void UCDoAction_Wizard::DoAction()
{
	Super::DoAction();

	CheckFalse(ActionDatas.Num() > 0);
	CheckFalse(State->IsIdleMode());

	State->SetActionMode();

	ActionDatas[0].PlayMontage(OwnerCharacter);
}

void UCDoAction_Wizard::Begin_DoAction()
{
	Super::Begin_DoAction();

	for (int32 i = FireBalls.Num() - 1; i >= 0; i--)
	{
		if (FireBalls[i]->GetAttachParentActor())
		{
			FireBalls[i]->OnProjectileHit.AddDynamic(this, &UCDoAction_Wizard::FireBallHit);
			FireBalls[i]->OnProjectileEndPlay.AddDynamic(this, &UCDoAction_Wizard::FireBallDestroy);

			FireBalls[i]->Shoot(FQuat(OwnerCharacter->GetActorRotation()).GetForwardVector());
		}
	}
}

void UCDoAction_Wizard::End_DoAction()
{
	Super::End_DoAction();

	ActionDatas[0].EndAction(OwnerCharacter);

	CreateFireBall();
}

void UCDoAction_Wizard::OnEquip()
{
	Super::OnEquip();

	CreateFireBall();
}

void UCDoAction_Wizard::OnUnequip()
{
	for (int32 i = FireBalls.Num() - 1; i >= 0; i--)
	{
		if (FireBalls[i]->GetAttachParentActor())
			FireBalls[i]->Destroy();
	}
}

