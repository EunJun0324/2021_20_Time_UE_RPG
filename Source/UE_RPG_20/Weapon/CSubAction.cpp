#include "Weapon/CSubAction.h"
#include "Global.h"
#include "GameFramework/Character.h"
#include "Component/CStateComponent.h"
#include "Component/CStatusComponent.h"


void UCSubAction::BeginPlay(class ACharacter* InOwner)
{
	OwnerCharacter = InOwner;
	World = OwnerCharacter->GetWorld();

	State  = CHelpers::GetComponent<UCStateComponent>(OwnerCharacter);
	Status = CHelpers::GetComponent<UCStatusComponent>(OwnerCharacter);
}