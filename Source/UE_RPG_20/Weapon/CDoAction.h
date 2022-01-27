#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "CWeaponStructures.h"
#include "CDoAction.generated.h"

UCLASS()
class UE_RPG_20_API UCDoAction : public UObject
{
	GENERATED_BODY()

public:
	UCDoAction();

	virtual void BeginPlay(class ACAttachment* InAttachment, class ACharacter* InOwner, const TArray<FDoActionData>& InActionDatas, const TArray<FHitData>& InHitDatas);

public:
	virtual void DoAction() {}
	virtual void Begin_DoAction() {}
	virtual void End_DoAction() {}

	virtual void Tick(float InDeltaTime) {}

public :
	UFUNCTION()
		virtual void OnAttachmentBeginOverlap(class ACharacter* InAttacker, class AActor* InAttackCauser, class ACharacter* InOtherCharacter) {}

	UFUNCTION()
		virtual void OnAttachmentEndOverlap(class ACharacter* InAttacker, class AActor* InAttackCauser, class ACharacter* InOtherCharacter) {}

	UFUNCTION()
		virtual void OffAttachmentCollision() {}

	UFUNCTION()
		virtual void OnEquip() {}

	UFUNCTION()
		virtual void OnUnequip() {}

protected :
	class ACharacter* OwnerCharacter;
	class UWorld* World;

	class UCStateComponent* State;

	TArray<FDoActionData> ActionDatas;
	TArray<FHitData> HitDatas;

	const bool* bEquipping;

public :
	FORCEINLINE void SetEquipping(const bool* InEquipping) { bEquipping = InEquipping; }
};
