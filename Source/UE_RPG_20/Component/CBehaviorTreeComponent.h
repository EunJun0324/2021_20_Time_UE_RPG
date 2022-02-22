#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CBehaviorTreeComponent.generated.h"

UENUM(BlueprintType)
enum class EBehaviorType : uint8
{
	Wait, Approach, Action, Patrol, Hitted, Max,
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FBehaviorTypeChanged, EBehaviorType, InNewType);


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
	UFUNCTION(BlueprintPure)
		bool IsWaitMode();

	UFUNCTION(BlueprintPure)
		bool IsApproachMode();

	UFUNCTION(BlueprintPure)
		bool IsActionMode();

	UFUNCTION(BlueprintPure)
		bool IsPatrolMode();

	UFUNCTION(BlueprintPure)
		bool IsHittedMode();

	FORCEINLINE void SetBlackBoard(class UBlackboardComponent* InBlackBoard) { BlackBoard = InBlackBoard; }

public:	
	UCBehaviorTreeComponent();

public :
		void SetWaitMode();
		void SetApproachMode();
		void SetActionMode();
		void SetPatrolMode();
		void SetHittedMode();

		class ACPlayer* GetTargetPlayer();
		FVector GetLocation();

protected:
	virtual void BeginPlay() override;

private :
	void ChangeType(EBehaviorType InType);

	EBehaviorType GetType();

public :
	UPROPERTY(BlueprintAssignable)
		FBehaviorTypeChanged OnBehaviorTypeChanged;

private :
	class UBlackboardComponent* BlackBoard;
};
