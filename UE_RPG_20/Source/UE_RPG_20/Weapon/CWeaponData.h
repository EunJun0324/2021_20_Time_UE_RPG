#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "CWeaponData.generated.h"

UCLASS(Blueprintable)
class UE_RPG_20_API UCWeaponData : public UObject
{
	GENERATED_BODY()
	
private :
	friend class UCWeaponAsset;

public :
	FORCEINLINE class ACAttachment* GetAttachment() { return Attachment; }
	FORCEINLINE class UCEquippment* GetEquippment() { return Equippment; }
	FORCEINLINE class UCDoAction* GetDoAction() { return DoAction; }
	FORCEINLINE class UCSubAction* GetSubAction() { return SubAction; }

private:
	class ACAttachment* Attachment;

	class UCEquippment* Equippment;

	class UCDoAction* DoAction;

	class UCSubAction* SubAction;
};
