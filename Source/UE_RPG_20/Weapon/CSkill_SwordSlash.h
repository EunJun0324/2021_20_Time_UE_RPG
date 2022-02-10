#pragma once

#include "CoreMinimal.h"
#include "Weapon/CSkill.h"
#include "CSkill_SwordSlash.generated.h"

UCLASS()
class UE_RPG_20_API ACSkill_SwordSlash : public ACSkill
{
	GENERATED_BODY()
	
private :
	UPROPERTY(EditDefaultsOnly, Category = "Damage")
		float DamageInterval = 0.1f;

private :
	UPROPERTY(EditDefaultsOnly)
		class USceneComponent* Root;

protected :
	UPROPERTY(BlueprintReadOnly, VisibleDefaultsOnly)
		class UNiagaraComponent* Niagara;

	UPROPERTY(BlueprintReadOnly, VisibleDefaultsOnly)
		class UBoxComponent* Box;

public :
	ACSkill_SwordSlash();

protected :
	virtual void BeginPlay();

private :
	UFUNCTION()
		void OnSystemFinished(class UNiagaraComponent* pSystem);

	UFUNCTION()
		void OnComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
		void OnComponentEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	UFUNCTION()
		void SendDamage();

private :
	TArray<ACharacter*> Hitted;

	FTimerHandle TimerHandle;
};
