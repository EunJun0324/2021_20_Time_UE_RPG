#include "Characters/CEnemy_AI.h"
#include "Global.h"
#include "Component/CBehaviorTreeComponent.h"
#include "Component/CWeaponComponent.h"
#include "Component/CStateComponent.h"
#include "Component/CPatrolComponent.h"

ACEnemy_AI::ACEnemy_AI()
{
	CHelpers::CreateActorComponent<UCBehaviorTreeComponent>(this, &Behavior, "Behavior");
	CHelpers::CreateActorComponent<UCPatrolComponent>(this, &Patrol, "Patrol");
}

void ACEnemy_AI::BeginPlay()
{
	Super::BeginPlay();

	CheckFalse(State->IsIdleMode());
	Weapon->SetOneHandMode();
}