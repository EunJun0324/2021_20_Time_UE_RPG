#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "CAnimNotify_Begin_DoAction.generated.h"

UCLASS()
class UE_RPG_20_API UCAnimNotify_Begin_DoAction : public UAnimNotify
{
	GENERATED_BODY()
	
private:
	FString GetNotifyName_Implementation() const override;

	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) override;
};
