#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "Component/CStatusComponent.h"
#include "CBTTaskNode_Speed.generated.h"

UCLASS()
class UE_RPG_20_API UCBTTaskNode_Speed : public UBTTaskNode
{
	GENERATED_BODY()
		
private :
	UPROPERTY(EditAnywhere, Category = "Speed")
		ESpeedType Type;

public :
	UCBTTaskNode_Speed();

protected :
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};
