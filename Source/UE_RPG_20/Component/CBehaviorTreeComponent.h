#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CBehaviorTreeComponent.generated.h"

UENUM(BlueprintType)
enum class EBhaviorType : uint8
{
	Wait, Approach, Action, Patrol, Hitted, Max,
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FBehaviorTypeChanged, EBhaviorType, InNewType)


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class UE_RPG_20_API UCBehaviorTreeComponent : public UActorComponent
{
	GENERATED_BODY()

private :
	UPROPERTY(EditAnywhere)
		FName BehaviorKey = "Behavior";

	UPROPERTY(EditAnywhere)
		FName PlayerKey = "Player";

	UPROPERTY(EditAnywhere)
		FName LocationKey = "Location";

public:
	FORCEINLINE void SetBlackBoard(class UBlackboardComponent* InBlackBoard) { BlackBoard = InBlackBoard; }

public:	
	UCBehaviorTreeComponent();

protected:
	virtual void BeginPlay() override;

private :
	class UBlackboardComponent* BlackBoard;
};
