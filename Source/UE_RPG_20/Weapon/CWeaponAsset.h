#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "CWeaponStructures.h"
#include "CWeaponAsset.generated.h"

UCLASS()
class UE_RPG_20_API UCWeaponAsset : public UDataAsset
{
	GENERATED_BODY()
	
public :
	UPROPERTY(BlueprintReadOnly, EditAnywhere)
		TSubclassOf<class UCEquipment> EquipmentClass;

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
		TArray<FDoActionData> DoActionDatas;

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
		TArray<FHitData> HitDatas;
};
