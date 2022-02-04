#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Component/CStateComponent.h"
#include "CEnemy.generated.h"

UCLASS()
class UE_RPG_20_API ACEnemy : public ACharacter
{
	GENERATED_BODY()

private :
	UPROPERTY(EditDefaultsOnly, Category = "Color")
		FLinearColor OriginColor = FLinearColor::Black;

private:
	UPROPERTY(VisibleDefaultsOnly)
		class UCMontageComponent* Montage;

	UPROPERTY(VisibleDefaultsOnly)
		class UCStatusComponent* Status;

	UPROPERTY(VisibleDefaultsOnly)
		class UCStateComponent* State;

public:
	ACEnemy();

	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent,
		class AController* EventInstigator, AActor* DamageCauser) override;

protected:
	virtual void BeginPlay() override;

private :
	UFUNCTION()
		void OnStateTypeChanged(EStateType InType);

private :
	void Hitted();
	void Dead();
private :
	void Change_Character_Color(FLinearColor InColor);

private :
	struct FDamaged
	{
		float DamageAmount;
		class AController* EventInstigator;
		struct FActionDamageEvent* DamageEvent;
	}Damaged;

	TArray<class UMaterialInstanceDynamic*> Materials;
};
