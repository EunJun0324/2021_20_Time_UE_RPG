#include "Weapon/CSkill_Thron.h"
#include "Global.h"
#include "GameFramework/Character.h"
#include "NiagaraComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "Engine/StaticMesh.h"

ACSkill_Thron::ACSkill_Thron()
{
	CHelpers::CreateComponent<USceneComponent>(this, &Root, "Root");
	CHelpers::CreateComponent<UNiagaraComponent>(this, &Niagara, "Niagara", Root);
}

void ACSkill_Thron::ReceiveParticleData_Implementation(const TArray<FBasicParticleData>& Data, UNiagaraSystem* NiagaraSystem)
{
		FVector location = Data[0].Position;

		if (CollisionMesh)
		{
			FBox box = CollisionMesh->GetBoundingBox();
			FVector center = box.GetCenter();
			FVector extent = box.GetExtent() * 3.3;

			TArray<FHitResult> hitResults;

			TArray<TEnumAsByte<EObjectTypeQuery>> objects;
			objects.Add(EObjectTypeQuery::ObjectTypeQuery3);

			TArray<AActor*> ignores;
			ignores.Add(OwnerCharacter);

			UKismetSystemLibrary::BoxTraceMultiForObjects(GetWorld(), location, location, extent, FRotator::ZeroRotator, objects, false, ignores, EDrawDebugTrace::ForDuration, hitResults, true);
		
			for (auto hit : hitResults)
			{
				ACharacter* character = Cast<ACharacter>(hit.GetActor());
				HitData.SendDamage(OwnerCharacter, this, character);
				Destroy();
			}
		}
}

void ACSkill_Thron::BeginPlay()
{
	Super::BeginPlay();

	Niagara->SetNiagaraVariableObject("Collision", this);
}
