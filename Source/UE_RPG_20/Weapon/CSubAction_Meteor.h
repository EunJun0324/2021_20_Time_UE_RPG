#pragma once

#include "CoreMinimal.h"
#include "Weapon/CSubAction.h"
#include "CWeaponStructures.h"
#include "CSubAction_Meteor.generated.h"

UCLASS()
class UE_RPG_20_API UCSubAction_Meteor : public UCSubAction
{
	GENERATED_BODY()
	
private :
	UPROPERTY(EditDefaultsOnly, Category = "Skill")
		TSubclassOf<class ACSkill_Thron> SkillClass;

	UPROPERTY(EditDefaultsOnly, Category = "Skill")
		FTransform SkillTransform;

	UPROPERTY(EditDefaultsOnly, Category = "Data")
		FDoActionData ActionData;

	UPROPERTY(EditDefaultsOnly, Category = "Data")
		FHitData HitData;

public :
	UCSubAction_Meteor();

	virtual void Pressed() override;

	virtual void Begin_SubAction() override;
	virtual void End_SubAction() override;

};
