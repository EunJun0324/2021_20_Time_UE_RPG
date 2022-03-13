#include "Weapon/CSkill.h"
#include "Global.h"
#include "GameFramework/Character.h"


ACSkill::ACSkill()
{
	PrimaryActorTick.bCanEverTick = true;

}

void ACSkill::BeginPlay()
{
	Super::BeginPlay();
	
	OwnerCharacter = Cast<ACharacter>(GetOwner());
}

void ACSkill::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

