#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "CAIController.generated.h"

UCLASS()
class UE_RPG_20_API ACAIController : public AAIController
{
	GENERATED_BODY()

private :
	UPROPERTY(EditAnywhere)
		class UAISenseConfig_Sight* SightSense;
public :
	ACAIController();
};
