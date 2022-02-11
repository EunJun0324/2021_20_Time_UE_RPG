#include "Weapon/CProjectile.h"

ACProjectile::ACProjectile()
{
	PrimaryActorTick.bCanEverTick = true;

}

void ACProjectile::BeginPlay()
{
	Super::BeginPlay();
	
}

void ACProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

