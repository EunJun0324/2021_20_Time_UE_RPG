#pragma once

#include "CoreMinimal.h"
#include "Weapon/CSubAction.h"
#include "Weapon/CWeaponStructures.h"
#include "Kismet/KismetSystemLibrary.h"
#include "CSubAction_Launcher.generated.h"

UCLASS()
class UE_RPG_20_API UCSubAction_Launcher : public UCSubAction
{
	GENERATED_BODY()
	
private :
	UPROPERTY(EditDefaultsOnly, Category = "Trace")
		float Distance = 1000;

	UPROPERTY(EditDefaultsOnly, Category = "Trace")
		float Speed = 200;

	UPROPERTY(EditDefaultsOnly, Category = "Trace")
		TEnumAsByte<EDrawDebugTrace::Type> DrawDebug;

	UPROPERTY(EditDefaultsOnly, Category = "Data")
		FDoActionData ActionData;

	UPROPERTY(EditDefaultsOnly, Category = "Data")
		FHitData HitData;

public :
	UCSubAction_Launcher();

	virtual void BeginPlay(class ACharacter* InOwner) override;
	virtual void Tick(float InDeltaTime) override;

	
	virtual void Pressed() override;

	virtual void Begin_SubAction() override;
	virtual void End_SubAction() override;

public :
	virtual void OnAttachmentBeginOverlap(class ACharacter* InAttacker, class AActor* InAttackCauser, class ACharacter* InOtherCharacter) override;

private :
	bool bMoving;
	FVector Start;
	FVector End;

	float OwnerRadius;

	TArray<class ACharacter*> Overlapped;
	TArray<class ACharacter*> Hitted;

};
