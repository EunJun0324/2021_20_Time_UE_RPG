#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CSword.generated.h"

UCLASS()
class UE_RPG_20_API ACSword : public AActor
{
	GENERATED_BODY()
	
private :
	UPROPERTY(VisibleDefaultsOnly)
		class USceneComponent* Root;

	UPROPERTY(VisibleDefaultsOnly)
		class USkeletalMeshComponent* Mesh;

	UPROPERTY(VisibleDefaultsOnly)
		class UCapsuleComponent* Capsule;

private :
	UPROPERTY(EditDefaultsOnly)
		class UAnimMontage* EquipMontage;

public:	
	ACSword();

	void Equip();
	void Begin_Equip();
	void End_Equip();

	void Unequip();

	void OnCollision();
	void OffCollision();

protected:
	virtual void BeginPlay() override;
	
private :
	UFUNCTION()
		void OnComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

public :
	FORCEINLINE bool GetEquipped() const { return bEquipped; }

private :
	class ACharacter* OwnerCharacter;
	class UCStateComponent* State;
	class UCStatusComponent* Status;

	bool bEquipped;
	
};
