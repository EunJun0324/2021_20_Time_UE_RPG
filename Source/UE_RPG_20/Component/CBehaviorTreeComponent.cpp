#include "Component/CBehaviorTreeComponent.h"
#include "Global.h"
#include "Characters/CPlayer.h"
#include "BehaviorTree/BlackboardComponent.h"

bool UCBehaviorTreeComponent::IsWaitMode()
{ return GetType() == EBehaviorType::Wait; }

bool UCBehaviorTreeComponent::IsApproachMode()
{ return GetType() == EBehaviorType::Approach; }

bool UCBehaviorTreeComponent::IsActionMode()
{ return GetType() == EBehaviorType::Action; }

bool UCBehaviorTreeComponent::IsPatrolMode()
{ return GetType() == EBehaviorType::Patrol; }

bool UCBehaviorTreeComponent::IsHittedMode()
{ return GetType() == EBehaviorType::Hitted; }

UCBehaviorTreeComponent::UCBehaviorTreeComponent() {}

void UCBehaviorTreeComponent::BeginPlay()
{ Super::BeginPlay(); }

void UCBehaviorTreeComponent::SetWaitMode()
{
	ChangeType(EBehaviorType::Wait); }

void UCBehaviorTreeComponent::SetApproachMode()
{ ChangeType(EBehaviorType::Approach); }

void UCBehaviorTreeComponent::SetActionMode()
{ ChangeType(EBehaviorType::Action); }

void UCBehaviorTreeComponent::SetPatrolMode()
{ ChangeType(EBehaviorType::Patrol); }

void UCBehaviorTreeComponent::SetHittedMode()
{ ChangeType(EBehaviorType::Hitted); }

ACPlayer* UCBehaviorTreeComponent::GetTargetPlayer()
{ return Cast<ACPlayer>(BlackBoard->GetValueAsObject(PlayerKey)); }

FVector UCBehaviorTreeComponent::GetLocation()
{ return BlackBoard->GetValueAsVector(LocationKey); }

void UCBehaviorTreeComponent::ChangeType(EBehaviorType InType)
{
	BlackBoard->SetValueAsEnum(BehaviorKey, (uint8)InType);

	if (OnBehaviorTypeChanged.IsBound())
		OnBehaviorTypeChanged.Broadcast(InType);
}

EBehaviorType UCBehaviorTreeComponent::GetType()
{ return (EBehaviorType)BlackBoard->GetValueAsEnum(BehaviorKey); }

