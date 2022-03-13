#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "CSubAction.generated.h"

UCLASS(Blueprintable)
class UE_RPG_20_API UCSubAction : public UObject
{
	GENERATED_BODY()
	
public :
	UCSubAction() { }

	virtual void BeginPlay(class ACharacter* InOwner);
	virtual void Tick(float InDeltaTime) { } 

public :
	virtual void Pressed() {}
	virtual void Released() {}

	virtual void Begin_SubAction() {}
	virtual void End_SubAction() {}

public :
	UFUNCTION()
		virtual void OnAttachmentBeginOverlap(class ACharacter* InAttacker, class AActor* InAttackCauser, class ACharacter* InOtherCharacter) {}

	UFUNCTION()
		virtual void OnAttachmentEndOverlap(class ACharacter* InAttacker, class AActor* InAttackCauser, class ACharacter* InOtherCharacter) {}

	UFUNCTION()
		virtual void OnAttachmentCollision() {}

	UFUNCTION()
		virtual void OffAttachmentCollision() {}

protected :
	class ACharacter* OwnerCharacter;
	class UWorld* World;
	class UCStateComponent* State;
	class UCStatusComponent* Status;
};
