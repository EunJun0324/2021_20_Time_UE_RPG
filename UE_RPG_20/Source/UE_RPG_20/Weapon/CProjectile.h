#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CProjectile.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FProjectileHit, class AActor*, InCauser, class ACharacter*, InOtherActor);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FProjectileEndPlay, class ACProjectile*, InDestroyer);

UCLASS()
class UE_RPG_20_API ACProjectile : public AActor
{
	GENERATED_BODY()
	
private :
	UPROPERTY(VisibleDefaultsOnly)
		class USphereComponent* Sphere;

	UPROPERTY(VisibleDefaultsOnly)
		class UProjectileMovementComponent* Projectile;

public :
	FORCEINLINE void SetIgnoreActors(const TArray<AActor*> InActors)
	{ IgnoreActors = InActors; }

public:	
	ACProjectile();

	void Shoot(const FVector& InForward);

protected:
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

private :
	UFUNCTION()
		void OnComponentHit(UPrimitiveComponent* HitComponent, AActor* OtherActor ,UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

public :
	FProjectileHit     OnProjectileHit;
	FProjectileEndPlay OnProjectileEndPlay;


private : 
	TArray<AActor*> IgnoreActors;
};
