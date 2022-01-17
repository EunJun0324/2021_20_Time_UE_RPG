#include "Component/CStateComponent.h"

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

void UCStateComponent::ChangeType(EStateType InType)
{ Type = InType; }