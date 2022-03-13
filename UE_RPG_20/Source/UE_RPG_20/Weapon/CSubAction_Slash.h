#pragma once

#include "CoreMinimal.h"
#include "Weapon/CSubAction.h"
#include "Weapon/CWeaponStructures.h"
#include "CSubAction_Slash.generated.h"

UCLASS()
class UE_RPG_20_API UCSubAction_Slash : public UCSubAction
{
	GENERATED_BODY()
	
private :
	UPROPERTY(EditDefaultsOnly, Category = "Skill")
		TSubclassOf<class ACSkill_SwordSlash> SkillClass;

	UPROPERTY(EditDefaultsOnly, Category = "Skill")
		FTransform SkillTransform;

	UPROPERTY(EditDefaultsOnly, Category = "Skill")
		FDoActionData ActionData;

	UPROPERTY(EditDefaultsOnly, Category = "Skill")
		FHitData HitData;

public :
	UCSubAction_Slash();

	virtual void Pressed() override;
	virtual void Begin_SubAction() override;
	virtual void End_SubAction() override;
};
