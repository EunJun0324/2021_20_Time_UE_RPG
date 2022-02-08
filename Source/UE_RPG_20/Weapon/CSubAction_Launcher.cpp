#include "Weapon/CSubAction_Launcher.h"
#include "Global.h"
#include "GameFramework/Character.h"
#include "Component/CStateComponent.h"
#include "Components/CapsuleComponent.h"

UCSubAction_Launcher::UCSubAction_Launcher() { }

void UCSubAction_Launcher::BeginPlay(class ACharacter* InOwner)
{
	Super::BeginPlay(InOwner);

	OwnerRadius = OwnerCharacter->GetCapsuleComponent()->GetScaledCapsuleRadius();
}
void UCSubAction_Launcher::Tick(float InDeltaTime)
{
	Super::Tick(InDeltaTime);

	CheckFalse(bMoving);

	FVector location = OwnerCharacter->GetActorLocation();

	if (location.Equals(End, OwnerRadius * 2))
	{
		bMoving = false;

		Start = End = OwnerCharacter->GetActorLocation();
	}

	location = UKismetMathLibrary::VInterpTo(location, End, InDeltaTime, Speed);

	//OwnerCharacter->GetCharacterMovement()->AddImpluse();
	//OwnerCharacter->SetActorLocation();

	FVector direction = (End - Start).GetSafeNormal2D();
	OwnerCharacter->AddActorWorldOffset(direction * Speed, true);
}

void UCSubAction_Launcher::Pressed() 
{
	CheckFalse(State->IsIdleMode());
	CheckTrue(State->IsSubActionMode());

	Super::Pressed();

	State->SetActionMode();
	State->OnSubActionMode();

	ActionData.PlayMontage(OwnerCharacter);
}
void UCSubAction_Launcher::Begin_SubAction()
{
	Super::Begin_SubAction();

	bMoving = true;

	Start = OwnerCharacter->GetActorLocation();
	End = Start + OwnerCharacter->GetActorForwardVector() * Distance;

	TArray<AActor*> ignores;
	ignores.Add(OwnerCharacter);

	TArray<FHitResult> hitResults;

	float y = OwnerRadius;
	float z = OwnerCharacter->GetCapsuleComponent()->GetScaledCapsuleHalfHeight();
	FRotator rotation = OwnerCharacter->GetActorRotation();

	TArray<TEnumAsByte<EObjectTypeQuery>> objects;
	objects.Add(EObjectTypeQuery::ObjectTypeQuery3);
	UKismetSystemLibrary::BoxTraceMultiForObjects(OwnerCharacter->GetWorld(), Start, End, FVector(0, y, z),
		rotation, objects, false, ignores, DrawDebug, hitResults, true);

	for (const FHitResult& hitResult : hitResults)
	{
		ACharacter* character = Cast<ACharacter>(hitResult.GetActor());
		{
			if (character)
			{
				character->GetCapsuleComponent()->SetCollisionProfileName("Launcher");
				Overlapped.AddUnique(character);
			}
		}
	}

	FHitResult lineResult;
	UKismetSystemLibrary::LineTraceSingle(OwnerCharacter->GetWorld(), Start, End, ETraceTypeQuery::TraceTypeQuery1, false, ignores, DrawDebug, lineResult, true);
	if (lineResult.bBlockingHit)
	{
		FVector direction = (End - Start).GetSafeNormal2D();
		End = lineResult.Location - (direction * OwnerRadius * 2);

		if (DrawDebug == EDrawDebugTrace::ForDuration)
			DrawDebugSphere(OwnerCharacter->GetWorld(), End, 10, 20, FColor::Magenta, true, 2);
	}
}
void UCSubAction_Launcher::End_SubAction() 
{
	Super::End_SubAction();

	bMoving = false;

	for (ACharacter* character : Overlapped)
		character->GetCapsuleComponent()->SetCollisionProfileName("Pawn");

	State->OffSubActionMode();
	ActionData.EndAction(OwnerCharacter);
}
void UCSubAction_Launcher::OnAttachmentBeginOverlap(class ACharacter* InAttacker, class AActor* InAttackCauser, class ACharacter* InOtherCharacter)
{
	Super::OnAttachmentBeginOverlap(InAttacker, InAttackCauser, InOtherCharacter);

	for (ACharacter* character : Hitted)
	{ CheckTrue(character == InOtherCharacter); }

	Hitted.AddUnique(InOtherCharacter);

	HitData.SendDamage(OwnerCharacter, InAttackCauser, InOtherCharacter);
}

void UCSubAction_Launcher::OffAttachmentCollision()
{
	Super::OffAttachmentCollision();
	CheckFalse(State->IsSubActionMode());

	Hitted.Empty();
}