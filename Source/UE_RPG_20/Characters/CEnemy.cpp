#include "Characters/CEnemy.h"

#include "Global.h"

#include "Components/SkeletalMeshComponent.h"
#include "Components/CapsuleComponent.h"

#include "Materials/MaterialInstanceDynamic.h"

#include "Component/CStatusComponent.h"
#include "Component/CMontageComponent.h"

#include "Weapon/CWeaponStructures.h"

ACEnemy::ACEnemy()
{
	CHelpers::CreateActorComponent<UCStatusComponent>(this, &Status, "Status");
	CHelpers::CreateActorComponent<UCStateComponent>(this, &State, "State");
	CHelpers::CreateActorComponent<UCMontageComponent>(this, &Montage, "Montage");


	GetMesh()->SetRelativeLocation(FVector(0, 0, -90));
	GetMesh()->SetRelativeRotation(FRotator(0, -90, 0));

	USkeletalMesh* mesh;
	CHelpers::GetAsset<USkeletalMesh>(&mesh, "SkeletalMesh'/Game/Character/Mesh/SK_Mannequin.SK_Mannequin'");
	GetMesh()->SetSkeletalMesh(mesh);

	TSubclassOf<UAnimInstance> animInstance;
	CHelpers::GetClass<UAnimInstance>(&animInstance, "AnimBlueprint'/Game/BP_CAnimInstance.BP_CAnimInstance_C'");
	GetMesh()->SetAnimInstanceClass(animInstance);
}

void ACEnemy::BeginPlay()
{
	Super::BeginPlay();
	
	State->OnStateTypeChanged.AddDynamic(this, &ACEnemy::OnStateTypeChanged);

	int count = 0;
	TArray<UMaterialInterface*> materials = GetMesh()->GetMaterials();
	for (UMaterialInterface* material : materials)
	{
		UMaterialInstanceDynamic* dynamic = UMaterialInstanceDynamic::Create(material, this);
		GetMesh()->SetMaterial(count, dynamic);
		Materials.Add(dynamic);
		count++;
	}

	Change_Character_Color(OriginColor);
}

void ACEnemy::OnStateTypeChanged(EStateType InType)
{
	switch (InType)
	{
	case EStateType::Hitted: Hitted(); break;
	case EStateType::Dead:  Dead();    break;
	}
}

float ACEnemy::TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser)
{
	Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);

	CLog::Print(this);

	Damaged.DamageAmount = DamageAmount;
	Damaged.EventInstigator = EventInstigator;
	Damaged.DamageEvent = (FActionDamageEvent*)&DamageEvent;

	State->SetHittedMode();

	return DamageAmount;
}

void ACEnemy::Hitted()
{
	// Montage->PlayHittedMode();

	Change_Character_Color(FLinearColor::Red);

	FTimerHandle timerHandle;
	FTimerDelegate timerDelegate = FTimerDelegate::CreateLambda([=]()
		{
			Change_Character_Color(OriginColor);
		});

	GetWorld()->GetTimerManager().SetTimer(timerHandle, timerDelegate, 0.2f, false);

	Status->SubHealth(Damaged.DamageAmount);
	Damaged.DamageAmount = 0.0f;

	if (Status->GetHp() <= 0.0f)
	{
		State->SetDeadMode();
		return;
	}

	FVector start = GetActorLocation();
	FVector target = Damaged.EventInstigator->GetPawn()->GetActorLocation();


	if (Damaged.DamageEvent && Damaged.DamageEvent->HitData)
	{
		FHitData* data = Damaged.DamageEvent->HitData;
		data->PlayMontage(this);

		FTransform transform;
		transform.SetLocation(GetActorLocation());
		
		data->PlayEffect(GetWorld(), transform);
		data->PlayHitStop(GetWorld());
		data->PlaySoundCue(GetWorld(), GetActorLocation());

		FVector direction = target - start;
		direction.Normalize();

		LaunchCharacter(-direction * 300, true, false);
	}
	Damaged.DamageEvent = NULL;

	SetActorRotation(UKismetMathLibrary::FindLookAtRotation(start , target));
	Damaged.EventInstigator = NULL;
}

void ACEnemy::Dead()
{
	GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	Montage->PlayDeadMode();
}

void ACEnemy::Change_Character_Color(FLinearColor InColor)
{
	for (UMaterialInstanceDynamic* material : Materials)
		material->SetVectorParameterValue("BodyColor", InColor);
}