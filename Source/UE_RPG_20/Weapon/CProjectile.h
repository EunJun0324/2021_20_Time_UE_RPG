#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CProjectile.generated.h"

UCLASS()
class UE_RPG_20_API ACProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	ACProjectile();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

};
