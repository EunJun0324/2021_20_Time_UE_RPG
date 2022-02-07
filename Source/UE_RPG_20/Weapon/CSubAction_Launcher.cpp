#include "Weapon/CSubAction_Launcher.h"
#include "Global.h"
#include "GameFramework/Character.h"
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
}
void UCSubAction_Launcher::Pressed() 
{
	Super::Pressed();

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

}
void UCSubAction_Launcher::End_SubAction() 
{
	Super::End_SubAction();

	bMoving = false;

	for (ACharacter* character : Overlapped)
		character->GetCapsuleComponent()->SetCollisionProfileName("Pawn");

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