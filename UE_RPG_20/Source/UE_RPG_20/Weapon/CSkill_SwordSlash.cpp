#include "Weapon/CSkill_SwordSlash.h"
#include "Global.h"
#include "GameFramework/Character.h"
#include "Components/BoxComponent.h"
#include "NiagaraComponent.h"

ACSkill_SwordSlash::ACSkill_SwordSlash()
{
	CHelpers::CreateComponent<USceneComponent>(this, &Root, "Root");
	CHelpers::CreateComponent<UNiagaraComponent>(this, &Niagara, "Niagara", Root);
	CHelpers::CreateComponent<UBoxComponent>(this, &Box, "Box", Root);

	UNiagaraSystem* niagara;
	CHelpers::GetAsset<UNiagaraSystem>(&niagara, "NiagaraSystem'/Game/Effects/P_SwordAura.P_SwordAura'");
	Niagara->SetAsset(niagara);
}

void ACSkill_SwordSlash::BeginPlay()										
{
	Super::BeginPlay();

	Niagara->SetNiagaraVariableObject("Scale_Callback", this);

	Niagara->OnSystemFinished.AddDynamic(this, &ACSkill_SwordSlash::OnSystemFinished);

	Box->OnComponentBeginOverlap.AddDynamic(this, &ACSkill_SwordSlash::OnComponentBeginOverlap);
	Box->OnComponentEndOverlap.AddDynamic(this, &ACSkill_SwordSlash::OnComponentEndOverlap);
	
	GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &ACSkill_SwordSlash::SendDamage, DamageInterval, true);
}
void ACSkill_SwordSlash::OnSystemFinished(class UNiagaraComponent* pSystem)
{
	GetWorld()->GetTimerManager().ClearTimer(TimerHandle);

	Destroy();
}

void ACSkill_SwordSlash::ReceiveParticleData_Implementation(const TArray<FBasicParticleData>& Data, UNiagaraSystem* NiagaraSystem)
{
	Box->SetRelativeScale3D(Data[0].Position);
	FVector location = Box->GetScaledBoxExtent();

	location.Y = 0;
	Box->SetRelativeLocation(location);
}

void ACSkill_SwordSlash::OnComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	CheckTrue(OwnerCharacter == OtherActor);

	ACharacter* character = Cast<ACharacter>(OtherActor);
	if (character)
		Hitted.AddUnique(character);
}

void ACSkill_SwordSlash::OnComponentEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	CheckTrue(OwnerCharacter == OtherActor);

	ACharacter* character = Cast<ACharacter>(OtherActor);
	if (character)
		Hitted.Remove(character);
}

void ACSkill_SwordSlash::SendDamage()
{
	for (int32 i = Hitted.Num() - 1; i >= 0; i--)
		HitData.SendDamage(OwnerCharacter, this, Hitted[i]);
}