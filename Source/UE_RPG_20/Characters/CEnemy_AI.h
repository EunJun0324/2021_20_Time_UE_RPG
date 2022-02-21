#pragma once

#include "CoreMinimal.h"
#include "Characters/CEnemy.h"
#include "CEnemy_AI.generated.h"

UCLASS()
class UE_RPG_20_API ACEnemy_AI : public ACEnemy
{
	GENERATED_BODY()
	
private :
	UPROPERTY(EditDefalutsOnly, Category = "AI")
		class UBehaviorTree* BehaviorTree;

	UPROPERTY(EditDefalutsOnly, Category = "AI")
		uint8 TeamID = 2;

private :
	UPROPERTY(VisibleDefaultOnly)
		class UCBehaviorTreeComponent* Behavior;

public :
	FORCEINLINE class UBehaviorTree* GetBehaviorTree()    { return BehaviorTree; }
	FORCEINLINE uint8 GetTeamID()                         { return TeamID; }
	FORCEINLINE class UCBehaviorTreeComponent* GetBehavior() { return Behavior; }

public :
	ACEnemy_AI();

protected :
	virtual void BeginPlay() override;
};
