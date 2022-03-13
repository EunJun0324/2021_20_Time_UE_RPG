#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Component/CStateComponent.h"
#include "Engine/DataTable.h"
#include "CMontageComponent.generated.h"


USTRUCT(BlueprintType)
struct FMontageData : public FTableRowBase
{
	GENERATED_BODY()

public :
	UPROPERTY(EditAnywhere)
		EStateType Type;

	UPROPERTY(EditAnywhere)
		class UAnimMontage* Montage;

	UPROPERTY(EditAnywhere)
		float PlayRatio;

	UPROPERTY(EditAnywhere)
		FName SectionName;
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class UE_RPG_20_API UCMontageComponent : public UActorComponent
{
	GENERATED_BODY()

private :
	UPROPERTY(EditAnywhere, Category = "DataTable")
		class UDataTable* DataTable;

public:	
	UCMontageComponent();

protected:
	virtual void BeginPlay() override;

public :
	void PlayHittedMode();
	void PlayDeadMode();

private :
	void PlayAnimMontage(EStateType InType);

private :
	class ACharacter* OwnerCharacter;

	FMontageData* Datas[(int32)EStateType::Max];
};
