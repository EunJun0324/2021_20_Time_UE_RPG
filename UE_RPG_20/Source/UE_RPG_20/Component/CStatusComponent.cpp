#include "Component/CStatusComponent.h"
#include "Global.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"

UCStatusComponent::UCStatusComponent() {}

void UCStatusComponent::AddHealth(float InAmount)
{
	Health += InAmount;
	Health = FMath::Clamp(Health, 0.0f, MaxHealth);

	if (OnChangeHpEvent.IsBound())
		OnChangeHpEvent.Broadcast(Health / MaxHealth);
}

void UCStatusComponent::SubHealth(float InAmount)
{
	Health -= InAmount;
	Health = FMath::Clamp(Health, 0.0f, MaxHealth);

	if (OnChangeHpEvent.IsBound())
		OnChangeHpEvent.Broadcast(Health / MaxHealth);
}

void UCStatusComponent::SetSpeed(ESpeedType InType)
{ OwnerCharacter->GetCharacterMovement()->MaxWalkSpeed = Speed[(int32)InType]; }

void UCStatusComponent::BeginPlay()
{
	Super::BeginPlay();

	OwnerCharacter = Cast<ACharacter>(GetOwner());

	Health = MaxHealth;
}




