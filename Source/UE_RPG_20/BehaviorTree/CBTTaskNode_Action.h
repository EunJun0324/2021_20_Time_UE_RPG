#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "CBTTaskNode_Action.generated.h"

UCLASS()
class UE_RPG_20_API UCBTTaskNode_Action : public UBTTaskNode
{
	GENERATED_BODY()
	
private :
	UPROPERTY(EditAnywhere, Category = "AI")
		float Delay = 2.0f;

public:
	UCBTTaskNode_Action();

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	virtual EBTNodeResult::Type AbortTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

	virtual void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

private :
	float TotalTime;
};
