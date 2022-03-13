#pragma once

#include "CoreMinimal.h"
#include "Weapon/CDoAction.h"
#include "CDoAction_Wizard.generated.h"

UCLASS()
class UE_RPG_20_API UCDoAction_Wizard : public UCDoAction
{
	GENERATED_BODY()
	
private :
	UPROPERTY(EditDefaultsOnly, Category = "FireBall")
	TSubclassOf<class ACProjectile> FireBallClass;

public :
	UCDoAction_Wizard();

	virtual void BeginPlay(class ACAttachment* InAttachment, class ACharacter* InOwner, const TArray<FDoActionData>& InActionDatas, const TArray<FHitData>& InHitDatas) override;

public:
	virtual void DoAction() override;
	virtual void Begin_DoAction() override;
	virtual void End_DoAction() override;

	virtual void OnEquip() override;
	virtual void OnUnequip() override;

private :
	void CreateFireBall();

	UFUNCTION()
		void FireBallHit(class AActor* InCauser, class ACharacter* InOtherCharacter);

	UFUNCTION()
		void FireBallDestroy(class ACProjectile* InDestroyer);

private :
	TArray<class ACProjectile*> FireBalls;
};
