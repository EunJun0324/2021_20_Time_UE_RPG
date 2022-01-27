#pragma once

#include "CoreMinimal.h"
#include "Weapon/CDoAction.h"
#include "CDoAction_Combo.generated.h"

UCLASS()
class UE_RPG_20_API UCDoAction_Combo : public UCDoAction
{
	GENERATED_BODY()
	
public:
	virtual void DoAction() override;
	virtual void Begin_DoAction() override;
	virtual void End_DoAction() override;

public:
	virtual void OnAttachmentBeginOverlap(class ACharacter* InAttacker, class AActor* InAttackCauser, class ACharacter* InOtherCharacter) override;

	virtual void OffAttachmentCollision() override;

private :
	int32 Index; 

	bool bEnable;
	bool bExist;

	int32 HitIndex;
	TArray<class ACharacter*> Hitted;
}; 
