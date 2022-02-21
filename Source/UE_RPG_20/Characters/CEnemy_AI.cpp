#include "Characters/CEnemy_AI.h"
#include "Global.h"
#include "Component/CBehaviorTreeComponent.h"


ACEnemy_AI::ACEnemy_AI()
{
	CHelpers::CreateActorComponent<UCBehaviorTreeComponent>(this, &Behavior, "Behavior");
}

void ACEnemy_AI::BeginPlay()
{
	Super::BeginPlay();

}