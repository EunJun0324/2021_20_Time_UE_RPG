#include "Component/CStateComponent.h"
#include "Global.h"

UCStateComponent::UCStateComponent() {}

void UCStateComponent::BeginPlay()
{ Super::BeginPlay(); }

void UCStateComponent::SetIdleMode()
{ ChangeType(EStateType::Idle); }

void UCStateComponent::SetEquipMode()
{ ChangeType(EStateType::Equip); }

void UCStateComponent::SetHittedMode()
{ ChangeType(EStateType::Hitted); }

void UCStateComponent::SetDeadMode()
{ ChangeType(EStateType::Dead); }

void UCStateComponent::SetActionMode()
{ ChangeType(EStateType::Action); }

void UCStateComponent::OnSubActionMode()
{ bInSubAction = true; }

void UCStateComponent::OffSubActionMode()
{ bInSubAction = false; }

void UCStateComponent::ChangeType(EStateType InType)
{ 
	Type = InType; 

	if (OnStateTypeChanged.IsBound())
		OnStateTypeChanged.Broadcast(InType);
}