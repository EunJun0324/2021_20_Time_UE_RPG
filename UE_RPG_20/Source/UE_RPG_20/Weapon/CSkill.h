#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Weapon/CWeaponStructures.h"
#include "CSkill.generated.h"

UCLASS()
class UE_RPG_20_API ACSkill : public AActor
{
	GENERATED_BODY()
	
public :
	FORCEINLINE void SetHitData(FHitData InHitData) { HitData = InHitData; }

public:	
	ACSkill();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

protected :
	class ACharacter* OwnerCharacter;
	FDoActionData ActionData;
	FHitData HitData;
};
