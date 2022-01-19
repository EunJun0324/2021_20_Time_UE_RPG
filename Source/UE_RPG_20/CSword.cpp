#include "CSword.h"
#include "Global.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/CapsuleComponent.h"
#include "Component/CStateComponent.h"
#include "Component/CStatusComponent.h"
#include "Animation/AnimMontage.h"

ACSword::ACSword()
{
	CHelpers::CreateComponent<USceneComponent>(this, &Root, "Root");
	CHelpers::CreateComponent<USkeletalMeshComponent>(this, &Mesh, "Mesh", Root);
	CHelpers::CreateComponent<UCapsuleComponent>(this, &Capsule, "Capsule", Mesh);

	USkeletalMesh* mesh;
	CHelpers::GetAsset<USkeletalMesh>(&mesh, "SkeletalMesh'/Game/Character/Weapons/Sword/SK_Sword.SK_Sword'");
	Mesh->SetSkeletalMesh(mesh);

	Capsule->SetRelativeLocation(FVector(-13, -130, 0));
	Capsule->SetRelativeRotation(FRotator(0, 0, 90));
	Capsule->SetCapsuleHalfHeight(220);
	Capsule->SetCapsuleRadius(11);

	CHelpers::GetAsset<UAnimMontage>(&EquipMontage, "AnimMontage'/Game/Character/Montages/OneHand/Draw_Sword_Montage.Draw_Sword_Montage'");

	CHelpers::GetAsset<UAnimMontage>(&ComboMontage[0], "AnimMontage'/Game/Character/Montages/OneHand/Sword_Attack_1_Montage.Sword_Attack_1_Montage'");
	CHelpers::GetAsset<UAnimMontage>(&ComboMontage[1], "AnimMontage'/Game/Character/Montages/OneHand/Sword_Attack_2_Montage.Sword_Attack_2_Montage'");
	CHelpers::GetAsset<UAnimMontage>(&ComboMontage[2], "AnimMontage'/Game/Character/Montages/OneHand/Sword_Attack_3_Montage.Sword_Attack_3_Montage'");
}

void ACSword::BeginPlay()
{
	Super::BeginPlay();
	
	OwnerCharacter = Cast<ACharacter>(GetOwner());
	State = CHelpers::GetComponent<UCStateComponent>(OwnerCharacter);
	Status = CHelpers::GetComponent<UCStatusComponent>(OwnerCharacter);

	OffCollision();

	Capsule->OnComponentBeginOverlap.AddDynamic(this, &ACSword::OnComponentBeginOverlap);
}
void ACSword::Equip()
{
	CheckFalse(State->IsIdleMode());

	if (bEquipped)
	{
		Unequip();

		return;
	}

	State->SetEquipMode();
	OwnerCharacter->PlayAnimMontage(EquipMontage, 2);
}
void ACSword::Begin_Equip()
{
	AttachToComponent(OwnerCharacter->GetMesh(), FAttachmentTransformRules(EAttachmentRule::KeepRelative, true), "Hand_OneHand");

	bEquipped = true;
}
void ACSword::End_Equip()
{
	State->SetIdleMode();

	OwnerCharacter->bUseControllerRotationYaw = true;
	OwnerCharacter->GetCharacterMovement()->bOrientRotationToMovement = false;

}
void ACSword::Unequip()
{
	AttachToComponent(OwnerCharacter->GetMesh(), FAttachmentTransformRules(EAttachmentRule::KeepRelative, true), "Holster_OneHand");
	bEquipped = false;


	OwnerCharacter->bUseControllerRotationYaw = false;
	OwnerCharacter->GetCharacterMovement()->bOrientRotationToMovement = true;
}

void ACSword::Action()		
{
	CheckFalse(bEquipped);

	if (bEnable)
	{
		bExist = true;
		bEnable = false;
		return;
	}

	CheckFalse(State->IsIdleMode());

	Status->Stop();
	State->SetActionMode();

	OwnerCharacter->PlayAnimMontage(ComboMontage[Index], 1.5f);
}
void ACSword::Begin_Action()
{
	CheckFalse(bExist);
	bExist = false;

	OwnerCharacter->PlayAnimMontage(ComboMontage[++Index], 1.5f);
}
void ACSword::End_Action()
{
	Index = 0;

	Status->Move();
	State->SetIdleMode();
}

void ACSword::OnCollision()
{ Capsule->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics); }

void ACSword::OffCollision()
{ Capsule->SetCollisionEnabled(ECollisionEnabled::NoCollision); }

void ACSword::OnComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	CheckTrue(OtherActor == OwnerCharacter);

	FDamageEvent DE;
	OtherActor->TakeDamage(20, DE ,OwnerCharacter->GetController(), this);
}