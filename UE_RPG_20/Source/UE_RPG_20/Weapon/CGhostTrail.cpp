#include "Weapon/CGhostTrail.h"
#include "Global.h"
#include "GameFramework/Character.h"
#include "Components/PoseableMeshComponent.h"
#include "Components/CapsuleComponent.h"
#include "Materials/MaterialInstanceConstant.h"
#include "Materials/MaterialInstanceDynamic.h"


ACGhostTrail::ACGhostTrail()
{
	CHelpers::CreateComponent<UPoseableMeshComponent>(this, &Poseable, "Poseable");
	CHelpers::GetAsset<UMaterialInstanceConstant>(&Material, "MaterialInstanceConstant'/Game/Materials/M_GhostTrail_Inst.M_GhostTrail_Inst'");
}

void ACGhostTrail::BeginPlay()
{
	Super::BeginPlay();
	
	Poseable->SetVisibility(false);

	OwnerCharacter = Cast<ACharacter>(GetOwner());
	Poseable->SetSkeletalMesh(OwnerCharacter->GetMesh()->SkeletalMesh);
	Poseable->CopyPoseFromSkeletalComponent(OwnerCharacter->GetMesh());

	DynamicMaterial = UMaterialInstanceDynamic::Create(Material, this);
	for (int32 i = 0; i < OwnerCharacter->GetMesh()->SkeletalMesh->Materials.Num(); i++)
		Poseable->SetMaterial(i, DynamicMaterial);

	FTimerDelegate timerDelegate = FTimerDelegate::CreateLambda([=]()
		{
			if (Poseable->IsVisible() == false)
				Poseable->ToggleVisibility();


			float height = OwnerCharacter->GetCapsuleComponent()->GetScaledCapsuleHalfHeight();
			SetActorLocation(OwnerCharacter->GetActorLocation() - FVector(0, 0, height));
			SetActorRotation(OwnerCharacter->GetActorRotation() + FRotator(0, -90, 0));
			Poseable->CopyPoseFromSkeletalComponent(OwnerCharacter->GetMesh());
			CLog::Print("SetActorRotation");
		});

	GetWorld()->GetTimerManager().SetTimer(TimerHandle, timerDelegate, Interval, true, StartDelay);
}

void ACGhostTrail::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);

	GetWorld()->GetTimerManager().ClearTimer(TimerHandle);
}

