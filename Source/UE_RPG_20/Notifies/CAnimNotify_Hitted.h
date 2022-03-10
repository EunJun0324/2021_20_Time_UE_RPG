#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "CAnimNotify_Hitted.generated.h"

UCLASS()
class UE_RPG_20_API UCAnimNotify_Hitted : public UAnimNotify
{
	GENERATED_BODY()

private:
	FString GetNotifyName_Implementation() const override;

	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) override;
};
