#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CWeaponComponent.generated.h"

UENUM(BlueprintType)
enum class EWeaponType : uint8
{
	Fist, OneHand, TwoHand, Warp, Wizard, Bow, Max,
};


DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FWeaponTypeChanged, EWeaponType, InNewType);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class UE_RPG_20_API UCWeaponComponent : public UActorComponent
{
	GENERATED_BODY()

private :
	UPROPERTY(EditAnywhere, Category = "DataAsset")
		class UCWeaponAsset* DataAssets[(int32)EWeaponType::Max];

public :
	FORCEINLINE bool IsUnarmedMode()   { return Type == EWeaponType::Max; }
	FORCEINLINE bool IsFistMode()      { return Type == EWeaponType::Fist; }
	FORCEINLINE bool IsOneHandMode()   { return Type == EWeaponType::OneHand; }
	FORCEINLINE bool IsTwoHandMode()   { return Type == EWeaponType::TwoHand; }
	FORCEINLINE bool IsWarpMode()      { return Type == EWeaponType::Warp; }
	FORCEINLINE bool IsWizardMode()    { return Type == EWeaponType::Wizard; }
	FORCEINLINE bool IsBowMode()       { return Type == EWeaponType::Bow; }


public:	
	UCWeaponComponent();

    void SetUnarmedMode();
    void SetFistMode();
    void SetOneHandMode();
    void SetTwoHandMode();
    void SetWarpMode();
    void SetWizardMode();
    void SetBowMode();

	void DoAction();
	void SubAction_Pressed();
	void SubAction_Released();

	void RemoveAll();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

public :
	class ACAttachment* GetAttachment();
	class UCEquippment* GetEquipment();
	class UCDoAction*   GetDoAction();
	class UCSubAction*  GetSubAction();

private :
	void SetMode(EWeaponType InType);
	void ChangeType(EWeaponType InType);

public :
	UPROPERTY(BlueprintAssignable)
		FWeaponTypeChanged OnWeaponTypeChanged;

private :
	class ACharacter* OwnerCharacter;
	EWeaponType Type = EWeaponType::Max;

	class UCWeaponData* Datas[(int32)EWeaponType::Max];
};
