#include "BehaviorTree/CBTService_Melee.h"
#include "Global.h"
#include "Characters/CEnemy_AI.h"
#include "Characters/CPlayer.h"
#include "Controllers/CAIController.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "Component/CStateComponent.h"
#include "Component/CBehaviorTreeComponent.h"
#include "Component/CPatrolComponent.h"


UCBTService_Melee::UCBTService_Melee()
{ NodeName = "Melee"; }

void UCBTService_Melee::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	ACAIController* controller = Cast<ACAIController>(OwnerComp.GetOwner());
	ACEnemy_AI* ai = Cast<ACEnemy_AI>(controller->GetPawn());
	UCStateComponent* state = CHelpers::GetComponent<UCStateComponent>(ai);
	UCBehaviorTreeComponent* behavior = CHelpers::GetComponent<UCBehaviorTreeComponent>(ai);

	if (state->IsHittedMode())
	{
		behavior->SetHittedMode();

		return;
	}

	ACPlayer* player = behavior->GetTargetPlayer();

	if (!player)
	{
		UCPatrolComponent* patrol = CHelpers::GetComponent<UCPatrolComponent>(ai);

		if (patrol)
		{
			behavior->SetPatrolMode();

			return;
		}

		behavior->SetWaitMode();

		return;
	}

	float distance = ai->GetDistanceTo(player);
	if (distance < ActionRange)
	{
		behavior->SetActionMode();

		return;
	}

	behavior->SetApproachMode();
}