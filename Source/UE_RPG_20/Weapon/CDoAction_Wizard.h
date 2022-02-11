#pragma once

#include "CoreMinimal.h"
#include "Weapon/CDoAction.h"
#include "CDoAction_Wizard.generated.h"

UCLASS()
class UE_RPG_20_API UCDoAction_Wizard : public UCDoAction
{
	GENERATED_BODY()
	
private :
	TSubclassOf<class ACProjectile> ProjectileClass;

public :
	UCDoAction_Wizard();

	virtual void BeginPlay(class ACAttachment* InAttachment, class ACharacter* InOwner, const TArray<FDoActionData>& InActionDatas, const TArray<FHitData>& InHitDatas) override;

public:
	virtual void DoAction() override;
	virtual void Begin_DoAction() override;
	virtual void End_DoAction() override;

	virtual void Tick(float InDeltaTime)override;

public:
	UFUNCTION()
		void OnFireballBeginOverlap(class AActor* InAttackCauser, class ACharacter* InOtherCharacter);
};
