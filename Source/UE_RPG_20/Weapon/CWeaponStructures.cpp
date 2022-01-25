#include "CWeaponStructures.h"
#include "Global.h"
#include "GameFramework/Character.h"
#include "Components/CapsuleComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Component/CStatusComponent.h"
#include "Component/CStateComponent.h"
#include "Animation/AnimMontage.h"
#include "Sound/SoundCue.h"


UAnimMontage* UCWeaponStructures::DefaultHitMontage = nullptr;

UCWeaponStructures::UCWeaponStructures()
{
	CHelpers::GetAsset<UAnimMontage>(&DefaultHitMontage, "AnimMontage'/Game/Character/Montages/Common/HitReaction_Montage.HitReaction_Montage'");
}

void FDoActionData::PlayMontage(ACharacter* InOwner)
{
	UCStatusComponent* status = CHelpers::GetComponent<UCStatusComponent>(InOwner);
	if (status)
	{
		bCanMove ? status->Move() : status->Stop();
	}

	InOwner->PlayAnimMontage(Montage, PlayRatio);
}

void FDoActionData::PlayEffect(UWorld* InWorld, ACharacter* InOwner)
{
	CheckNull(Effect);

	FTransform transform = EffectTransform;

	FVector ownerLocation = InOwner->GetActorLocation();
	ownerLocation += InOwner->GetActorRotation().RotateVector(transform.GetLocation());
	transform.SetLocation(ownerLocation);

	FRotator rotation = InOwner->GetActorRotation();
	rotation += FRotator(transform.GetRotation());
	transform.SetRotation(FQuat(rotation));

	CHelpers::PlayEffect(InWorld, Effect, transform);
}

void FDoActionData::PlayEffect(USkeletalMeshComponent* InMesh, FName InSockectName)
{
	CheckNull(Effect);

	AActor* owner = InMesh->GetOwner();
	UWorld* world = owner->GetWorld();

	CHelpers::PlayEffect(world, Effect, EffectTransform, InMesh, InSockectName);
}

void FDoActionData::EndAction(ACharacter* InOwner)
{
	UCStatusComponent* status = CHelpers::GetComponent<UCStatusComponent>(InOwner);
	if (status)
		status->Move();

	UCStateComponent* state = CHelpers::GetComponent<UCStateComponent>(InOwner);
	if (state)
		state->SetIdleMode();
}

void FHitData::PlayMontage(ACharacter* InOwner)
{
	UCStatusComponent* status = CHelpers::GetComponent<UCStatusComponent>(InOwner);

	if (status)
		bCanMove ? status->Move() : status->Stop();


	UAnimMontage* montage = Montage ? Montage : UCWeaponStructures::GetDefaultHitMontage();
	InOwner->PlayAnimMontage(montage, PlayRatio);
}

void FHitData::PlayEffect(UWorld* InWorld, const FTransform& InTransform)
{
	CheckNull(Effect);

	FTransform transform = EffectTransform;
	transform.SetRotation(InTransform.GetRotation());
	transform.AddToTranslation(InTransform.GetLocation());

	CHelpers::PlayEffect(InWorld, Effect, transform);
}

void FHitData::PlayEffect(USkeletalMeshComponent* InMesh, FName InSockectName)
{
	CheckNull(Effect);

	AActor* owner = InMesh->GetOwner();
	UWorld* world = owner->GetWorld();

	CHelpers::PlayEffect(world, Effect, EffectTransform, InMesh, InSockectName);
}

void FHitData::PlaySoundCue(UWorld* InWorld, const FVector& InLocation)
{
	CheckNull(SoundCue);

	UGameplayStatics::SpawnSoundAtLocation(InWorld, SoundCue, InLocation);
}

void FHitData::PlayHitStop(UWorld* InWorld)
{
	CheckTrue(FMath::IsNearlyZero(StopTime));

	UGameplayStatics::SetGlobalTimeDilation(InWorld, 0.001);

	FTimerDelegate timerDelegate = FTimerDelegate::CreateLambda([=]()
		{
			UGameplayStatics::SetGlobalTimeDilation(InWorld, 1);
		});

	FTimerHandle timerHandle;
	InWorld->GetTimerManager().SetTimer(timerHandle, timerDelegate, StopTime, false);

}

void FHitData::SendDamage(ACharacter* InAttacker, AActor* InAttackCursor, ACharacter* InOtherCharacter)
{
	FActionDamageEvent e;
	e.HitData = this;
	InOtherCharacter->TakeDamage(Power, e, InAttacker->GetController(), InAttackCursor);
}
