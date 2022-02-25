#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CPatrolComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class UE_RPG_20_API UCPatrolComponent : public UActorComponent
{
	GENERATED_BODY()

private :
	UPROPERTY(EditAnywhere, Category = "Path")
		class ACPatrolPath* Path;

	UPROPERTY(EditAnywhere, Category = "Path")
		int32 NextIndex;

	UPROPERTY(EditAnywhere, Category = "Path")
		bool bReverse;

	UPROPERTY(EditAnywhere, Category = "Path")
		float AcceptanceDistanse = 10;

public :
	FORCEINLINE bool IsValidPath() { return Path != nullptr; }

public:	
	UCPatrolComponent();
	
	bool GetMoveTo(FVector& OutLocation, float& OutAcceptanceDistanse);

	void UpdateNextIndex();

protected:
	virtual void BeginPlay() override;

};
