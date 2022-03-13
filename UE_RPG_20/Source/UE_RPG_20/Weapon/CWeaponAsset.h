#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "CWeaponStructures.h"
#include "CEquippment.h"
#include "CWeaponAsset.generated.h"

UCLASS()
class UE_RPG_20_API UCWeaponAsset : public UDataAsset
{
	GENERATED_BODY()
	
public :
	UPROPERTY(BlueprintReadOnly, EditAnywhere)
		TSubclassOf<class ACAttachment> AttachmentClass;

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
		TSubclassOf<class UCEquippment> EquipmentClass;

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
		FEquipmentData EquipmentData;

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
		TSubclassOf<class UCDoAction> DoActionClass;

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
		TArray<FDoActionData> DoActionDatas;

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
		TArray<FHitData> HitDatas;

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
		TSubclassOf<class UCSubAction> SubActionClass;

public :
	UCWeaponAsset();

	void BeginPlay(class ACharacter* InOwner, class UCWeaponData** OutAction);
	void EndPlay();
};
