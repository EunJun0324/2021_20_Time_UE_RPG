#include "Weapon/CProjectile.h"
#include "Global.h"
#include "GameFramework/Character.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/SphereComponent.h"


ACProjectile::ACProjectile()
{
	CHelpers::CreateComponent<USphereComponent>(this, &Sphere, "Sphere");
	CHelpers::CreateActorComponent<UProjectileMovementComponent>(this, &Projectile, "Projectile");

	Projectile->ProjectileGravityScale = 0;
}

void ACProjectile::BeginPlay()
{
	Super::BeginPlay();

	Sphere->OnComponentHit.AddDynamic(this, &ACProjectile::OnComponentHit);

	Sphere->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	Projectile->Deactivate();
}

void ACProjectile::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);

	if (OnProjectileEndPlay.IsBound())
		OnProjectileEndPlay.Broadcast(this);
}

void ACProjectile::OnComponentHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	for (AActor* actor : IgnoreActors)
		CheckTrue(actor == OtherActor);

	ACharacter* character = Cast<ACharacter>(OtherActor);
	Sphere->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	if (character && OnProjectileHit.IsBound())
		OnProjectileHit.Broadcast(this, character);
}

void ACProjectile::Shoot(const FVector& InForward)
{
	DetachFromActor(FDetachmentTransformRules(EDetachmentRule::KeepWorld, true));

	Projectile->Velocity = InForward * Projectile->InitialSpeed;

	Sphere->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	
	Projectile->Activate();
}

