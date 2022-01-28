#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "CEquippment.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FEquipAndUnequip);

USTRUCT(BlueprintType)
struct FEquipmentData
{
	GENERATED_BODY()

public :
	UPROPERTY(EditAnywhere)
		class UAnimMontage* Montage;

	UPROPERTY(EditAnywhere)
		float PlayRatio = 1;

	UPROPERTY(EditAnywhere)
		bool bCanMove = true;

	UPROPERTY(EditAnywhere)
		bool bLookForward = true;
};

UCLASS(Blueprintable)
class UE_RPG_20_API UCEquippment : public UObject
{
	GENERATED_BODY()
	
public :
	FORCEINLINE const bool* IsEquipping() { return &bEquipping; }

public :
	UCEquippment();

	void BeginPlay(class ACharacter* InOwner, const FEquipmentData& InData);

public :
	UFUNCTION(BlueprintNativeEvent)
		void Equip();
	void Equip_Implementation();


	UFUNCTION(BlueprintNativeEvent)
		void Begin_Equip();
	void Begin_Equip_Implementation();


	UFUNCTION(BlueprintNativeEvent)
		void End_Equip();
	void End_Equip_Implementation();


	UFUNCTION(BlueprintNativeEvent)
		void Unequip();
	void Unequip_Implementation();

public :
	FEquipAndUnequip OnEquip;
	FEquipAndUnequip OnUnequip;

protected :
	class ACharacter* OwnerCharacter;
	class UCStateComponent* State;
	class UCStatusComponent* Status;

	FEquipmentData Data;
	bool bEquipping;
};
