#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "CWeaponStructures.generated.h"

USTRUCT(BlueprintType)
struct FDoActionData
{
	GENERATED_BODY()

public :
	UPROPERTY(EditAnywhere)
		class UAnimMontage* Montage;

	UPROPERTY(EditAnywhere)
		float PlayRatio = 1;

	UPROPERTY(EditAnywhere)
		bool bCanMove = true;

	UPROPERTY(EditAnywhere)
		bool bFixedCamera;

	UPROPERTY(EditAnywhere)
		class UFXSystemAsset* Effect;

	UPROPERTY(EditAnywhere)
		FTransform EffectTransform;

public :
	void PlayMontage(class ACharacter* InOwner);
	void PlayEffect(class UWorld* InWorld, class ACharacter* InOwner);
	void PlayEffect(class USkeletalMeshComponent* InMesh, FName InSockectName = NAME_None);
	
	void EndAction(class ACharacter* InOwner);

};

USTRUCT(BlueprintType)
struct FHitData
{
	GENERATED_BODY()

public :
	UPROPERTY(EditAnywhere)
		class UAnimMontage* Montage;

	UPROPERTY(EditAnywhere)
		float PlayRatio = 1;

	UPROPERTY(EditAnywhere)
		bool bCanMove = true;

	UPROPERTY(EditAnywhere)
		float Power = 5;

	UPROPERTY(EditAnywhere)
		float Launch = 100;

	UPROPERTY(EditAnywhere)
		float StopTime;

	UPROPERTY(EditAnywhere)
		class UFXSystemAsset* Effect;

	UPROPERTY(EditAnywhere)
		FTransform EffectTransform;

	UPROPERTY(EditAnywhere)
		class USoundCue* SoundCue;

public:
	void PlayMontage(class ACharacter* InOwner);
	void PlayEffect(class UWorld* InWorld, const FTransform& InTransform);
	void PlayEffect(class USkeletalMeshComponent* InMesh, FName InSockectName = NAME_None);
	void PlaySoundCue(class UWorld* InWorld, const FVector& InLocation);
	void PlayHitStop(class UWorld* InWorld);
	void SendDamage(class ACharacter* InAttacker, class AActor* InAttackCursor, class ACharacter* InOtherCharacter);

};

USTRUCT(BlueprintType)
struct FActionDamageEvent : public FDamageEvent
{
	GENERATED_BODY()

public :
	FHitData* HitData;
};

UCLASS()
class UE_RPG_20_API UCWeaponStructures : public UObject
{

	GENERATED_BODY()

public:
	UCWeaponStructures();

	FORCEINLINE static class UAnimMontage* GetDefaultHitMontage() { return DefaultHitMontage; }

private :
	static class UAnimMontage* DefaultHitMontage;
};
