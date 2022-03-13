#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "CAIController.generated.h"

UCLASS()
class UE_RPG_20_API ACAIController : public AAIController
{
	GENERATED_BODY()

private :
	UPROPERTY(VisibleDefaultsOnly)
		class UAIPerceptionComponent* Perception;

	UPROPERTY(VisibleDefaultsOnly)
		class UCBehaviorTreeComponent* Behavior;

public :
	ACAIController();

	virtual void Tick(float DeltaTime) override;

protected :
	virtual void BeginPlay() override;

	virtual void OnPossess(APawn* InPawn) override;
	virtual void OnUnPossess() override;

private :
	UFUNCTION()
		void OnPerceptionUpdated(const TArray<AActor*>& UpdatedActors);

private :
	class ACEnemy_AI* OwnerCharacter;
	class UAISenseConfig_Sight* SightSense;


};
