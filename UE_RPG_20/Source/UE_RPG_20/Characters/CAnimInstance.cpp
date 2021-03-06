#include "CAnimInstance.h"
#include "Global.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"

#include "Characters/CPlayer.h"
#include "CSword.h"

void UCAnimInstance::NativeBeginPlay()
{
	Super::NativeBeginPlay();

	OwnerCharacter = Cast<ACharacter>(TryGetPawnOwner());
	CheckNull(OwnerCharacter);
	
	Weapon = CHelpers::GetComponent<UCWeaponComponent>(OwnerCharacter);

	if (Weapon)
		Weapon->OnWeaponTypeChanged.AddDynamic(this, &UCAnimInstance::OnWeaponTypeChanged);
}

void UCAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);
	CheckNull(OwnerCharacter);

	Speed = OwnerCharacter->GetVelocity().Size2D();
	Direction = CalculateDirection(OwnerCharacter->GetVelocity(), OwnerCharacter->GetControlRotation());
	Pitch = OwnerCharacter->GetBaseAimRotation().Pitch;

	// ACPlayer* player = Cast<ACPlayer>(OwnerCharacter);
	// if (player) bEquipped = player->GetSword()->GetEquipped();
}

void UCAnimInstance::OnWeaponTypeChanged(EWeaponType InNewType)
{ WeaponType = InNewType; }